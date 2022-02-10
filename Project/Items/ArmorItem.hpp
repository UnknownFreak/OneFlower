#ifndef ArmorItem_HPP
#define ArmorItem_HPP

#include "StatChangingItem.hpp"
#include <Helpers/Enum/ArmorType.hpp>
#include <Combat/Modifier.hpp>

namespace Items
{

	class Armor : public Items::StatChangingItem
	{
	public:
		Enums::ArmorType armorType;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<StatChangingItem>(this));
			ar(armorType);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<StatChangingItem>(this));
			ar(armorType);
		}
	};
}

#endif