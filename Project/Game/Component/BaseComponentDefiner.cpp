#include "BaseComponent.hpp"
#include "GameObject.h"
void BaseComponent::attachOn(GameObject* attachTo)
{
	this->attachedOn = attachTo;
	attachTo->componentMap.insert(std::make_pair(this->getType(),this));
}
bool BaseComponent::updateFromEditor()
{
	return false;
}
void BaseComponent::update()
{
}
/*
void BaseComponent::sendMessage(const BaseMessage& msg)
{
#ifdef _DEBUG
if(this->attachedOn)
for(auto it = attachedOn->GetComponents()->begin(); it != attachedOn->GetComponents()->end(); ++it)
it->second->recieveMessage(msg);
#else
for(auto it = attachedOn->GetComponents()->begin(); it != attachedOn->GetComponents()->end(); ++it)
it->second->recieveMessage(msg);
#endif
}
//*/
void recieveMessage(const BaseMessage& target)
{
}

/*
std::string BaseComponent::getTypeName()
{
return this->componentName;
}
//*/