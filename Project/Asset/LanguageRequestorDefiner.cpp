#include "LanguageRequestor.hpp"
#include <Asset/AssetManagerCore.hpp>
#include <algorithm>
namespace Language
{

	void LanguageRequestor::resolvePatchedLanguages()
	{
		mappedLanguageIds.clear();
		for each (std::pair<FileName, TranslationString> pair in languages)
		{
			resolvePatchedLanguages(pair.second.getHeader().addedIds, pair.first);
			resolvePatchedLanguages(pair.second.getHeader().moddedIds, pair.first);
		}
	}

	void LanguageRequestor::resolvePatchedLanguages(const std::map<Core::String, std::vector<Core::uuid>>& ref, const Core::String& fileName)
	{
		for each(std::pair<LanguageName, std::vector<Core::uuid>> pair2 in ref)
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

	const sf::Font& LanguageRequestor::getCurrentFont() const
	{
		return m_font;
	}

	void LanguageRequestor::setLanguage(const LanguageName & language)
	{
		for each(const LanguageName& name in languageNames)
			if (name == language)
			{
				selectedLanguage = language;
				reloadStrings();
				return;
			}
		Engine::GetModule<OneLogger>().Error("Unable to set language [" + language + "]");
	}

	LanguageRequestor::LanguageRequestor() : IRequestable(Core::Builtin, Core::uuid::nil(), OneVersion(1, 0, 0))
	{
		load();
	}

	void LanguageRequestor::load()
	{
		clear();
		allLanguageFiles = listDirectory(Core::langPath, ".lang", false);
		languages = Engine::GetModule<Asset::AssetManager>().loadLanguages(allLanguageFiles);
		resolvePatchedLanguages();
	}

	void LanguageRequestor::loadFont()
	{
		const Core::String path = Core::fontPath + languages[selectedLanguage].getFontName();
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
}
