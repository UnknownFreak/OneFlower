#include <object/InstanceHandler.hpp>

#include <object/internalInstanceHandler.hpp>
#include <logger/Logger.hpp>

of::object::InstanceHandler* g_instanceHandler = nullptr;

namespace of::object
{

	object::GameObject* InstanceHandler::createPlayer()
	{
		if (player != nullptr)
		{
			delete player;
		}
		player = new GameObject();
		player->tag = "player";
		player->id = of::common::uuid::nil();
		return player;
	}

	object::GameObject* InstanceHandler::addObject()
	{
		of::common::uuid id;
		return addObject(id);
	}

	object::GameObject* InstanceHandler::addObject(const of::common::uuid& uuid)
	{
		// in place default construct gameobject by accessing element id.
		object::GameObject* o = &objects[uuid];
		o->id = uuid;
		o->initialize();
		return o;
	}

	object::GameObject* InstanceHandler::getObject(const of::common::uuid& uuid)
	{
		if (exists(uuid))
			return &objects.at(uuid);
		else if (uuid == of::common::uuid::nil())
			return player;
		return nullptr;
	}

	bool InstanceHandler::exists(const of::common::uuid& uuid) const
	{
		return objects.find(uuid) != objects.end();
	}

	object::GameObject* InstanceHandler::getPlayer() const
	{
		return player;
	}

	void InstanceHandler::removeObject(const of::common::uuid& objectId, const float delayedtime)
	{
		of::logger::get().getLogger("EngineModule::InstanceHandler").Info("Removing object " + objectId.to_string());
		objectsToDelete[objectId] = delayedtime;
	}

	void InstanceHandler::processDeletedObjects(const float elapsedTime)
	{
		auto it = objectsToDelete.begin();
		while (it != objectsToDelete.end())
		{
			it->second -= elapsedTime;
			if (it->second < 0)
			{
				auto id = it->first;
				auto& logger = of::logger::get().getLogger("EngineModule::InstanceHandler");
				logger.Fine("Processing removal of " + id.to_string());
				logger.Debug(of::common::toHex((size_t)&it->first));
				objects[id].onDelete();
				objects.erase(id);
				it = objectsToDelete.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void InstanceHandler::unloadAll()
	{
		objects.clear();
		objectsToDelete.clear();
	}

	void InstanceHandler::unloadNonUnique()
	{
		auto it = objects.begin();
		while (it != objects.end())
		{
			if (it->second.unique == false)
			{
				objectsToDelete.erase(it->first);
				it = objects.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void InstanceHandler::persistGameObjects()
	{
		for (auto& i : objects)
		{
			i.second.persistIf(of::file::SaveSetting::PERSIST_ON_SAVE);
			i.second.persistIf(of::file::SaveSetting::SPECIAL_RE_CONSTRUCT);
		}
	}

	void InstanceHandler::resolveObjectReferences()
	{
		for (auto& i : objects)
		{
			i.second.resolveReferences();
		}
	}

	void init()
	{
		if (g_instanceHandler == nullptr)
		{
			of::logger::get().Info("Initializing ObjectInstanceHandler");
			g_instanceHandler = new InstanceHandler();
		}
	}

	void shutdown()
	{
		delete g_instanceHandler;
		g_instanceHandler = nullptr;
	}

	InstanceHandler& get()
	{
		return *g_instanceHandler;
	}

	GameObject* addObject()
	{
		return g_instanceHandler->addObject();
	}

	GameObject* addObject(const of::common::uuid& uuid)
	{
		return g_instanceHandler->addObject(uuid);
	}

	GameObject* getObject(const of::common::uuid& uuid)
	{
		return g_instanceHandler->getObject(uuid);
	}

	void removeObject(const of::common::uuid& id, const float delayedTime)
	{
		g_instanceHandler->removeObject(id, delayedTime);
	}

}
