#pragma once

#include <map>

namespace of::locale
{
	class LanguageRequestor;

	namespace utils
	{

		void loadLanguages(const std::vector<common::String>& languageFiles, std::map<common::String, TranslationStringContainer>&);

		void saveLanguages(const LanguageRequestor& lr);
		void saveLanguageFile(const common::String& filename, TranslationStringContainer& saveable);
	}

}
