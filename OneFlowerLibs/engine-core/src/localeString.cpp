#include <locale/localeString.hpp>

of::common::uuid of::asset::Trait<of::locale::LocaleString>::typeId = of::common::uuid("a36a1fa2-4fa8-4384-a4cf-f8910e03b539");

namespace of::locale
{
	asset::TypeInfo LocaleString::getTrait() const
	{
		return { asset::Trait<LocaleString>::typeId };
	}
}