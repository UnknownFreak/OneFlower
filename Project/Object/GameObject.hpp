#pragma once
#ifndef GameObject_HPP
#define GameObject_HPP

#include <unordered_map>

#include <Helpers/Enum/ObjectState.hpp>
#include <Helpers/Enum/ComponentType.hpp>
#include <Helpers/Enum/InteractionOption.hpp>
#include "IBaseComponent.hpp"

#include <Interfaces/IUpdateable.hpp>
#include <Interfaces/ISimulatable.hpp>

#include "Transform.hpp"
#include <Resources/GameModeModifier.hpp>
#include <Trigger/Trigger.hpp>


class GameObject : public Interfaces::IUpdateable, Interfaces::ISimulatable
{
	friend class Component::Base;
	bool unloading = false;

	std::vector<std::unique_ptr<Trigger::Trigger>> onDeathTriggers;

public:
	Core::uuid id;
	Core::String tag;

	Enums::ObjectState objectState = Enums::ObjectState::Active;

	// TODO: Fix a message struct to set properties.
	void sendMessage(const Core::String& msgType, const Core::String& message);

	GameObject();
	GameObject(GameObject&& copy);
	GameObject(const GameObject& copy);
	GameObject& operator=(const GameObject& copy);
	~GameObject();
	
	bool interact(const Enums::InteractionOption& interaction);
	void interact(const bool& reverseAnimation, const short& repeat);

	void toggleObjectState();
	void toggleObjectState(const Enums::ObjectState& newState);

	void onCollision(GameObject*);
	// Inherited via IUpdateable
	virtual void Update() override;

	// Inherited via ISimulatable
	virtual void Simulate(const float& fElapsedTime) override;
	void Simulate(const float& fElapsedTime, const bool& bUpdate);

	void onDeath(const GameObject* killer, const float& delayedDespawnTime=0, const bool& unloadFlag=false);
	void onDelete();
	void applyGameMode(const Resource::GameModeModifier& modifer);

	void reAttach();

	template <class T, typename... Args>
	T* addComponent(Args... as)
	{
		if (componentMap.find(Component::IBase<T>::typeID) == componentMap.end())
		{
			Component::Base* componentToAttach = new T(as...);
			componentToAttach->attachOn(this);
			return (T*)componentToAttach;
		}
		return nullptr;
	};

	Component::Base* AddComponent(Component::Base* componentToAdd);
	Component::Base* AddOrReplaceComponent(Component::Base* componentToAdd);

	template<class T>
	T* getComponent() const
	{
		auto it = componentMap.find(Component::IBase<T>::typeID);
		return it == componentMap.end() ? nullptr : (T*)it->second.get();
	}

	template<class T>
	std::shared_ptr<T> getSharedComponent() const
	{
		auto it = componentMap.find(Component::IBase<T>::typeID);
		return it == componentMap.end() ? nullptr : std::dynamic_pointer_cast<T>(it->second);
	}

	template<class T>
	bool removeComponent()
	{
		auto const type_id = Component::IBase<T>::typeID;

		if (componentMap.find(type_id) == componentMap.end())
			return false;
		componentMap.erase(type_id);
		return true;
	}

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(id);
		ar(tag);
		ar(componentMap);
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(id);
		ar(tag);
		componentMap.clear();
		ar(componentMap);
		for (auto& it : componentMap)
		{
			it.second->attachOn(this);
		}
	}

protected:
	std::unordered_map<Enums::ComponentType, std::shared_ptr<Component::Base>> componentMap;
};

#endif