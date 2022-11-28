#include <locale/LanguageRequestor.hpp>
#include "util/langaugeSaverUtil.hpp"


#include <algorithm>
#include <module/ModuleManager.hpp>

#include <utils/os/ListDir.hpp>

of::common::uuid of::file::archive::Trait<of::locale::LanguageRequestor>::typeId = of::common::uuid("3a605c27-d5c2-46e5-91bf-9135e02a7437");

CEREAL_REGISTER_TYPE(of::locale::LanguageRequestor);
CEREAL_REGISTER_TYPE(of::locale::TranslationStringContainer);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, of::locale::LanguageRequestor);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, of::locale::TranslationStringContainer);

namespace of::locale
{

	void LanguageRequestor::resolvePatchedLanguages()
	{
		mappedLanguageIds.clear();
		for (std::pair<FileName, TranslationStringContainer> pair : languages)
		{
			resolvePatchedLanguages(pair.second.getHeader().addedIds, pair.first);
			resolvePatchedLanguages(pair.second.getHeader().moddedIds, pair.first);
		}
	}

	void LanguageRequestor::resolvePatchedLanguages(const std::map<common::String, std::vector<common::uuid>>& ref, const common::String& fileName)
	{
		for(std::pair<LanguageName, std::vector<common::uuid>> pair2 : ref)
		{
			if (std::find(languageNames.begin(), languageNames.end(), pair2.first) == languageNames.end())
			{
				languageNames.push_back(pair2.first);
			}
			for (common::uuid& i : pair2.second)
			{
				mappedLanguageIds[{pair2.first, i}] = fileName;
			}
		}
	}

#if defined _EDITOR_ || _UNITTESTS_

	void LanguageRequestor::addLanguage(const FileName & language, const common::String & fontName)
	{
		if (std::find(allLanguageFiles.begin(), allLanguageFiles.end(), language) == allLanguageFiles.end())
		{
			allLanguageFiles.push_back(language);
			languages.emplace(language, TranslationString(language, fontName));
		}
	}

	void LanguageRequestor::addString(const LanguageName & language, const common::uuid & id, const common::String & value,
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
			it.second.first = languages[f].getPrimitive(selectedLanguage, it.first).getValue();
			it.second.second = true;
		}
	}

	std::vector<common::String>& LanguageRequestor::getLanguages()
	{
		return languageNames;
	}

	common::String LanguageRequestor::getString(const common::uuid & id)
	{
		if (requestedStrings.find(id) == requestedStrings.end()) 
		{
			FileName f = mappedLanguageIds[{selectedLanguage, id}];
			requestedStrings[id].first = languages[f].getPrimitive(selectedLanguage, id).getValue();
			requestedStrings[id].second = false;
		}
		return requestedStrings[id].first;
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
		of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("locale::LanguageRequestor").Error("Unable to set language [" + language + "]");
	}

	LanguageRequestor::LanguageRequestor() : Requestable(common::Builtin, common::uuid::nil(), OneVersion(1, 0, 0), file::ObjectType::Language)
	{
		load();
	}

	void LanguageRequestor::load()
	{
#if defined _UNITTESTS_
		clear();
#endif
		allLanguageFiles = of::os::listDirectory(common::langPath, ".lang", false);
		languages = utils::loadLanguages(allLanguageFiles);
		resolvePatchedLanguages();
	}

	void LanguageRequestor::archiveLoad()
	{
		languages = utils::loadLanguages(allLanguageFiles);
	}

	void LanguageRequestor::archiveSave() const
	{
		utils::saveLanguages(*this);
	}

	bool& locale::LanguageRequestor::isTranslationChanged(const common::uuid& translationId)
	{
		return requestedStrings[translationId].second;
	}

	void locale::LanguageRequestor::translationChanged(const common::uuid& translationId)
	{
		requestedStrings[translationId].second = false;
	}

	file::archive::TypeInfo LanguageRequestor::getTrait() const
	{
		return { of::file::archive::Trait<LanguageRequestor>::typeId };
	}

	void LanguageRequestor::loadFont()
	{
		const common::String path = common::fontPath + languages[selectedLanguage].getFontName();
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
