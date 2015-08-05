#include "prefab.hpp"

#include "../Component/GameObject.h"
#include "../Component/DialogComponent.hpp"
#include "../Component/HitboxComponent.hpp"
#include "../Component/OverheadComponent.hpp"
#include "../Component/RenderComponent.h"
#include "../Component/RigidComponent.hpp"
#include "../Component/TransformComponent.hpp"
#include "../Component/BaseComponent.hpp"

//LOW: Remove this if not needed and just use the default compiler ctor instead of empty body
// Default c-tor
Prefab::Prefab()
{
}
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
Prefab::Prefab(const Prefab& pre): name(pre.name),tag(pre.tag)
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
Prefab::Prefab(GameObject* go): name(go->name),tag(go->tag)
{
	for(std::map<int,BaseComponent*>::iterator it = go->GetComponents()->begin(); it != go->GetComponents()->end(); ++it)
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