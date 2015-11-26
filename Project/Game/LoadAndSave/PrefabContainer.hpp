#ifndef PrefabContainer_HPP
#define PrefabContainer_HPP

#include <map>
#include "Prefab.hpp"

class GameObject;
class PrefabContainer
{
private:
	std::map<size_t,Prefab> mapOfPrefabs;
public:
	PrefabContainer() = default;

	void addPrefab(const Prefab pref);
	void addPrefab(const GameObject* go);
	void addPrefab(const size_t prefabID, const GameObject* go);
	void removePrefab(size_t prefabID);

	std::map<size_t, Prefab>::iterator find(size_t id);
	std::map<size_t, Prefab>::iterator end();
	std::map<size_t, Prefab>::iterator begin();
	std::map<size_t, Prefab>& getMap();
	size_t size();

protected:
	template<class Archive>
	friend void save(Archive &ar,const PrefabContainer &pre);
	template<class Archive>
	friend void load(Archive &ar,PrefabContainer &pre);
};

#endif