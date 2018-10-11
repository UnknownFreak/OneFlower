#include "GameObject.h"
#include "IBaseComponent.hpp"
#include "TransformComponent.hpp"
//#include <iostream>
std::map<GameObject*, unsigned int> listOfGameObjectID;
std::vector<unsigned int> listOfOldGameObjectID;

size_t RequestID();
std::map<size_t, Component::Base*>* GameObject::GetComponents()
{
	return &componentMap;
}

GameObject::GameObject() : IObject("New GameObject")
{
	id = RequestID();
	AddComponent(new Component::Transform());
	listOfGameObjectID.insert(std::make_pair(this, id));
}
/*GameObject::GameObject(GameObject & go)
{
this->id = go.id;
this->name = go.name;
for (std::map<int, Base*>::iterator it = go.componentMap.begin(); it != go.componentMap.end(); it++) {
std::cout<< it->second->getTypeName();
//this->componentMap.insert(componentMap.end(),);
}
}
//*/

GameObject::GameObject(const GameObject & go) : IObject(go)
{
	this->id = go.id;
	this->name = go.name;

	for (std::map<size_t, Component::Base*>::const_iterator it = go.componentMap.begin(); it != go.componentMap.end(); it++)
	{
		this->AddComponent(it->second->copy());
	}
}

GameObject::GameObject(Core::String _name) : IObject(_name)
{
	id = RequestID();
	AddComponent(new Component::Transform());
	listOfGameObjectID.insert(std::make_pair(this, id));
}
GameObject & GameObject::operator=(const GameObject & right)
{
	name = right.name;
	tag = right.tag;
	id = right.id;
	for (std::map<size_t, Component::Base*>::const_iterator it = right.componentMap.begin(); it != right.componentMap.end(); it++)
	{
		this->AddComponent(it->second->copy());
	}
	return *this;
}
GameObject::~GameObject()
{
	//Engine::Window.ListViewer.remove(this);

	std::map<GameObject*, unsigned int>::iterator it;
	if (listOfGameObjectID.size() != 0)
	{
		it = listOfGameObjectID.find(this);
		if (it != listOfGameObjectID.end())
		{
			listOfOldGameObjectID.insert(listOfOldGameObjectID.end(), it->second);

			if (it != listOfGameObjectID.end())
				listOfGameObjectID.erase(it);
		}
	}
	for (std::map<size_t, Component::Base*>::iterator cIt = componentMap.begin(); cIt != this->componentMap.end(); cIt++)
	{
		delete cIt->second;
		cIt->second = 0;
	}
}
/*
void GameObject::AddComponent(Base* componentToAttach)
{
//use map inbuild function to check if there is a
if (!componentMap.count(componentToAttach->getTypeName()) > 0)
{
componentToAttach->attachOn(this);
componentMap.insert(componentMap.end(),
std::make_pair
(
componentToAttach->getTypeName(),
componentToAttach
)
);
}
}
//*/
Component::Base* GameObject::AddComponent(Component::Base* componentToAttach)
{
	//use map inbuild function to check if there is a
	if (!componentMap.count(componentToAttach->getType()))
	{
		componentToAttach->attachOn(this);
		componentMap.insert(std::make_pair(componentToAttach->getType(), componentToAttach));
		return componentToAttach;
	}
	else
	{
		delete componentToAttach;
		componentToAttach = 0;
		return NULL;
	}
}
void GameObject::sendMessage(const BaseMessage msg, Component::Base* c)
{
	componentMap.find(c->getType())->second->getMessage(msg);
}
void GameObject::sendAll(const BaseMessage msg)
{
	for (std::map<size_t, Component::Base*>::iterator it = componentMap.begin(); it != componentMap.end(); ++it)
	{
		it->second->getMessage(msg);
	}
}
//void GameObject::collision(std::vector<Physics::Collider*>& msgs)
//{
//	Physics::Collider& msg = *msgs[0];
//	for (std::map<int, Base*>::iterator it = componentMap.begin(); it != componentMap.end(); ++it)
//	{
//		it->second->onCollision(msg);
//	}
//}

//Return a unused or a new ID
size_t RequestID()
{
	unsigned int temp = 0;
	if (!listOfGameObjectID.size())
	{
		return 1;
	}
	//	if (listOfOldGameObjectID.size() > 0)
	//	return listOfOldGameObjectID.at(0);
	else
	{
		temp = listOfGameObjectID.rbegin()->second;
		return	 temp + 1;
	}
}
void GameObject::destroy()
{
	//Engine::game.requestRemoveal(this);
}