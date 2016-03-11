#ifndef Prefab_HPP
#define Prefab_HPP

#include <vector>
#include "../Component/BaseComponent.hpp"
#include "EditorObjectSaveMode.hpp"
class GameObject;
class Prefab
{
	friend class BaseComponent;
public:
	
	Prefab() = default;
	Prefab(const GameObject* go);
	Prefab(const GameObject go);
	Prefab(const Prefab& pre);
	~Prefab();

	GameObject* createFromPrefab();

private:
#ifdef _DEBUG
public:
#endif
	
	std::vector<BaseComponent*> base;
	size_t ID;
	std::string name;
	std::string tag;
	std::string fromMod = "OneFlower.main";
	size_t mode = EditorObjectSaveMode::ADD;
	const unsigned int getTypeID(size_t index);

protected:
	template<class Archive>
	friend void save(Archive &ar,const Prefab &pre);
	template<class Archive>
	friend void load(Archive &ar,Prefab &pre);
};

#endif