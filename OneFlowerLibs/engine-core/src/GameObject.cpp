#include <object/GameObject.hpp>

//#include <Combat/Stats.hpp>

//#include <Object/ObjectStateActivator.hpp>

//#include <Graphics/PlayerInteractionPrompt.hpp>

#include <module/ObjectInstanceHandler.hpp>
#include <object/component/Transform.hpp>
//#include "Interactable.hpp"

namespace of::object
{
	void GameObject::post(const messaging::Topic& topic, std::shared_ptr<messaging::Body> message)
	{
		post({ topic, message });
	}
	void GameObject::post(const messaging::Message& message)
	{
		for (auto& it : componentMap)
		{
			it.second->onMessage(message);
		}
	}
	bool GameObject::post(const common::uuid& id, const messaging::Topic& topic, std::shared_ptr<messaging::Body> message)
	{
		return post(id, { topic, message });
	}

	bool GameObject::post(const common::uuid& id, const messaging::Message& message)
	{
		auto comp = componentMap.find(id);
		if (comp != componentMap.end())
		{
			comp->second->onMessage(message);
			return true;
		}
		return false;
	}

	GameObject::GameObject() noexcept
	{
		addComponent<component::Transform>();
	}
	GameObject::GameObject(GameObject&& copy) noexcept
	{
		componentMap = std::move(copy.componentMap);
		for (auto& x : componentMap)
		{
			x.second.get()->attachOn(this);
		}
		copy.componentMap.clear();
	}
	GameObject::GameObject(const GameObject& copy) noexcept
	{
		for (auto& x : copy.componentMap)
		{
			AddComponent(x.second->copy());
		}
	}

	GameObject& GameObject::operator=(const GameObject& copy) noexcept
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

	GameObject::~GameObject() noexcept
	{
		auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Object::GameObject");
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

	/*
	bool GameObject::interact(const Enums::InteractionOption& interaction)
	{
		auto comp = getComponent<PlayerInteractionPrompt>();
		if (comp)
		{
			return comp->doInteraction(interaction);
		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Object::GameObject").Warning("Trying to perform interact with an object that has no player interact prompt added to it.");
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
	//*/

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
			
			post(messaging::Topic::of(messaging::Topics::TOGGLE_STATE), std::make_shared<messaging::Body>());
			//
			//Component::ObjectStateActivator* c = getComponent<Component::ObjectStateActivator>();
			//if (c)
			//{
			//	c->toggle();
			//}
		}
		else if (newState == Enums::ObjectState::Inactive && objectState != newState)
		{
			objectState = newState;
			post(messaging::Topic::of(messaging::Topics::TOGGLE_STATE), std::make_shared<messaging::Body>());
			//	Component::ObjectStateActivator* c = getComponent<Component::ObjectStateActivator>();
			//if (c)
			//{
			//	c->toggle();
			//}
		}

	}

	void GameObject::onCollision(GameObject* collider)
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
		of::engine::GetModule<of::module::ObjectInstanceHandler>().removeObject(this, delayedDespawnTime);

	}

	void GameObject::onDelete()
	{
		auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Object::GameObject");
		logger.Debug("OnDelete -> Enter");
		if (unloading)
		{
			logger.Debug("Unloading - Fast return");
			return;
		}
		logger.Debug("OnDelete -> componentMap");
		for (auto& component : componentMap)
		{
			logger.Debug("OnDelete Component Shared Ptr Addr -> " + of::common::toHex((size_t)&component.second));
			logger.Debug("OnDelete Component Addr -> " + of::common::toHex((size_t)component.second.get()));
			logger.Debug("OnDelete Component TypeId -> " + component.first.to_string());
			logger.Debug("OnDelete Component TypeName -> " + component.second->getTypeName());
			component.second->onDelete();
		}
		logger.Debug("OnDelete -> Exit");
	}

	void GameObject::applyGameMode(const of::resource::GameModeModifier& modifier)
	{
		for (auto& trigger : modifier.onDeathTriggers)
		{
			onDeathTriggers.push_back(std::move(trigger->clone()));
		}
		for (auto& mod : modifier.modifierList)
		{
			post(messaging::Topic::of(messaging::Topics::ADD_MODIFIER), std::make_shared<messaging::ModifierId>(mod, 0.f));
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

	component::Base* GameObject::AddComponent(component::Base* componentToAdd)
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

	component::Base* GameObject::AddOrReplaceComponent(component::Base* componentToAdd)
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
};
