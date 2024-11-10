#include <locale/internalLocale.hpp>
#include <locale/locale.hpp>

#include <locale/localeString.hpp>

#include <engine/paths.hpp>
#include <engine/settings.hpp>

#include <utils/os/ListDir.hpp>

static of::locale::Locale* g_locale = nullptr;

namespace of::locale
{

	Locale::Locale() : selectedLang(), allLanguages(), languageRequestor(of::engine::path::locale, selectedLang)
	{
		selectedLang.emplace_back(of::settings::get().getLocale());
		allLanguages = of::os::listDirectory(of::engine::path::locale, ".lang", false);
	}

	static void loadLocaleSettings(const of::common::String& locale)
	{
		g_locale->localeSettings = g_locale->languageRequestor.requestShared<LocaleSettings>(asset::AssetId{ locale, of::common::uuid::nil() });
		if(g_locale->localeChangedHook.operator bool())
			g_locale->localeChangedHook(g_locale->localeSettings->fontName);
	}

	void init()
	{
		if (g_locale == nullptr)
		{
			g_locale = new Locale();
		}
	}


	void shutdown()
	{
		if (g_locale)
		{
			delete g_locale;
			g_locale = nullptr;
		}
	}

	Locale& get()
	{
		return *g_locale;
	}

	void setLocaleChangedHook(std::function<void(const of::common::String& font)> hook)
	{
		g_locale->localeChangedHook = hook;
		loadLocaleSettings(g_locale->selectedLang[0]);
	}

	void setActiveLocale(const of::common::String& newLocale)
	{
		g_locale->selectedLang.clear();
		g_locale->selectedLang.emplace_back(newLocale);
		loadLocaleSettings(newLocale);
	}

	of::common::String getLocaleString(const of::common::uuid& stringId)
	{
		const asset::AssetId id(g_locale->selectedLang[0], stringId);
		auto* ptr = g_locale->languageRequestor.request<LocaleString>(id);
		if (ptr)
		{
			return ptr->value;
		}
		logger::get().getLogger("of::locale").Error("Unable to get locale string [" + id(true) + "]");
		return "E_NOT_FOUND";
	}
}