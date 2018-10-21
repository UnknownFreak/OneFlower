#include "Language.hpp"
#include <fstream>
#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Asset/AssetManagerCore.hpp>

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
	PrimitiveSaveable<Core::String>& langStr = stringList.request(language, id);
	if (langStr.getValue() == "")
	{
		Engine::GetModule<OneLogger>().Warning("Failed to load string from language <" + language + ", " + std::to_string(id) + ">", __FILE__, __LINE__);
		PrimitiveSaveable<Core::String>& strR = stringList.request(fallbackLanguage, id);
	}
	if (langStr.getValue() == "")
	{
		Engine::GetModule<OneLogger>().Error("Failed to load string from language fallback <" + fallbackLanguage + ", " + std::to_string(id) + ">", __FILE__, __LINE__);
		return "### Err Loading String ###" + language + "###" + fallbackLanguage + "###" + std::to_string(id) + "###";
	}
	return langStr.getValue();
}

sf::Text Language::getText(size_t id, size_t charSize)
{
	return sf::Text(getString(id), m_font, charSize);
}

void Language::Patch(const IPatch & other)
{
	const Language& patcher = (Language&)other;
	for each (std::pair<std::string, size_t> var in patcher.languageFiles)
		if (languageFiles.find(var.first) != languageFiles.end())
			languageFiles.insert({ var.first, 0 });

	stringList.fileLoadOrder = languageFiles;
}
