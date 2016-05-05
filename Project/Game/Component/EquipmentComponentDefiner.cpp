#include "EquipmentComponent.hpp"
#include "../Item/Armor.hpp"

const unsigned int IBaseComponent<EquipmentComponent>::typeID = 1013;
std::string IBaseComponent<EquipmentComponent>::componentName = "EquipmentComponent";

EquipmentComponent::EquipmentComponent(): helm(NULL),chest(NULL),gloves(NULL),leggings(NULL),boots(NULL)
{
}

Items::Item* EquipmentComponent::equipArmor(Items::Item* item)
{
	if(item)
		if(item->getTag() != Items::Item::armor)
			return false;
		else
		{
			Items::Armor* arm = (Items::Armor*)item;
			if(arm->armorType == "Helm")
			{
				Items::Item* tmp = helm;
				helm = arm;
				return tmp;
			}
			else if(arm->armorType == "Chest")
			{
				Items::Item* tmp = chest;
				chest = arm;
				return tmp;
			}
			else if(arm->armorType == "Gloves")
			{
				Items::Item* tmp = gloves;
				gloves = arm;
				return tmp;
			}
			else if(arm->armorType == "Leggings")
			{
				Items::Item* tmp = leggings;
				leggings = arm;
				return tmp;
			}
			else if(arm->armorType == "Boots")
			{
				Items::Item* tmp = boots;
				boots = arm;
				return tmp;
			}
			else
				return NULL;
		}
	return NULL;
}