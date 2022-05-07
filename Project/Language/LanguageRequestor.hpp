#ifndef LanguageRequsetor_HPP
#define LanguageRequsetor_HPP

#include <Interfaces/IRequestable.hpp>

//TODO:
//#include <swizzle/font?>

#include "LanguageHeader.hpp"
#include "TranslationString.hpp"


namespace Language
{
	class LanguageRequestor : public Interfaces::IRequestable
	{
		
		Core::String fallbackLanguage;
		Core::String selectedLanguage;

		typedef Core::String FileName;
		typedef Core::String LanguageName;

		std::vector<FileName> allLanguageFiles;
		std::vector<LanguageName> languageNames;

		std::map<std::tuple<LanguageName, Core::uuid>, FileName> mappedLanguageIds;

		std::map<Core::uuid, Core::String> requestedStrings;

//#if defined _EDITOR_ || _UNITTESTS_
	public:
//#endif
		std::map<FileName, TranslationString> languages;
	private:

		void resolvePatchedLanguages();
		void resolvePatchedLanguages(const std::map<Core::String, std::vector<Core::uuid>>& ref, const Core::String& fileName);

#if defined _EDITOR_ || _UNITTESTS_
	public:
		void addLanguage(const FileName & language, const Core::String& fontName);

		void addString(const LanguageName& language, const Core::uuid& id, const Core::String& value, const FileName& languageFile, const bool& isPatch=false);
	private:
#endif
		void reloadStrings();

		void loadFont();

		void archiveLoad();
		void archiveSave() const;
	public:

#if defined _UNITTESTS_
		inline void clear() {
			requestedStrings.clear();
			allLanguageFiles.clear();
			languageNames.clear();
		}
#endif

		std::vector<Core::String>& getLanguages();

		Core::String& getString(const Core::uuid& id);
		
		//const sf::Font& getCurrentFont() const;

		void setLanguage(const LanguageName& language);

		LanguageRequestor();

		void load();


		virtual Interfaces::TypeInfo getTrait() const override;

		template<class Archive>
		void load(Archive& ar)
		{
			ar(allLanguageFiles);
			ar(languageNames);
			archiveLoad();
			resolvePatchedLanguages();
		}

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(allLanguageFiles);
			ar(languageNames);
			archiveSave();
		}
	};
}

#endif