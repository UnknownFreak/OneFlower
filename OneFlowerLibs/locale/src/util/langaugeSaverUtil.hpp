#pragma once

#include <map>

namespace of::locale
{
	class LanguageRequestor;

	namespace utils
	{

		std::map<common::String, TranslationStringContainer> loadLanguages(const std::vector<common::String>& languageFiles);

		void saveLanguages(const LanguageRequestor& lr);
		void saveLanguageFile(const common::String& filename, TranslationStringContainer& saveable);
	}

}
