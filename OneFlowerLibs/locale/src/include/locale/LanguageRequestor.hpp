#ifndef LanguageRequsetor_HPP
#define LanguageRequsetor_HPP

#include <file/archive/Requestable.hpp>

//TODO:
//#include <swizzle/font?>

#include "TranslationStringContainer.hpp"


namespace of::locale
{
	class LanguageRequestor : public file::archive::Requestable
	{
		
		common::String fallbackLanguage;
		common::String selectedLanguage;

		typedef common::String FileName;
		typedef common::String LanguageName;

		std::vector<FileName> allLanguageFiles;
		std::vector<LanguageName> languageNames;

		std::map<std::tuple<LanguageName, common::uuid>, FileName> mappedLanguageIds;

		std::map<common::uuid, std::pair<common::String, bool>> requestedStrings;
		
//#if defined _EDITOR_ || _UNITTESTS_
	public:
//#endif
		std::map<FileName, TranslationStringContainer> languages;
	private:

		void resolvePatchedLanguages();
		void resolvePatchedLanguages(const std::map<common::String, std::vector<common::uuid>>& ref, const common::String& fileName);

#if defined _EDITOR_ || _UNITTESTS_
	public:
		void addLanguage(const FileName & language, const common::String& fontName);

		void addString(const LanguageName& language, const common::uuid& id, const common::String& value, const FileName& languageFile, const bool& isPatch=false);
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

		std::vector<common::String>& getLanguages();

		common::String getString(const common::uuid& id);
		
		//const sf::Font& getCurrentFont() const;

		void setLanguage(const LanguageName& language);

		LanguageRequestor();

		void load();

		bool& isTranslationChanged(const common::uuid& translationId);
		void translationChanged(const common::uuid& translationId);

		virtual file::archive::TypeInfo getTrait() const override;

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