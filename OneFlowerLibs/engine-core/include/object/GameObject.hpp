#pragma once
#ifndef GameObject_HPP
#define GameObject_HPP

#include <unordered_map>
#include <cereal/types/unordered_map.hpp>

#include "messaging/ComponentMessage.hpp"

#include "ObjectState.hpp"

#include "component/IBaseComponent.hpp"

#include <resource/GameModeModifier.hpp>
#include <resource/trigger/Trigger.hpp>

#include <module/SaveSetting.hpp>

namespace of::module
{
	class ObjectInstanceHandler;
}

namespace of::object
{
	class ObjectSaveState;

	class GameObject
	{
		friend class of::module::ObjectInstanceHandler;
		friend class component::Base;
		bool unloading = false;

		std::vector<std::unique_ptr<of::resource::trigger::Trigger>> onDeathTriggers;


		void resolveReferences();

	public:
		of::common::uuid id;
		of::common::String tag;

		of::module::SaveSetting saveSetting = of::module::SaveSetting::NEVER_STORE;
		ObjectState objectState = ObjectState::Active;
		bool keepSavedOnObjectDelete = false;
		bool unique = false;

		void post(const messaging::Topic& topic, std::shared_ptr<messaging::Body> message);
		void post(const messaging::Message& message);

		bool post(const common::uuid& id, const messaging::Topic& topic, std::shared_ptr<messaging::Body> message);
		bool post(const common::uuid& id, const messaging::Message& message);

		template<class T>
			requires std::derived_from<T, component::Base>
		bool post(const messaging::Topic& topic, std::shared_ptr<messaging::Body> message)
		{
			return post<T>({ topic, message });
		}

		template<class T>
		requires std::derived_from<T, component::Base>
		bool post(const messaging::Message& message)
		{
			auto comp = getComponent<T>();
			if (comp)
			{
				comp->onMessage(message);
				return true;
			}
			return false;
		}

		GameObject() noexcept;
		GameObject(GameObject&& copy) noexcept;
		GameObject(const GameObject& copy) noexcept;
		GameObject& operator=(const GameObject& copy) noexcept;
		~GameObject() noexcept;
	
		//bool interact(const Enums::InteractionOption& interaction);
		//void interact(const bool& reverseAnimation, const short& repeat);

		void toggleObjectState();
		void toggleObjectState(const ObjectState& newState);

		void onCollision(GameObject*);
		// Inherited via IUpdateable
		void Update();

		// Inherited via ISimulatable
		void Simulate(const float& fElapsedTime);
		void Simulate(const float& fElapsedTime, const bool& bUpdate);

		void onDeath(const GameObject* killer, const float& delayedDespawnTime=0, const bool& unloadFlag=false);
		void onDelete();
		void applyGameMode(const of::resource::GameModeModifier& modifer);

		void reAttach();

		template <class T, typename... Args>
			requires std::derived_from<T, component::Base> && std::constructible_from<T, Args...>
		T* addComponent(Args... as)
		{
			if (componentMap.find(component::IBase<T>::typeID) == componentMap.end())
			{
				component::Base* componentToAttach = new T(as...);
				componentToAttach->attachOn(this);
				return (T*)componentToAttach;
			}
			return nullptr;
		};

		component::Base* AddComponent(component::Base* componentToAdd);
		component::Base* AddOrReplaceComponent(component::Base* componentToAdd);

		template<class T>
			requires std::derived_from<T, component::Base>
		T* getComponent() const
		{
			auto it = componentMap.find(component::IBase<T>::typeID);
			return it == componentMap.end() ? nullptr : (T*)it->second.get();
		}

		template<class T>
			requires std::derived_from<T, component::Base>
		std::shared_ptr<T> getSharedComponent() const
		{
			auto it = componentMap.find(component::IBase<T>::typeID);
			return it == componentMap.end() ? nullptr : std::dynamic_pointer_cast<T>(it->second);
		}

		template<class T>
			requires std::derived_from<T, component::Base>
		bool removeComponent()
		{
			auto const type_id = component::IBase<T>::typeID;

			if (componentMap.find(type_id) == componentMap.end())
				return false;
			componentMap.erase(type_id);
			return true;
		}

		ObjectSaveState* getCurrentSaveState();
		void persist(const of::module::SaveSetting& persist);
		void onReconstruct();

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
		std::unordered_map<of::common::uuid, std::shared_ptr<component::Base>> componentMap;
	};
};


#endif