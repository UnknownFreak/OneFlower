#include <locale/StoredTranslatable.hpp>

of::common::uuid of::asset::Trait<of::locale::StoredTranslatable>::typeId = of::common::uuid("82fa0362-3917-4a70-a6d1-44a0b8ebf92e");

namespace of::locale
{
    common::String StoredTranslatable::getValue() const
    {
        return value;
    }

    of::asset::TypeInfo StoredTranslatable::getTrait() const
    {
        return { asset::Trait<StoredTranslatable>::typeId };
    }
}
