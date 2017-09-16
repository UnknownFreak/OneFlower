#include "prefab.hpp"

#include <Core/Component/GameObject.h>
// D-tor
Prefab::~Prefab()
{
	for (size_t i = 0; i < base.size(); ++i)
	{
		delete base[i];
		base[i] = nullptr;
	}
	base.clear();
}

Prefab::Prefab() : IRequestable("", 0), name(""), tag(""), base()
{

}

// Copy-c-tor

Prefab::Prefab(const Prefab& pre) : name(pre.name), tag(pre.tag), IRequestable(pre)
{
	for (size_t i = 0; i < pre.base.size(); ++i)
		base.push_back(pre.base[i]->copy());
}
// Ctor with Gameobject ptr
Prefab::Prefab(const GameObject* go) : name(go->name), tag(go->tag), IRequestable("", 0)
{
	for (std::map<int, BaseComponent*>::iterator it = ((GameObject*)go)->GetComponents()->begin(); it != ((GameObject*)go)->GetComponents()->end(); ++it)
		base.push_back(it->second->copy());
	for (std::vector<BaseComponent*>::iterator it = base.begin(); it != base.end(); ++it)
	{
		BaseComponent* tmp = *it;
		tmp->attachedOn = NULL;
	}
}

Prefab & Prefab::operator=(const Prefab & left)
{
	name = left.name;
	tag = left.tag;
	ID = left.ID;
	fromMod = left.fromMod;
	mode = left.mode;
	for (size_t i = 0; i < left.base.size(); ++i)
		base.push_back(left.base[i]->copy());
	return *this;
}

GameObject* Prefab::createFromPrefab()
{
	GameObject* go = new GameObject();
	go->name = name;
	go->tag = tag;
	for each (BaseComponent* var in base)
		go->AddComponent(var->copy());
	return go;
}
const unsigned int Prefab::getTypeID(size_t index)
{
	return base[index]->getType();
}