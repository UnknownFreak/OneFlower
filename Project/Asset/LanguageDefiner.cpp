#include "Language.hpp"
#include <fstream>
#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Asset/AssetManagerCore.hpp>
#include <Core/uuid.hpp>

void Language::loadFont(const Core::String & name)
{
	Core::String path = "Data\\Font\\" + name;
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

Language::Language() : Language("Arial.ttf")
{
}

Language::Language(Core::String fontName) : fontName(fontName), m_font(), stringList(DatabaseIndex::ObjectTypeEnum::PrimitiveString, "Data\\Lang\\"), IRequestable("BUILTIN", Core::uuid::nil(), OneVersion(1,0,0))
{
	loadFont(fontName);
}

Language::Language(const Language & copy) : IRequestable(copy), stringList(DatabaseIndex::ObjectTypeEnum::PrimitiveString, "Data\\Lang\\")
{
	fallbackLanguage = copy.fallbackLanguage;
	selectedLanguage = copy.selectedLanguage;
	availableLanguages = copy.availableLanguages;
	languageFiles = copy.languageFiles;
	fontName = copy.fontName;
	m_font = copy.m_font;
}

Language & Language::operator=(const Language & right)
{
	if (this == &right)
		return *this;

	ID = right.ID;
	fromMod = right.fromMod;
	mode = right.mode;
	objectVersion = right.objectVersion;

	fallbackLanguage = right.fallbackLanguage;
	selectedLanguage = right.selectedLanguage;
	availableLanguages = right.availableLanguages;
	languageFiles = right.languageFiles;
	m_font = right.m_font;
	fontName = right.fontName;

	return *this;
}

sf::Font & Language::getFont()
{
	return m_font;
}

Core::String Language::getString(const Core::uuid& id)
{
	PrimitiveSaveable<Core::String>& langStr = stringList.request(selectedLanguage, id);
	if (langStr.getValue() == "")
	{
		Engine::GetModule<OneLogger>().Warning("Failed to load string from selectedLanguage <" + selectedLanguage + ", " + id.to_string() + ">", __FILE__, __LINE__);
		langStr = stringList.request(fallbackLanguage, id);
	}
	if (langStr.getValue() == "")
	{
		Engine::GetModule<OneLogger>().Error("Failed to load string from selectedLanguage fallback <" + fallbackLanguage + ", " + id.to_string() + ">", __FILE__, __LINE__);
		return "### Err Loading String ###" + selectedLanguage + "###" + fallbackLanguage + "###" + id.to_string() + "###";
	}
	return langStr.getValue();
}

sf::Text Language::getText(const Core::uuid& id, size_t charSize)
{
	return sf::Text(getString(id), m_font, charSize);
}

void Language::Patch(const IPatch & other)
{
	//const Language& patcher = (Language&)other;
	//for each (std::pair<std::string, size_t> var in patcher.languageFiles)
	//	if (languageFiles.find(var.first) == languageFiles.end())
	//		languageFiles.insert({ var.first, 0 });
	//
	//for each (Core::String var in patcher.availableLanguages)
	//	if (std::find(availableLanguages.begin(), availableLanguages.end(), var) == availableLanguages.end())
	//		availableLanguages.push_back(var);
	//
	//stringList.fileLoadOrder = languageFiles;
}

