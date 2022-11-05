#include "LanguageRequestor.hpp"
#include <File/Asset/Manager.hpp>
#include <algorithm>
#include <Helpers/ListDir.hpp>

Core::uuid Interfaces::Trait<Language::LanguageRequestor>::typeId = Core::uuid("3a605c27-d5c2-46e5-91bf-9135e02a7437");
CEREAL_REGISTER_TYPE(Language::LanguageRequestor);
CEREAL_REGISTER_TYPE(Language::TranslationString);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Language::LanguageRequestor);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Language::TranslationString);
namespace Language
{

	void LanguageRequestor::resolvePatchedLanguages()
	{
		mappedLanguageIds.clear();
		for (std::pair<FileName, TranslationString> pair : languages)
		{
			resolvePatchedLanguages(pair.second.getHeader().addedIds, pair.first);
			resolvePatchedLanguages(pair.second.getHeader().moddedIds, pair.first);
		}
	}

	void LanguageRequestor::resolvePatchedLanguages(const std::map<Core::String, std::vector<Core::uuid>>& ref, const Core::String& fileName)
	{
		for(std::pair<LanguageName, std::vector<Core::uuid>> pair2 : ref)
		{
			if (std::find(languageNames.begin(), languageNames.end(), pair2.first) == languageNames.end())
			{
				languageNames.push_back(pair2.first);
			}
			for (Core::uuid& i : pair2.second)
			{
				mappedLanguageIds[{pair2.first, i}] = fileName;
			}
		}
	}

#if defined _EDITOR_ || _UNITTESTS_

	void LanguageRequestor::addLanguage(const FileName & language, const Core::String & fontName)
	{
		if (std::find(allLanguageFiles.begin(), allLanguageFiles.end(), language) == allLanguageFiles.end())
		{
			allLanguageFiles.push_back(language);
			languages.emplace(language, TranslationString(language, fontName));
		}
	}

	void LanguageRequestor::addString(const LanguageName & language, const Core::uuid & id, const Core::String & value,
		const FileName& languageFile, const bool& isPatch)
	{
		if (std::find(languageNames.begin(), languageNames.end(), language) == languageNames.end())
		{
			languageNames.push_back(language);
		}
		languages[languageFile].addString(language, id, value, isPatch);
	}

#endif

	void LanguageRequestor::reloadStrings()
	{
		for (auto& it : requestedStrings)
		{
			FileName f = mappedLanguageIds[{selectedLanguage, it.first}];
			it.second = languages[f].getPrimitive(selectedLanguage, it.first).getValue();
		}
	}

	std::vector<Core::String>& LanguageRequestor::getLanguages()
	{
		return languageNames;
	}

	Core::String& LanguageRequestor::getString(const Core::uuid & id)
	{
		if (requestedStrings.find(id) == requestedStrings.end()) 
		{
			FileName f = mappedLanguageIds[{selectedLanguage, id}];
			requestedStrings[id] = languages[f].getPrimitive(selectedLanguage, id).getValue();
		}
		return requestedStrings[id];
	}

	//const sf::Font& LanguageRequestor::getCurrentFont() const
	//{
	//	return m_font;
	//}

	void LanguageRequestor::setLanguage(const LanguageName & language)
	{
		for (const LanguageName& name : languageNames)
			if (name == language)
			{
				selectedLanguage = language;
				reloadStrings();
				return;
			}
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Language::LanguageRequestor").Error("Unable to set language [" + language + "]");
	}

	LanguageRequestor::LanguageRequestor() : IRequestable(Core::Builtin, Core::uuid::nil(), OneVersion(1, 0, 0), Enums::ObjectType::Language)
	{
		load();
	}

	void LanguageRequestor::load()
	{
#if defined _UNITTESTS_
		clear();
#endif
		allLanguageFiles = Helpers::os::listDirectory(Core::langPath, ".lang", false);
		languages = Engine::GetModule<File::Asset::Manager>().loadLanguages(allLanguageFiles);
		resolvePatchedLanguages();
	}

	void LanguageRequestor::archiveLoad()
	{
		languages = Engine::GetModule<File::Asset::Manager>().loadLanguages(allLanguageFiles);
	}

	void LanguageRequestor::archiveSave() const
	{
		Engine::GetModule<File::Asset::Manager>().saveLanguages(*this);
	}

	Interfaces::TypeInfo LanguageRequestor::getTrait() const
	{
		return { Interfaces::Trait<LanguageRequestor>::typeId };
	}

	void LanguageRequestor::loadFont()
	{
		const Core::String path = Core::fontPath + languages[selectedLanguage].getFontName();
		std::ifstream i(path, std::ios::in | std::ifstream::binary);
		i.seekg(0, i.end);
		size_t len = (size_t)i.tellg();
		i.seekg(0, i.beg);
		char* data = new char[len];
		i.read(data, len);
	
		//m_font.loadFromMemory(data, len);
		delete[] data;
	}
}
