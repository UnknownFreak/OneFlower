#include <object/GameObject.hpp>

#include <component/transform.hpp>
#include <object/ObjectSaveState.hpp>

#include <object/InstanceHandler.hpp>
#include <file/SaveFile.hpp>
#include <logger/Logger.hpp>

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
		//add<component::Transform>();
		for (auto& c : componentMap)
		{
			c.second->initialize();
		}
	}

	GameObject::GameObject() noexcept
	{
		add<component::Transform>();
	}

	GameObject::GameObject(GameObject&& copy) noexcept
	{
		componentMap = std::move(copy.componentMap);
		for (auto& x : componentMap)
		{
			x.second.get()->attach();
		}
		copy.componentMap.clear();
	}
	GameObject::GameObject(const GameObject& copy) noexcept
	{
		for (auto& x : copy.componentMap)
		{
			add(std::shared_ptr<of::component::Base>(x.second->copy()));
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
			add(std::shared_ptr<of::component::Base>(x.second->copy()));
		}
		initialize();
		return *this;
	}

	GameObject::~GameObject() noexcept
	{
		auto& logger = of::logger::get().getLogger("Object::GameObject");
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
			of::logger::get().getLogger("Object::GameObject").Warning("Trying to perform interact with an object that has no player interact prompt added to it.");
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

	void GameObject::toggleObjectState(const ObjectState newState)
	{
		if ((newState == ObjectState::Active && objectState != newState) || (objectState == ObjectState::Inactive && objectState != newState))
		{
			objectState = newState;
			
			post(messaging::Topic::of(messaging::Topics::TOGGLE_STATE), std::make_shared<messaging::Body>());
		}
		persistIf(of::file::SaveSetting::PERSIST_ON_INTERACT);
	}

	void GameObject::onCollision(GameObject* collider)
	{
		if (objectState == ObjectState::Active)
		{
			using namespace of::object::messaging;
			post(Topic::of(Topics::ON_COLLISION), std::make_shared<GameObjectPtr>(collider));
		}
	}

	void GameObject::onDeath(const GameObject* killer, const float delayedDespawnTime, const bool unloadFlag)
	{
		using namespace of::object::messaging;
		//unloading = unloadFlag;
		if (!unloadFlag)
		{
			post(Topic::of(Topics::ON_DEATH), std::make_shared<GameObjectPtr>(killer));
		}
		of::object::removeObject(id, delayedDespawnTime);
	}

	void GameObject::onDelete()
	{
		auto& logger = of::logger::get().getLogger("Object::GameObject");
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
			auto& saveFile = of::engine::GetModule<of::file::SaveFile>();
			saveFile.remove(of::file::FileId(id));
		}
		else if (keepSavedOnObjectDelete && unique)
		{
			auto& saveFile = of::engine::GetModule<of::file::SaveFile>();
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

	component::Base* GameObject::add(std::shared_ptr<of::component::Base> componentToAdd)
	{
		if (componentMap.find(componentToAdd->getType()) == componentMap.end())
		{
			componentMap.insert(std::make_pair(componentToAdd->getType(), componentToAdd));
			componentToAdd->attachedOn = this;
			componentToAdd->attach();
			return componentToAdd.get();
		}
		return nullptr;
	}

	component::Base* GameObject::addOrReplace(std::shared_ptr<of::component::Base> componentToAdd)
	{
		if (componentMap.find(componentToAdd->getType()) != componentMap.end())
		{
			componentMap[componentToAdd->getType()]->decouple();
			componentMap.erase(componentToAdd->getType());
		}
		return add(componentToAdd);
	}

	ObjectSaveState* GameObject::getCurrentSaveState()
	{
		auto& saveFile = of::engine::GetModule<of::file::SaveFile>();
		of::file::FileId tmp(id);
		if (!saveFile.exists(tmp))
		{
			saveFile.setState(tmp, std::make_unique<ObjectSaveState>());
		}
		auto state = saveFile.getState<ObjectSaveState>(tmp);
		state->objectState = objectState;
		return state;
	}

	void GameObject::persistIf(const of::file::SaveSetting persist)
	{
		if (persist != of::file::SaveSetting::NEVER_STORE && saveSetting == persist)
		{
			auto& saveFile = of::engine::GetModule<of::file::SaveFile>();
			of::file::FileId tmp(id);
			if (!saveFile.exists(tmp))
			{
				saveFile.setState(tmp, std::make_unique<ObjectSaveState>());
			}
			auto state = saveFile.getState<ObjectSaveState>(tmp);
			if (saveSetting == of::file::SaveSetting::SPECIAL_RE_CONSTRUCT)
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

	void GameObject::loadPersisted()
	{
		auto& saveFile = of::engine::GetModule<of::file::SaveFile>();
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
