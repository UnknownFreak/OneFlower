#include "EquipmentComponent.hpp"
#include "../Item/Armor.hpp"

const unsigned int IBaseComponent<EquipmentComponent>::typeID = 1013;
std::string IBaseComponent<EquipmentComponent>::componentName = "EquipmentComponent";

EquipmentComponent::EquipmentComponent() : helm(NULL), chest(NULL), gloves(NULL), leggings(NULL), boots(NULL)
{

}

Item* EquipmentComponent::equipArmor(Item* item)
{
	if (item)
		if (item->tag != Item::armor)
			return false;
		else
		{
			Armor* arm = (Armor*)item;
			if (arm->armorType == "Helm")
			{
				Item* tmp = helm;
				helm = arm;
				return tmp;
			}
			else if (arm->armorType == "Chest")
			{
				Item* tmp = chest;
				chest = arm;
				return tmp;
			}
			else if (arm->armorType == "Gloves")
			{
				Item* tmp = gloves;
				gloves = arm;
				return tmp;
			}
			else if (arm->armorType == "Leggings")
			{
				Item* tmp = leggings;
				leggings = arm;
				return tmp;
			}
			else if (arm->armorType == "Boots")
			{
				Item* tmp = boots;
				boots = arm;
				return tmp;
			}
			else
				return NULL;
 		}
	return NULL;
}