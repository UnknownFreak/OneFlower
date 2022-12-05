#include <locale/Translatable.hpp>

#include <file/Handler.hpp>
#include <locale/LanguageRequestor.hpp>

namespace of::locale
{

	of::locale::LanguageRequestor& get()
	{
		auto& handler = of::engine::GetModule<of::file::Handler>();
		return *handler.archive.request<of::locale::LanguageRequestor>({ common::Builtin, common::uuid::nil() }, true);
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