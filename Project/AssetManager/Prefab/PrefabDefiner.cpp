#include "prefab.hpp"

#include <Core/Component/GameObject.h>

#define prefab_current_version OneVersion(1,0,0)

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

Prefab::Prefab() : IRequestable("", 0, prefab_current_version), name(""), tag(""), base()
{

}

// Copy-c-tor

Prefab::Prefab(const Prefab& pre) : name(pre.name), tag(pre.tag), IRequestable(pre)
{
	for (size_t i = 0; i < pre.base.size(); ++i)
		base.push_back(pre.base[i]->copy());
}
// Ctor with Gameobject ptr
Prefab::Prefab(const GameObject* go) : name(go->name), tag(go->tag), IRequestable("", 0, prefab_current_version)
{
	for (std::map<int, BaseComponent*>::iterator it = ((GameObject*)go)->GetComponents()->begin(); it != ((GameObject*)go)->GetComponents()->end(); ++it)
		base.push_back(it->second->copy());
	for (std::vector<BaseComponent*>::iterator it = base.begin(); it != base.end(); ++it)
	{
		BaseComponent* tmp = *it;
		tmp->attachedOn = NULL;
	}
}

Prefab & Prefab::operator=(const Prefab & right)
{
	name = right.name;
	tag = right.tag;
	ID = right.ID;
	fromMod = right.fromMod;
	mode = right.mode;
	objectVersion = right.objectVersion;
	for (size_t i = 0; i < right.base.size(); ++i)
		base.push_back(right.base[i]->copy());
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
const size_t Prefab::getTypeID(size_t index)
{
	return base[index]->getType();
}