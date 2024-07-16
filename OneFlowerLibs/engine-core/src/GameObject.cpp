#include <object/GameObject.hpp>

#include <object/component/Transform.hpp>
#include <object/ObjectSaveState.hpp>

#include <object/InstanceHandler.hpp>
#include <module/SaveFile.hpp>
#include <module/logger/OneLogger.hpp>

namespace of::object
{

	void GameObject::resolveReferences()
	{
		for (auto& it : componentMap)
		{
			it.second->resolveReferences();
		}
	}

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

	bool GameObject::post(const common::uuid& id_, const messaging::Topic& topic, std::shared_ptr<messaging::Body> message)
	{
		return post(id_, { topic, message });
	}

	bool GameObject::post(const common::uuid& id_, const messaging::Message& message)
	{
		auto comp = componentMap.find(id_);
		if (comp != componentMap.end())
		{
			comp->second->onMessage(message);
			return true;
		}
		return false;
	}

	void GameObject::initialize()
	{
		add<component::Transform>();
	}

	GameObject::GameObject() noexcept
	{
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
			add(x.second->copy());
		}
	}

	GameObject& GameObject::operator=(const GameObject& copy) noexcept
	{
		id = copy.id;
		for (auto& x : componentMap)
		{
			x.second->decouple();
		}
		componentMap.clear();
		for (auto& x : copy.componentMap)
		{
			add(x.second->copy());
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
			x.second.get()->decouple();
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
		ObjectState state = ObjectState::Active;
		if (objectState == ObjectState::Active)
			state = ObjectState::Inactive;

		toggleObjectState(state);
	}

	void GameObject::toggleObjectState(const ObjectState& newState)
	{
		if ((newState == ObjectState::Active && objectState != newState) || (objectState == ObjectState::Inactive && objectState != newState))
		{
			objectState = newState;
			
			post(messaging::Topic::of(messaging::Topics::TOGGLE_STATE), std::make_shared<messaging::Body>());
		}
		persistIf(of::module::SaveSetting::PERSIST_ON_INTERACT);
	}

	void GameObject::onCollision(GameObject* collider)
	{
		if (objectState == ObjectState::Active)
		{
			using namespace of::object::messaging;
			post(Topic::of(Topics::ON_COLLISION), std::make_shared<GameObjectPtr>(collider));
		}
	}

	void GameObject::onDeath(const GameObject* killer, const float& delayedDespawnTime, const bool& unloadFlag)
	{
		using namespace of::object::messaging;
		//unloading = unloadFlag;
		if (!unloadFlag)
		{
			post(Topic::of(Topics::ON_DEATH), std::make_shared<GameObjectPtr>(killer));
		}
		of::engine::GetModule<of::object::InstanceHandler>().removeObject(id, delayedDespawnTime);
	}

	void GameObject::onDelete()
	{
		auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Object::GameObject");
		logger.Debug("OnDelete -> Enter");
		//if (unloading)
		//{
		//	logger.Debug("Unloading - Fast return");
		//	return;
		//}
		logger.Debug("OnDelete -> componentMap");
		for (auto& component : componentMap)
		{
			using namespace of::object::messaging;
			logger.Debug("OnDelete Component Shared Ptr Addr -> " + of::common::toHex((size_t)&component.second));
			logger.Debug("OnDelete Component Addr -> " + of::common::toHex((size_t)component.second.get()));
			logger.Debug("OnDelete Component TypeId -> " + component.first.to_string());
			logger.Debug("OnDelete Component TypeName -> " + component.second->getTypeName());
			post(component.first, Topic::of(Topics::ON_DELETE), std::make_shared<Body>());
		}

		if (keepSavedOnObjectDelete == false)
		{
			logger.Debug("Clearing object persistance status");
			auto& saveFile = of::engine::GetModule<of::module::SaveFile>();
			saveFile.remove(of::file::FileId(id));
		}
		else if (keepSavedOnObjectDelete && unique)
		{
			auto& saveFile = of::engine::GetModule<of::module::SaveFile>();
			auto saveState = saveFile.getState<ObjectSaveState>(of::file::FileId(id));
			saveState->objectState = ObjectState::NoRecreate;
			saveState->objectSaveStates.clear();
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
			x.second->decouple();
			x.second->attachOn(this);
		}
	}

	component::Base* GameObject::add(component::Base* componentToAdd)
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

	component::Base* GameObject::addOrReplace(component::Base* componentToAdd)
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

	ObjectSaveState* GameObject::getCurrentSaveState()
	{
		auto& saveFile = of::engine::GetModule<of::module::SaveFile>();
		of::file::FileId tmp(id);
		if (!saveFile.exists(tmp))
		{
			saveFile.setState(tmp, std::make_unique<ObjectSaveState>());
		}
		auto state = saveFile.getState<ObjectSaveState>(tmp);
		state->objectState = objectState;
		return state;
	}

	void GameObject::persistIf(const of::module::SaveSetting& persist)
	{
		if (persist != of::module::SaveSetting::NEVER_STORE && saveSetting == persist)
		{
			auto& saveFile = of::engine::GetModule<of::module::SaveFile>();
			of::file::FileId tmp(id);
			if (!saveFile.exists(tmp))
			{
				saveFile.setState(tmp, std::make_unique<ObjectSaveState>());
			}
			auto state = saveFile.getState<ObjectSaveState>(tmp);
			if (saveSetting == of::module::SaveSetting::SPECIAL_RE_CONSTRUCT)
			{
				state->prefabId = prefabId;
			}
			state->objectState = objectState;
			for (auto& it : componentMap)
			{
				it.second->persist(state);
			}
		}
	}

	void GameObject::onReconstruct()
	{
		auto& saveFile = of::engine::GetModule<of::module::SaveFile>();
		of::file::FileId tmp(id);
		if (saveFile.exists(tmp))
		{
			auto state = saveFile.getState<ObjectSaveState>(tmp);
			objectState = state->objectState;
			for (auto& it : componentMap)
			{
				it.second->onReconstruct(state);
			}
		}
	}
};
