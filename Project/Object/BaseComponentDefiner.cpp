#include "BaseComponent.hpp"
#include "GameObject.hpp"

namespace Component
{
	void Base::attachOn(GameObject* attachTo)
	{
		if (attachedOn)
			detach();
		this->attachedOn = attachTo;
		if(attachTo->componentMap.find(this->getType()) == attachTo->componentMap.end())
			attachTo->componentMap.insert(std::make_pair(this->getType(), std::shared_ptr<Base>(this)));
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
	//void Base::getMessage(const BaseMessage target)
	//{
	//}

	/*
	std::string Base::getTypeName()
	{
	return this->componentName;
	}
	//*/
}