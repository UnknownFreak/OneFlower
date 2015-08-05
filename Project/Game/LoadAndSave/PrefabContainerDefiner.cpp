#include "PrefabContainer.hpp"

#include "../Component/GameObject.h"

#include <string>
PrefabContainer::PrefabContainer()
{
}

//Adds a prefab from existing GameObject, with the name of the gameobject as key name
void PrefabContainer::addPrefab(GameObject* go)
{
	mapOfPrefabs.insert(std::pair <std::string,Prefab>(go->name,Prefab(go)));
}

//Adds a prefab from existing GameObject, with a custom string key
void PrefabContainer::addPrefab(std::string name,GameObject* go)
{
	mapOfPrefabs.insert(std::pair<std::string,Prefab>(name,go));
}

// If prefab does exist remove it, string as input
void PrefabContainer::removePrefab(std::string prefab)
{
	std::map<std::string,Prefab>::iterator it = mapOfPrefabs.find(prefab);

	if(it != mapOfPrefabs.end())
		mapOfPrefabs.erase(it);
	else
		;
}