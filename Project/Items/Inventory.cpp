#include "Inventory.hpp"
#include <Object/GameObject.hpp>

Enums::ComponentType Component::IBase<Component::Inventory>::typeID = Enums::ComponentType::Inventory;
Core::String Component::IBase<Component::Inventory>::componentName = "Inventory";

void Component::Inventory::equipWeapon(std::shared_ptr<Items::Base>& item, const bool& offhand)
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

void Component::Inventory::equipArmor(std::shared_ptr<Items::Base>& item)
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

void Component::Inventory::equipAmmo(std::shared_ptr<Items::Base>& theAmmo)
{
	ammo = theAmmo;
}

void Component::Inventory::equipTrinket(std::shared_ptr<Items::Base>& item, const bool& secondary)
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

void Component::Inventory::equipItem(std::shared_ptr<Items::Base>& item, const bool& offhand)
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

void Component::Inventory::addItem(std::shared_ptr<Items::Base>& item, const size_t& stackSize)
{
	item;
	stackSize;
	//itemList.push_back(item); 
	//Engine::Get<Questing>().onItemPickUp(findItem(item), findItemStack(item))
}

void Component::Inventory::removeItem(std::shared_ptr<Items::Base>& item, const size_t& stackSize)
{
	item;
	stackSize;
	//itemList.push_back(item); 
	//Engine::Get<Questing>().onItemRemoved(findItem(item), findItemStack(item))
}

size_t Component::Inventory::getItemStack(const ModFileUUIDHelper& itemId)
{
	auto result = std::find_if(itemList.begin(), itemList.end(), [&itemId](const std::shared_ptr<Items::Base>& b) { return b->getModfile() == itemId; });
	if (result == itemList.end())
		return 0;
	return result->get()->stackSize;
}

void Component::Inventory::onCollision(Interfaces::ICollider* )
{
}

void Component::Inventory::Update()
{
}

void Component::Inventory::Simulate(const float& )
{
}

void Component::Inventory::onDeath()
{
}
