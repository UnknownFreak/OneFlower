#include "InventoryComponent.hpp"
#include "GameObject.h"
#include "../Item.hpp"
const unsigned int IBaseComponent<InventoryComponent>::typeID = 1008;
std::string IBaseComponent<InventoryComponent>::componentName = "InventoryComponent";
InventoryComponent::InventoryComponent() : maxItems(50), maxWeight(150), items()
{

}

void InventoryComponent::addItem(Item* item)
{
	Item* tmp = 0;
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); ++it)
	{
		tmp = *it;
		if (tmp->ID == item->ID)
		{

		}
	}
}

void InventoryComponent::attachOn(GameObject* attachTo)
{
	BaseComponent::attachOn(attachTo);
	REGISTER_EDITOR_VARIABLE(int, maxItems, MaxItems);
	REGISTER_EDITOR_VARIABLE(int, maxWeight, MaxWeight);
}