#include "PickupComponent.hpp"

const unsigned int IBaseComponent<PickupComponent>::typeID = 1010;
std::string IBaseComponent<PickupComponent>::componentName = "PickupComponent";

PickupComponent::PickupComponent(unsigned int itemID) : itemID(itemID)
{

}

void PickupComponent::attachOn(GameObject* attachTo)
{
	BaseComponent::attachOn(attachTo);
	//REGISTER_EDITOR_VARIABLE(unsigned int,itemID,ItemID);
}
bool PickupComponent::updateFromEditor()
{
	return true;
}