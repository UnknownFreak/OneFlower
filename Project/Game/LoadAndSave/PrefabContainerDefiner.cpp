#include "PrefabContainer.hpp"
#include "../Component/GameObject.h"
#include "../../Engine.hpp"

#include <string>

void PrefabContainer::addPrefab(const Prefab prefab)
{
	mapOfPrefabs.insert(std::pair<size_t, Prefab>(prefab.ID, Prefab(prefab)));
#ifdef _DEBUG
	Engine::Window.prefabList.addPrefab(mapOfPrefabs.find(prefab.ID)->second);
#endif
}
/*Adds a prefab from existing GameObject, with the id of the gameobject as key
*Not recomended
*Use addPrefab(size_t,GameObject*) instead
*/
void PrefabContainer::addPrefab(const GameObject* go)
{
	mapOfPrefabs.insert(std::pair <size_t,Prefab>(go->id,Prefab(go)));
#ifdef _DEBUG
	Engine::Window.prefabList.addPrefab(mapOfPrefabs.find(go->id)->second);
#endif
}

//Adds a prefab from existing GameObject, with a custom key
void PrefabContainer::addPrefab(const size_t ID,const GameObject* go)
{
	mapOfPrefabs.insert(std::pair<size_t,Prefab>(ID,Prefab(go)));
#ifdef _DEBUG
	Engine::Window.prefabList.addPrefab(mapOfPrefabs.find(ID)->second);
#endif
}

// If prefab does exist remove it
void PrefabContainer::removePrefab(size_t prefabID)
{
	std::map<size_t,Prefab>::iterator it = mapOfPrefabs.find(prefabID);

	if (it != mapOfPrefabs.end())
	{
#ifdef _DEBUG
		Engine::Window.prefabList.removePrefab(it->second);
#endif
		mapOfPrefabs.erase(it);
	}
	else
		;
}

//Iterator functions
std::map<size_t, Prefab>::iterator PrefabContainer::find(size_t prefabID)
{
	return mapOfPrefabs.find(prefabID);
}
std::map<size_t, Prefab>::iterator PrefabContainer::end()
{
	return mapOfPrefabs.end();
}
std::map<size_t, Prefab>::iterator PrefabContainer::begin()
{
	return mapOfPrefabs.begin();
}
std::map<size_t, Prefab>& PrefabContainer::getMap()
{
	return mapOfPrefabs;
}
size_t PrefabContainer::size()
{
	return mapOfPrefabs.size();
}