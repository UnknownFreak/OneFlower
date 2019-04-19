#ifndef LanguageRequsetor_HPP
#define LanguageRequsetor_HPP

#include <Asset/IRequestable.hpp>
#include <Core/EngineModule/ListDir.hpp>
#include <Core/EngineModule/EngineModuleManager.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "LanguageHeader.hpp"
#include "Language.hpp"


namespace Language
{
	class LanguageRequestor : public IRequestable
	{
		
		Core::String fallbackLanguage;
		Core::String selectedLanguage;

		sf::Font m_font;

		typedef Core::String FileName;
		typedef Core::String LanguageName;

		std::vector<FileName> allLanguageFiles;
		std::vector<LanguageName> languageNames;

		std::map<std::tuple<LanguageName, size_t>, FileName> mappedLanguageIds;

		std::map<size_t, Core::String> requestedStrings;

#if defined _EDITOR_ || _UNITTESTS_
	public:
#endif
		std::map<FileName, TranslationString> languages;
	private:

		void resolvePatchedLanguages();
		void resolvePatchedLanguages(const std::map<Core::String, std::vector<size_t>>& ref, const Core::String& fileName);

#if defined _EDITOR_ || _UNITTESTS_
	public:
		void addLanguage(const FileName & language, const Core::String& fontName);

		void addString(const LanguageName& language, const size_t& id, const Core::String& value, const FileName& languageFile, const bool& isPatch=false);
	private:
#endif
		void reloadStrings();

		void loadFont();

	public:

#if defined _UNITTESTS_
		inline void clear() {
			requestedStrings.clear();
			allLanguageFiles.clear();
			languageNames.clear();
		}
#endif

		std::vector<Core::String>& getLanguages();

		Core::String& getString(const size_t& id);
		
		const sf::Font& getCurrentFont() const;

		void setLanguage(const LanguageName& language);

		LanguageRequestor();

		void load();


		template<class Archive>
		void load(Archive& ar)
		{
			ar(allLanguageFiles);
			ar(languageNames);
			languages = Engine::GetModule<Asset::AssetManager>().loadLanguages(allLanguageFiles);
			resolvePatchedLanguages();
		}

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(allLanguageFiles);
			ar(languageNames);
			Engine::GetModule<Asset::AssetManager>().saveLanguages(*this);
		}
	};
}

#endif