#include "BaseComponent.hpp"
#include "GameObject.h"

namespace Component
{
	void Base::attachOn(GameObject* attachTo)
	{
		this->attachedOn = attachTo;
		attachTo->componentMap.insert(std::make_pair(this->getType(), this));
	}
	bool Base::updateFromEditor()
	{
		return false;
	}
	void Base::update()
	{
	}
	void Base::onCollision(Physics::Collider& c)
	{
	}

	/*
	void Base::sendMessage(const BaseMessage& msg)
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
	void Base::getMessage(const BaseMessage target)
	{
	}

	/*
	std::string Base::getTypeName()
	{
	return this->componentName;
	}
	//*/
}