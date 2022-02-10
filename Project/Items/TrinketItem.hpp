#ifndef TrinketItem_Hpp
#define TrinketItem_Hpp

#include "StatChangingItem.hpp"
#include <Helpers/Enum/TrinketType.hpp>
#include <Combat/Modifier.hpp>


namespace Items
{
	class Trinket : public Items::StatChangingItem
	{

	public:
		Enums::TrinketType trinketType;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<StatChangingItem>(this));
			ar(trinketType);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<StatChangingItem>(this));
			ar(trinketType);
		}
	};
}

#endif