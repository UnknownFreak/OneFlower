#include <locale/Translatable.hpp>

#include <locale/LanguageRequestor.hpp>
#include <asset/asset.hpp>

namespace of::locale
{

	static of::locale::LanguageRequestor& get()
	{
		static LanguageRequestor l;
		return l;
	}

	Translatable::Translatable()
	{
	}

	Translatable::Translatable(const common::uuid& translationId) : translationId(translationId)
	{
		load();
	}

	void Translatable::load()
	{
		
		value = get().getString(translationId);
	}

	void Translatable::reloadIfNeeded()
	{
		auto& requestor = get();

		if (requestor.isTranslationChanged(translationId))
		{
			load();
			requestor.translationChanged(translationId);
		}
	}
}