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
		
		of::common::String fallbackLanguage;
		of::common::String selectedLanguage;

		typedef of::common::String FileName;
		typedef of::common::String LanguageName;

		std::vector<FileName> allLanguageFiles;
		std::vector<LanguageName> languageNames;

		std::map<std::tuple<LanguageName, of::common::uuid>, FileName> mappedLanguageIds;

		std::map<of::common::uuid, of::common::String> requestedStrings;

//#if defined _EDITOR_ || _UNITTESTS_
	public:
//#endif
		std::map<FileName, TranslationString> languages;
	private:

		void resolvePatchedLanguages();
		void resolvePatchedLanguages(const std::map<of::common::String, std::vector<of::common::uuid>>& ref, const of::common::String& fileName);

#if defined _EDITOR_ || _UNITTESTS_
	public:
		void addLanguage(const FileName & language, const of::common::String& fontName);

		void addString(const LanguageName& language, const of::common::uuid& id, const of::common::String& value, const FileName& languageFile, const bool& isPatch=false);
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

		std::vector<of::common::String>& getLanguages();

		of::common::String& getString(const of::common::uuid& id);
		
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