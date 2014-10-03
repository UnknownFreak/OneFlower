#include "GameObject.h"
#include <vector>
#include <map>
std::map<GameObject*,unsigned int> listOfGameObjectID;
std::vector<unsigned int> listOfOldGameObjectID;

unsigned int RequestID();
GameObject::GameObject()
{
	id = RequestID();
	listOfGameObjectID.insert(listOfGameObjectID.end(), std::make_pair(this, id));
}
GameObject::GameObject(std::string _name)
{
	id = RequestID();
	name = _name;
	listOfGameObjectID.insert(listOfGameObjectID.end(), std::make_pair(this, id));
}
GameObject::~GameObject()
{
	std::map<GameObject*, unsigned int>::iterator it;
	it = listOfGameObjectID.find(this);
	if (it != listOfGameObjectID.end())
	{
		listOfOldGameObjectID.insert(listOfOldGameObjectID.end(), it->second);

		if (it != listOfGameObjectID.end())
			listOfGameObjectID.erase(it);
		for (std::map<std::string, BaseComponent*>::iterator cIt = componentMap.begin(); cIt != this->componentMap.end(); cIt++)
		{
			delete cIt->second;
			cIt->second = 0;
		}
	}
}

void GameObject::AddComponent(BaseComponent* componentToAttach)
{
	//use map inbuild function to check if there is a
	if (!componentMap.count(componentToAttach->getTypeName()) > 0)
	{
		componentToAttach->attachOn(this);
		componentMap.insert	(	componentMap.end(),
								std::make_pair
									(
										componentToAttach->getTypeName(),
										componentToAttach
									)
							);	
	}
}

//Return a unused or a new ID
unsigned int RequestID()
{
	unsigned int temp = 0;
	if (!listOfGameObjectID.size() > 0)
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