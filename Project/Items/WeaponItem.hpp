#ifndef WeaponItem_Hpp
#define WeaponItem_Hpp

#include "StatChangingItem.hpp"
#include <Helpers/Enum/WeaponType.hpp>
#include <Combat/Modifier.hpp>
#include <Graphics/Model/IModel.hpp>

class Prefab;

namespace Items
{
	class Weapon : public Items::StatChangingItem
	{
		Prefab* mesh;

		void loadModel();

	public:
		Enums::WeaponType weaponType;
		double weaponStrength;
		ModFileUUIDHelper modelId;
		bool isTwoHanded;
		bool requireAmmoToUse;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<StatChangingItem>(this));
			ar(weaponStrength);
			ar(modelId);
			ar(isTwoHanded);
			ar(weaponType);
			ar(requireAmmoToUse);
		}
		
		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Base>(StatChangingItem));
			ar(weaponStrength);
			ar(modelId);
			ar(isTwoHanded);
			ar(weaponType);
			ar(requireAmmoToUse);
			loadModel();
		}
	};
}

#endif