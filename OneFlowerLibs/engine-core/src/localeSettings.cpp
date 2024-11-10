#include <locale/localeString.hpp>
#include <locale/localeSettings.hpp>

of::common::uuid of::asset::Trait<of::locale::LocaleSettings>::typeId = of::common::uuid("3a605c27-d5c2-46e5-91bf-9135e02a7437");

namespace of::locale
{
	asset::TypeInfo LocaleSettings::getTrait() const
	{
		return { asset::Trait<LocaleSettings>::typeId };
	}
}