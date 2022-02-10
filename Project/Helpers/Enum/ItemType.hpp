#ifndef ItemType_HPP
#define ItemType_HPP

#include <Helpers/uuid.hpp>

namespace Enums
{
	enum class ItemType
	{
		Armor,
		Bag,
		Trinket,
		
		Ammo,
		Weapon,

		CraftingMaterial,
		Quest,
		Junk,

		Unknown = 255
	};

	inline Core::uuid getId(const ItemType& type)
	{
		switch (type)
		{
		case ItemType::Ammo:
			return Core::uuid("372f8c1c-54b1-4809-971e-ff6f86057012");
		case ItemType::Armor:
			return Core::uuid("5ea8daab-da7e-4e3e-8c6c-16ccf279299c");
		case ItemType::Bag:
			return Core::uuid("173e8f6e-c0c0-41a8-aab7-8da2d1997b4d");
		case ItemType::Trinket:
			return Core::uuid("10e80941-118f-4c7d-8382-f0ce89d66ca3");
		case ItemType::Weapon:
			return Core::uuid("1d070607-effa-4ce0-86f7-4038e1ab9694");
		case ItemType::CraftingMaterial:
			return Core::uuid("ada7f9a0-d626-48d2-82e4-985924243074");
		case ItemType::Quest:
			return Core::uuid("2864b000-766f-477f-a9ef-63fe9605bdc3");
		case ItemType::Junk:
			return Core::uuid("fc644d86-f40b-4ee7-a8da-ce4c218e3ebd");
		default:
			break;
		}
		return Core::uuid::nil();
	}
}


#endif