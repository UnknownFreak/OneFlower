#ifndef Prefab_HPP
#define Prefab_HPP

#include <vector>


class BaseComponent;
class GameObject;
class Prefab
{
public:

	Prefab();
	Prefab(GameObject* go);
	Prefab(GameObject go);
	Prefab(const Prefab& pre);
	~Prefab();

	GameObject* createFromPrefab();

private:
	
	std::vector<BaseComponent*> base;

	std::string name;
	std::string tag;
	template<class Archive>
	friend void save(Archive &ar,const Prefab &pre);
	template<class Archive>
	friend void load(Archive &ar, Prefab &pre);
};



#endif