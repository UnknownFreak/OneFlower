#include "BaseComponent.hpp"
void BaseComponent::attachOn(GameObject* attachTo)
{
	this->attachedOn = attachTo;
}
bool BaseComponent::UpdateFromEditor()
{
	return false;
}
/*	
std::string BaseComponent::getTypeName()
{
	return this->componentName;
}
//*/