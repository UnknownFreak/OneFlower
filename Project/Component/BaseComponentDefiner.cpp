#include "BaseComponent.hpp"
#include "GameObject.h"
void BaseComponent::attachOn(GameObject* attachTo)
{
	this->attachedOn = attachTo;
	attachTo->componentMap.insert(std::make_pair(this->getType(),this));
}
bool BaseComponent::UpdateFromEditor()
{
	return false;
}
void BaseComponent::onCollision(GameObject* target)
{
}

/*
std::string BaseComponent::getTypeName()
{
return this->componentName;
}
//*/