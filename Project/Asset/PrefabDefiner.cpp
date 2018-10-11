#include "prefab.hpp"

#include <Core/Component/GameObject.h>

#define prefab_current_version OneVersion(1,0,0)

namespace Asset
{

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

	Prefab::Prefab() : IRequestable("", 0, prefab_current_version), //IObject(),
		base()
	{

	}

	// Copy-c-tor

	Prefab::Prefab(const Prefab& pre) : //IObject(pre),
		IRequestable(pre)
	{
		for (size_t i = 0; i < pre.base.size(); ++i)
			base.push_back(pre.base[i]->copy());
	}
	// Ctor with Gameobject ptr
	Prefab::Prefab(const GameObject* go) :// IObject(*go),
		IRequestable("", 0, prefab_current_version)
	{
		for (std::map<size_t, Component::Base*>::iterator it = ((GameObject*)go)->GetComponents()->begin(); it != ((GameObject*)go)->GetComponents()->end(); ++it)
			base.push_back(it->second->copy());
		for (std::vector<Component::Base*>::iterator it = base.begin(); it != base.end(); ++it)
		{
			Component::Base* tmp = *it;
			tmp->attachedOn = NULL;
		}
	}

	Prefab & Prefab::operator=(const Prefab & right)
	{
		//name = right.name;
		//tag = right.tag;
		ID = right.ID;
		fromMod = right.fromMod;
		mode = right.mode;
		objectVersion = right.objectVersion;
		for (size_t i = 0; i < right.base.size(); ++i)
			base.push_back(right.base[i]->copy());
		return *this;
	}

	GameObject* Prefab::createFromPrefab() const
	{
		GameObject* go = new GameObject();
		//go->name = name;
		//go->tag = tag;
		for each (Component::Base* var in base)
			go->AddComponent(var->copy());
		return go;
	}
	const size_t Prefab::getTypeID(size_t index)
	{
		return base[index]->getType();
	}

	Core::String Prefab::getName() const
	{
		return "";// name;
	}

	Core::String Prefab::getValue() const
	{
		return "<Prefab Data>";
	}
}
