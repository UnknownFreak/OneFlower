#ifndef PrefabContainer_HPP
#define PrefabContainer_HPP

#include <map>
#include "Prefab.hpp"

class GameObject;
class PrefabContainer
{
private:
	std::map<size_t, Prefab> mapOfPrefabs2;
	std::map<std::pair<std::string, size_t>, Prefab> mapOfPrefabs;
public:
	PrefabContainer() = default;

	void addPrefab(const Prefab& pref);
	void addPrefab(const GameObject* go);
	void addPrefab(const size_t prefabID, const GameObject* go);
	void removePrefab(size_t prefabID);

	std::map<std::pair<std::string, size_t>, Prefab>::iterator find(std::string name, size_t prefabID);
	std::map<std::pair<std::string, size_t>, Prefab>::iterator end();
	std::map<std::pair<std::string, size_t>, Prefab>::iterator begin();
	std::map<std::pair<std::string, size_t>, Prefab>& getMap();
	size_t size();
};

#endif