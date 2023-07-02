#pragma once
#ifndef GameObject_HPP
#define GameObject_HPP

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>
#include <utils/concepts/concepts.hpp>

#include <file/FileId.hpp>

#include <unordered_map>
#include <cereal/types/unordered_map.hpp>

#include "messaging/ComponentMessage.hpp"

#include "ObjectState.hpp"

#include "component/BaseComponent.hpp"

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

		std::vector<std::unique_ptr<of::resource::trigger::Trigger>> onDeathTriggers;

		void resolveReferences();

	public:
		of::common::uuid id;
		of::common::String tag;

		of::module::SaveSetting saveSetting = of::module::SaveSetting::NEVER_STORE;
		ObjectState objectState = ObjectState::Active;
		bool keepSavedOnObjectDelete = false;
		bool unique = false;
		of::file::FileId prefabId;

		void initialize();
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
			auto comp = get<T>();
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

		void onDeath(const GameObject* killer, const float& delayedDespawnTime=0, const bool& unloadFlag=false);
		void onDelete();
		void applyGameMode(const of::resource::GameModeModifier& modifer);

		void reAttach();

		template <class T, typename... Args>
			requires std::derived_from<T, component::Base> && 
		std::constructible_from<T, Args...> &&
			of::utils::concepts::has_typeId_member<T>
		T* add(Args... as)
		{
			if (componentMap.find(T::typeId) == componentMap.end())
			{
				component::Base* componentToAttach = new T(as...);
				componentToAttach->attachOn(this);
				return (T*)componentToAttach;
			}
			return nullptr;
		};

		component::Base* add(component::Base* componentToAdd);
		component::Base* addOrReplace(component::Base* componentToAdd);

		template<class T>
			requires std::derived_from<T, component::Base> &&
		of::utils::concepts::has_typeId_member<T>
		T* get() const
		{
			auto it = componentMap.find(T::typeId);
			return it == componentMap.end() ? nullptr : (T*)it->second.get();
		}

		template<class T>
			requires std::derived_from<T, component::Base> &&
		of::utils::concepts::has_typeId_member<T>
		std::shared_ptr<T> getShared() const
		{
			auto it = componentMap.find(T::typeId);
			return it == componentMap.end() ? nullptr : std::dynamic_pointer_cast<T>(it->second);
		}

		template<class T>
			requires std::derived_from<T, component::Base>&&
		of::utils::concepts::has_typeId_member<T>
		bool remove()
		{
			auto constexpr type_id = T::typeId;

			if (componentMap.find(type_id) == componentMap.end())
				return false;
			componentMap.erase(type_id);
			return true;
		}

		ObjectSaveState* getCurrentSaveState();
		void persistIf(const of::module::SaveSetting& persist);
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