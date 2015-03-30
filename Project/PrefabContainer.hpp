#ifndef PrefabContainer_HPP
#define PrefabContainer_HPP

#include <map>
#include "Prefab.hpp"

class GameObject;
class PrefabContainer
{
public:
	PrefabContainer();

	std::map<std::string,Prefab> mapOfPrefabs;

	void addPrefab(GameObject* go);
	void addPrefab(std::string prefabName,GameObject* go);

	void removePrefab(std::string prefab);

protected:
	template<class Archive>
	friend void save(Archive &ar,const PrefabContainer &pre);
	template<class Archive>
	friend void load(Archive &ar,PrefabContainer &pre);
};

#endif