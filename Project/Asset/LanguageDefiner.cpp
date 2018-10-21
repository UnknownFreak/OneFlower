#include "Language.hpp"
#include <fstream>
#include <Core\EngineModule\EngineModuleManager.hpp>

void Language::loadFont(const Core::String & name)
{
	Core::String path = "Data/Font" + name;
	std::wstring wstr = Engine::GetModule<Core::StringConverter>().toUtf16(path);
	std::ifstream i(path, std::ios::in | std::ifstream::binary);
	i.seekg(0, i.end);
	size_t len = (size_t)i.tellg();
	i.seekg(0, i.beg);
	char* data = new char[len];
	i.read(data, len);

	m_font.loadFromMemory(data, len);
	delete[] data;
}

Language::Language(Core::String fontName) : m_font(), stringList(DatabaseIndex::ObjectTypeEnum::PrimitiveString, "Data\\Lang\\")
{
	loadFont(fontName);
}

sf::Font & Language::getFont()
{
	return m_font;
}

Core::String Language::getString(size_t id)
{
	PrimitiveSaveable<Core::String>& strR = stringList.request(languageFile, id);
	if (strR.getValue() == "")
	{
		Engine::GetModule<OneLogger>().Warning("Failed to load string from language <" + languageFile + ", " + std::to_string(id) + ">", __FILE__, __LINE__);
		PrimitiveSaveable<Core::String>& strR = stringList.request(fallbackLanguage, id);
	}
	if (strR.getValue() == "")
	{
		Engine::GetModule<OneLogger>().Error("Failed to load string from language fallback <" + fallbackLanguage + ", " + std::to_string(id) + ">", __FILE__, __LINE__);
		return "### Err Loading String ###" + languageFile + "###" + fallbackLanguage + "###" + std::to_string(id) + "###";
	}
	return strR.getValue();
}

sf::Text Language::getText(size_t id, size_t charSize)
{
	Core::String s = getString(id);
	return sf::Text(s, m_font, charSize);
}