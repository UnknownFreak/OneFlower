#include "GameObject.hpp"
#include <Combat/Stats.hpp>

#include <Graphics/PlayerInteractionPrompt.hpp>

#include "ObjectInstanceHandler.hpp"
#include "Interactable.hpp"


void GameObject::sendMessage(const Core::String& msgType, const Core::String& message)
{
	msgType;
	message;
}
GameObject::GameObject()
{
	addComponent<Component::Transform>();
}
GameObject::GameObject(GameObject&& copy)
{
	componentMap = std::move(copy.componentMap);
	for (auto& x : componentMap)
	{
		x.second.get()->attachOn(this);
	}
	copy.componentMap.clear();
}
GameObject::GameObject(const GameObject& copy)
{
	for (auto& x : copy.componentMap)
	{
		AddComponent(x.second->copy());
	}
}

GameObject& GameObject::operator=(const GameObject& copy)
{
	id = copy.id;
	for (auto& x : componentMap)
	{
		x.second->detach();
	}
	componentMap.clear();
	for (auto& x : copy.componentMap)
	{
		AddComponent(x.second->copy());
	}
	reAttach();
	return *this;
}

GameObject::~GameObject()
{
	auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Object::GameObject");
	logger.Debug("~GameObject -> id: " + id.to_string());
	logger.Debug("~GameObject -> tag: " + tag);
	for (auto& x : componentMap)
	{
		logger.Debug("~GameObject -> Detach" + x.second->getTypeName());
		x.second.get()->detach();
	}
	componentMap.clear();
	logger.Debug("~GameObject -> Done " + id.to_string());
}

bool GameObject::interact(const Enums::InteractionOption& interaction)
{
	auto comp = getComponent<PlayerInteractionPrompt>();
	if (comp)
	{
		return comp->doInteraction(interaction);
	}
	else
	{
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Object::GameObject").Warning("Trying to perform interact with an object that has no player interact prompt added to it.");
	}
	return false;
}

void GameObject::interact(const bool& reverseAnimation, const short& repeat)
{
	auto comp = getComponent<Component::Interactable>();
	if (comp)
	{
		comp->interact(reverseAnimation, repeat);
	}
}

void GameObject::toggleObjectState()
{
	Enums::ObjectState state = Enums::ObjectState::Active;
	if (objectState == Enums::ObjectState::Active)
		state = Enums::ObjectState::Inactive;

	toggleObjectState(state);
}

void GameObject::toggleObjectState(const Enums::ObjectState& newState)
{
	if (newState == Enums::ObjectState::Active && objectState != newState)
	{
		objectState = newState;
		Component::ObjectStateActivator* c = getComponent<Component::ObjectStateActivator>();
		if (c)
		{
			c->toggle();
		}
	}
	else if (newState == Enums::ObjectState::Inactive && objectState != newState)
	{
		objectState = newState;
		Component::ObjectStateActivator* c = getComponent<Component::ObjectStateActivator>();
		if (c)
		{
			c->toggle();
		}
	}

}

void GameObject::onCollision(Interfaces::ICollider* collider)
{
	if (objectState == Enums::ObjectState::Active)
		for (auto& component : componentMap)
		{
			component.second->onCollision(collider);
		}
}

void GameObject::Update()
{
	for (auto& i : componentMap)
	{
		i.second->Update();
	}
}

void GameObject::Simulate(const float& fElapsedTime)
{
	if (objectState == Enums::ObjectState::Active)
		for (auto& component : componentMap)
		{
			component.second->Simulate(fElapsedTime);
		}
}

void GameObject::Simulate(const float& fElapsedTime, const bool& bUpdate)
{
	if (objectState == Enums::ObjectState::Active)
		for (auto& component : componentMap)
		{
			component.second->Simulate(fElapsedTime);
			if (bUpdate)
				component.second->Update();
		}
}

void GameObject::onDeath(const GameObject* killer, const float& delayedDespawnTime, const bool& unloadFlag)
{
	killer;
	unloading = unloadFlag;
	if (!unloadFlag)
		for (auto& component : componentMap)
		{
			component.second->onDeath();
		}
	Engine::GetModule<EngineModule::ObjectInstanceHandler>().removeObject(this, delayedDespawnTime);

}

void GameObject::onDelete()
{
	auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Object::GameObject");
	logger.Debug("OnDelete -> Enter");
	if (unloading)
	{
		logger.Debug("Unloading - Fast return");
		return;
	}
	logger.Debug("OnDelete -> componentMap");
	for (auto& component : componentMap)
	{
		logger.Debug("OnDelete Component Shared Ptr Addr -> " + Core::toHex((size_t)&component.second));
		logger.Debug("OnDelete Component Addr -> " + Core::toHex((size_t)component.second.get()));
		logger.Debug("OnDelete Component Type -> " + Enums::to_string(component.first));
		logger.Debug("OnDelete Component TypeName -> " + component.second->getTypeName());
		component.second->onDelete();
	}
	logger.Debug("OnDelete -> Exit");
}

void GameObject::applyGameMode(const Resource::GameModeModifier& modifier)
{
	for (auto& trigger : modifier.onDeathTriggers)
	{
		onDeathTriggers.push_back(std::move(trigger->clone()));
	}
	auto p = getComponent<Component::Stats>();
	if (p)
	{
		for (auto& mod : modifier.modifierList)
		{
			p->addModifier(mod);
		}
	}
}

void GameObject::reAttach()
{
	for (auto& x : componentMap)
	{
		x.second->detach();
		x.second->attachOn(this);
	}
}

Component::Base* GameObject::AddComponent(Component::Base* componentToAdd)
{
	if (componentMap.find(componentToAdd->getType()) == componentMap.end())
	{
		componentToAdd->attachOn(this);
	}
	else
	{
		delete componentToAdd;
		componentToAdd = nullptr;
	}
	return componentToAdd;
}

Component::Base* GameObject::AddOrReplaceComponent(Component::Base* componentToAdd)
{
	if (componentMap.find(componentToAdd->getType()) == componentMap.end())
		componentToAdd->attachOn(this);
	else
	{
		componentMap.erase(componentToAdd->getType());
		componentToAdd->attachOn(this);
	}
	return componentToAdd;
}
