#include "GameObject.h"
#include <vector>
#include <map>
#include "../Component/IBaseComponent.hpp"
#include "TransformComponent.hpp"
#include "RenderComponent.h"
#include "HitboxComponent.hpp"
#include "DialogComponent.hpp"

#include "../Engine.hpp"


std::map<GameObject*,unsigned int> listOfGameObjectID;
std::vector<unsigned int> listOfOldGameObjectID;

unsigned int RequestID();
std::map<int,BaseComponent*>* GameObject::GetComponents()
{
	return &componentMap;
}

GameObject::GameObject()
{
	id = RequestID();
	AddComponent(new TransformComponent());
	listOfGameObjectID.insert(std::make_pair(this,id));
}
/*GameObject::GameObject(GameObject & go)
{
this->id = go.id;
this->name = go.name;
for (std::map<int, BaseComponent*>::iterator it = go.componentMap.begin(); it != go.componentMap.end(); it++) {
std::cout<< it->second->getTypeName();
//this->componentMap.insert(componentMap.end(),);
}
}
//*/

GameObject::GameObject(const GameObject & go)
{
	this->id = go.id;
	this->name = go.name;

	for(std::map<int,BaseComponent*>::const_iterator it = go.componentMap.begin(); it != go.componentMap.end(); it++)
	{
		std::cout << it->second->getTypeName() << std::endl;
		if(it->second->getType() == IBaseComponent<RenderComponent>::typeID)
		{
			this->AddComponent(new RenderComponent(*go.ReadComponent<RenderComponent>()));
		}
		else if(it->second->getType() == IBaseComponent<TransformComponent>::typeID)
		{
			this->AddComponent(new TransformComponent(*go.ReadComponent<TransformComponent>()));
		}
		else if(it->second->getType() == IBaseComponent<HitboxComponent>::typeID)
		{
			this->AddComponent(new HitboxComponent(*go.ReadComponent<HitboxComponent>()));
		}
		else if(it->second->getType() == IBaseComponent<DialogComponent>::typeID)
		{
			this->AddComponent(new DialogComponent(*go.ReadComponent<DialogComponent>()));
		}
	}
}

GameObject::GameObject(std::string _name)
{
	name = _name;
	id = RequestID();
	AddComponent(new TransformComponent());
	listOfGameObjectID.insert(std::make_pair(this,id));
}
GameObject::~GameObject()
{
	std::map<GameObject*,unsigned int>::iterator it;
	it = listOfGameObjectID.find(this);
	if(it != listOfGameObjectID.end())
	{
		listOfOldGameObjectID.insert(listOfOldGameObjectID.end(),it->second);

		if(it != listOfGameObjectID.end())
			listOfGameObjectID.erase(it);
		for(std::map<int,BaseComponent*>::iterator cIt = componentMap.begin(); cIt != this->componentMap.end(); cIt++)
		{
			delete cIt->second;
			cIt->second = 0;
		}
	}
}
/*
void GameObject::AddComponent(BaseComponent* componentToAttach)
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
void GameObject::AddComponent(BaseComponent* componentToAttach)
{
	//use map inbuild function to check if there is a
	if(!componentMap.count(componentToAttach->getType()) > 0)
	{
		componentToAttach->attachOn(this);
		componentMap.insert(std::make_pair(componentToAttach->getType(),componentToAttach));
	}
	else
	{
		delete componentToAttach;
		componentToAttach = 0;
	}
}

//Return a unused or a new ID
unsigned int RequestID()
{
	unsigned int temp = 0;
	if(!listOfGameObjectID.size() > 0)
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
	Engine::game.requestRemoveal(this);
}