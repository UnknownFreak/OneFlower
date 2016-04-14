#include "prefab.hpp"

#include "../Component/GameObject.h"
#include "../Component/DialogComponent.hpp"
#include "../Component/HitboxComponent.hpp"
#include "../Component/OverheadComponent.hpp"
#include "../Component/RenderComponent.h"
#include "../Component/RigidComponent.hpp"
#include "../Component/TransformComponent.hpp"
#include "../Component/BaseComponent.hpp"

#include "../../Engine.hpp"
// D-tor
Prefab::~Prefab()
{
	for(size_t i = 0; i < base.size(); ++i)
	{
		delete base[i];
		base[i] = nullptr;
	}
	base.clear();
}
// Copy-c-tor
Prefab::Prefab(const Prefab& pre) : name(pre.name), tag(pre.tag), ID(pre.ID), fromMod(pre.fromMod), mode(pre.mode)
{
	for(size_t i = 0; i < pre.base.size(); ++i)
	{
		BaseComponent* tmp = pre.base[i];
		if(tmp->getType() == IBaseComponent<RenderComponent>::typeID)
		{
			base.push_back(new RenderComponent(*(RenderComponent*)tmp));
		}
		else if(tmp->getType() == IBaseComponent<TransformComponent>::typeID)
		{
			base.push_back(new TransformComponent(*(TransformComponent*)tmp));
		}
		else if(tmp->getType() == IBaseComponent<HitboxComponent>::typeID)
		{
			base.push_back(new HitboxComponent(*(HitboxComponent*)tmp));
		}
		else if(tmp->getType() == IBaseComponent<DialogComponent>::typeID)
		{
			base.push_back(new DialogComponent(*(DialogComponent*)tmp));
		}
		else if(tmp->getType() == IBaseComponent<OverheadComponent>::typeID)
		{
			base.push_back(new OverheadComponent(*(OverheadComponent*)tmp));
		}
		else if(tmp->getType() == IBaseComponent<RigidComponent>::typeID)
		{
			base.push_back(new RigidComponent(*(RigidComponent*)tmp));
		}
	}
}
// Ctor with Gameobject ptr
Prefab::Prefab(const GameObject* go) : name(go->name), tag(go->tag), ID(0)
{
	for (std::map<int, BaseComponent*>::iterator it = ((GameObject*)go)->GetComponents()->begin(); it != ((GameObject*)go)->GetComponents()->end(); ++it)
	{
		//Make directives id instead and use switches
		if(it->first == IBaseComponent<RenderComponent>::typeID)
		{
			base.push_back(new RenderComponent(*(RenderComponent*)it->second));
		}
		else if(it->first == IBaseComponent<TransformComponent>::typeID)
		{
			base.push_back(new TransformComponent(*(TransformComponent*)it->second));
		}
		else if(it->first == IBaseComponent<HitboxComponent>::typeID)
		{
			base.push_back(new HitboxComponent(*(HitboxComponent*)it->second));
		}
		else if(it->first == IBaseComponent<DialogComponent>::typeID)
		{
			base.push_back(new DialogComponent(*(DialogComponent*)it->second));
		}
		else if(it->first == IBaseComponent<OverheadComponent>::typeID)
		{
			base.push_back(new OverheadComponent(*(OverheadComponent*)it->second));
		}
		else if(it->first == IBaseComponent<RigidComponent>::typeID)
		{
			base.push_back(new RigidComponent(*(RigidComponent*)it->second));
		}
	}
	for(std::vector<BaseComponent*>::iterator it = base.begin(); it != base.end(); ++it)
	{
		BaseComponent* tmp = *it;
		tmp->attachedOn = NULL;
	}
}

GameObject* Prefab::createFromPrefab()
{
	GameObject* go = new GameObject();
	go->name = name;
	go->tag = tag;
	for each (BaseComponent* var in base)
	{
		if (var->getType() == IBaseComponent<RenderComponent>::typeID)
			go->AddComponent(new RenderComponent(*(RenderComponent*)var));
		else if (var->getType() == IBaseComponent<TransformComponent>::typeID)
			go->AddComponent(new TransformComponent(*(TransformComponent*)var));
		else if (var->getType() == IBaseComponent<HitboxComponent>::typeID)
			go->AddComponent(new HitboxComponent(*(HitboxComponent*)var));
		else if (var->getType() == IBaseComponent<DialogComponent>::typeID)
			go->AddComponent(new DialogComponent(*(DialogComponent*)var));
		else if (var->getType() == IBaseComponent<OverheadComponent>::typeID)
			go->AddComponent(new OverheadComponent(*(OverheadComponent*)var));
		else if (var->getType() == IBaseComponent<RigidComponent>::typeID)
			go->AddComponent(new RigidComponent(*(RigidComponent*)var));
		else
			;// Engine::Window.debug.print("Missing if statement for component type:" + std::to_string(var->getType()), __LINE__, __FILE__);
	}
	return go;
}
const unsigned int Prefab::getTypeID(size_t index)
{
	return base[index]->getType();
}