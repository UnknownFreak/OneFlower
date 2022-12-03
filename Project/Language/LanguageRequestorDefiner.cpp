#include "LanguageRequestor.hpp"
#include <file/Handler.hpp>
#include <algorithm>
#include <utils/os/ListDir.hpp>


of::common::uuid of::file::archive::Trait<Language::LanguageRequestor>::typeId = of::common::uuid("3a605c27-d5c2-46e5-91bf-9135e02a7437");
CEREAL_REGISTER_TYPE(Language::LanguageRequestor);
CEREAL_REGISTER_TYPE(Language::TranslationString);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Language::LanguageRequestor);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Language::TranslationString);

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

	void LanguageRequestor::resolvePatchedLanguages(const std::map<of::common::String, std::vector<of::common::uuid>>& ref, const of::common::String& fileName)
	{
		for(std::pair<LanguageName, std::vector<of::common::uuid>> pair2 : ref)
		{
			if (std::find(languageNames.begin(), languageNames.end(), pair2.first) == languageNames.end())
			{
				languageNames.push_back(pair2.first);
			}
			for (of::common::uuid& i : pair2.second)
			{
				mappedLanguageIds[{pair2.first, i}] = fileName;
			}
		}
	}

#if defined _EDITOR_ || _UNITTESTS_

	void LanguageRequestor::addLanguage(const FileName & language, const of::common::String & fontName)
	{
		if (std::find(allLanguageFiles.begin(), allLanguageFiles.end(), language) == allLanguageFiles.end())
		{
			allLanguageFiles.push_back(language);
			languages.emplace(language, TranslationString(language, fontName));
		}
	}

	void LanguageRequestor::addString(const LanguageName & language, const of::common::uuid & id, const of::common::String & value,
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

	std::vector<of::common::String>& LanguageRequestor::getLanguages()
	{
		return languageNames;
	}

	of::common::String& LanguageRequestor::getString(const of::common::uuid & id)
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
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Language::LanguageRequestor").Error("Unable to set language [" + language + "]");
	}

	LanguageRequestor::LanguageRequestor() : Requestable(of::common::Builtin, of::common::uuid::nil(), OneVersion(1, 0, 0), of::file::ObjectType::Language)
	{
		load();
	}

	void LanguageRequestor::load()
	{
#if defined _UNITTESTS_
		clear();
#endif
		allLanguageFiles = of::os::listDirectory(of::common::langPath, ".lang", false);
		//languages = of::engine::GetModule<of::file::Handler>().loadLanguages(allLanguageFiles);
		resolvePatchedLanguages();
	}

	void LanguageRequestor::archiveLoad()
	{
		//languages = of::engine::GetModule<of::file::Handler>().loadLanguages(allLanguageFiles);
	}

	void LanguageRequestor::archiveSave() const
	{
		//of::engine::GetModule<of::file::Handler>().saveLanguages(*this);
	}

	of::file::archive::TypeInfo LanguageRequestor::getTrait() const
	{
		return { of::file::archive::Trait<LanguageRequestor>::typeId };
	}

	void LanguageRequestor::loadFont()
	{
		const of::common::String path = of::common::fontPath + languages[selectedLanguage].getFontName();
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
