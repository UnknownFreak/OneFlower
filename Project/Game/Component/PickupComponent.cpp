#include "PickupComponent.hpp"
#include "../Item/Item.hpp"
#include "../Item/Armor.hpp"
#include "../Item/Bag.hpp"
#include "../LoadAndSave/LoadAndSave.hpp"
#include "InventoryComponent.hpp"
#include "../../Engine.hpp"
const unsigned int IBaseComponent<PickupComponent>::typeID = 1010;
std::string IBaseComponent<PickupComponent>::componentName = "PickupComponent";

PickupComponent::PickupComponent(unsigned int itemID,int stackSize): itemID(itemID),stackSize(stackSize)
{
}

void PickupComponent::attachOn(GameObject* attachTo)
{
	BaseComponent::attachOn(attachTo);
	REGISTER_EDITOR_VARIABLE(int,stackSize,StackSize);
	REGISTER_EDITOR_VARIABLE(bool,pickedUp,PickedUp);
}
void PickupComponent::pickupLoot(GameObject* character)
{
	if(character && !pickedUp)
		if(character->GetComponent<InventoryComponent>())
			if(character->GetComponent<InventoryComponent>()->addItem(createItem(),stackSize))
				pickedUp = true;
}
Item PickupComponent::createItem()
{
	Item item;
	loadItem(itemID,item);
	return item;
}
#ifdef _DEBUG
bool PickupComponent::UpdateFromEditor()
{
	pickupLoot(Engine::Window.focus.gameObject);
	return true;
}
#endif