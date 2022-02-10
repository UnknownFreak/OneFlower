#ifndef StatChangingItem_Hpp
#define StatChangingItem_Hpp

#include "Item.hpp"
#include <Combat/Modifier.hpp>


namespace Items
{
	class StatChangingItem : public Items::Base
	{

	public:
		Combat::Modifier defence;
		std::vector<Combat::Modifier> attributeModifier;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Base>(this));
			ar(defence);
			ar(attributeModifier);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Base>(this));
			ar(defence);
			ar(attributeModifier);
		}
	};
}

#endif