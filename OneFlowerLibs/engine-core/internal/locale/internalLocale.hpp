#pragma once

#include <functional>

#include <asset/requestor.hpp>

#include <locale/localeSettings.hpp>

namespace of::locale
{

	struct Locale
	{
		Locale();
		Locale& operator=(const Locale& other) = delete;
		// this vector goes into requestor
		std::vector<of::common::String> selectedLang;
		std::vector<of::common::String> allLanguages;
		of::asset::Requestor languageRequestor;
		std::function<void(const of::common::String& font)> localeChangedHook;
		std::shared_ptr<LocaleSettings> localeSettings;
	};

	void init();
	void shutdown();

	void setLocaleChangedHook(std::function<void(const of::common::String& font)> hook);

	Locale& get();

}