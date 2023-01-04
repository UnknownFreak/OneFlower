#include "Inventory.hpp"
#include <Object/GameObject.hpp>

//of::common::uuid of::object::component::IBase<of::object::component::Inventory>::typeID;
//of::common::String of::object::component::IBase<of::object::component::Inventory>::componentName = "Inventory";

namespace of::object::component
{
	void Inventory::onMessage(const of::object::messaging::Message&)
	{
	}

	void Inventory::equipWeapon(std::shared_ptr<Items::Base>& item, const bool& offhand)
	{
		auto theWeapon = std::dynamic_pointer_cast<Items::Weapon>(item);
		if (theWeapon->isTwoHanded)
		{
			mainHand = theWeapon;
			offHand.reset();
		}
		else
		{
			if (offhand)
				offHand = theWeapon;
			else
				mainHand = theWeapon;
		}
	}

	void Inventory::equipArmor(std::shared_ptr<Items::Base>& item)
	{
		auto theArmor = std::dynamic_pointer_cast<Items::Armor>(item);
		if (theArmor->armorType == Enums::ArmorType::Head)
			swap(helm, theArmor);
		else if (theArmor->armorType == Enums::ArmorType::Shoulder)
			swap(shoulder, theArmor);
		else if (theArmor->armorType == Enums::ArmorType::Gloves)
			swap(shoulder, theArmor);
		else if (theArmor->armorType == Enums::ArmorType::Chest)
			swap(chest, theArmor);
		else if (theArmor->armorType == Enums::ArmorType::Leggings)
			swap(leggings, theArmor);
		else if (theArmor->armorType == Enums::ArmorType::Boot)
			swap(boots, theArmor);
		else if (theArmor->armorType == Enums::ArmorType::Cape)
			swap(cape, theArmor);
	}

	void Inventory::equipAmmo(std::shared_ptr<Items::Base>& theAmmo)
	{
		ammo = theAmmo;
	}

	void Inventory::equipTrinket(std::shared_ptr<Items::Base>& item, const bool& secondary)
	{
		auto theTrinket = std::dynamic_pointer_cast<Items::Trinket>(item);
		if (theTrinket->trinketType == Enums::TrinketType::Amulet)
		{
			swap(amulet, theTrinket);
		}
		else if (theTrinket->trinketType == Enums::TrinketType::Accessory)
		{
			if (secondary)
				swap(accessory2, theTrinket);
			else
				swap(accessory, theTrinket);
		}
		else if (theTrinket->trinketType == Enums::TrinketType::Ring)
		{
			if (secondary)
				swap(ring2, theTrinket);
			else
				swap(ring, theTrinket);
		}
	}

	void Inventory::equipItem(std::shared_ptr<Items::Base>& item, const bool& offhand)
	{
		if (item->type == Enums::ItemType::Weapon)
		{
			equipWeapon(item, offhand);
		}
		else if (item->type == Enums::ItemType::Armor)
		{
			equipArmor(item);
		}
		else if (item->type == Enums::ItemType::Ammo)
		{
			equipAmmo(item);
		}
		else if (item->type == Enums::ItemType::Trinket)
		{
			equipTrinket(item, offhand);
		}
	}

	void Inventory::addItem(std::shared_ptr<Items::Base>& item, const size_t& stackSize)
	{
		item;
		stackSize;
		//itemList.push_back(item); 
		//Engine::Get<Questing>().onItemPickUp(findItem(item), findItemStack(item))
	}

	void Inventory::removeItem(std::shared_ptr<Items::Base>& item, const size_t& stackSize)
	{
		item;
		stackSize;
		//itemList.push_back(item); 
		//Engine::Get<Questing>().onItemRemoved(findItem(item), findItemStack(item))
	}

	size_t Inventory::getItemStack(const of::file::FileId& itemId)
	{
		auto result = std::find_if(itemList.begin(), itemList.end(), [&itemId](const std::shared_ptr<Items::Base>& b) { return b->getModfile() == itemId; });
		if (result == itemList.end())
			return 0;
		return result->get()->stackSize;
	}

	void Inventory::onCollision(GameObject*)
	{
	}

	void Inventory::Update()
	{
	}

	void Inventory::Simulate(const float&)
	{
	}

	void Inventory::onDeath()
	{
	}
}