#include "BaseComponent.hpp"
void BaseComponent::attachOn(GameObject* attachTo)
{
	this->attachedOn = attachTo;
}
std::string BaseComponent::getTypeName()
{
	return this->componentName;
}