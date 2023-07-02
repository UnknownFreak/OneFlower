#include <module/ObjectInstanceHandler.hpp>
#include <module/logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::ObjectInstanceHandler>::type = of::module::EngineResourceType::ObjectInstanceHandler;

namespace of::module
{

	object::GameObject* ObjectInstanceHandler::addObject()
	{
		of::common::uuid id;
		return addObject(id);
	}

	object::GameObject* ObjectInstanceHandler::addObject(const of::common::uuid& uuid)
	{
		// in place default construct gameobject by accessing element id.
		object::GameObject* o = &objects[uuid];
		o->id = uuid;
		o->initialize();
		return o;
	}

	object::GameObject* ObjectInstanceHandler::getObject(const of::common::uuid& uuid)
	{
		if (exists(uuid))
			return &objects.at(uuid);
		else if (uuid == of::common::uuid::nil())
			return player;
		return nullptr;
	}

	bool ObjectInstanceHandler::exists(const of::common::uuid& uuid) const
	{
		return objects.find(uuid) != objects.end();
	}

	object::GameObject* ObjectInstanceHandler::getPlayer() const
	{
		return player;
	}

	void ObjectInstanceHandler::removeObject(of::common::uuid objectId, const float& delayedtime)
	{
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("EngineModule::ObjectInstanceHandler").Info("Removing object " + objectId.to_string());
		objectsToDelete[objectId] = delayedtime;
	}

	void ObjectInstanceHandler::processDeletedObjects(const float& elapsedTime)
	{
		auto it = objectsToDelete.begin();
		while (it != objectsToDelete.end())
		{
			it->second -= elapsedTime;
			if (it->second < 0)
			{
				auto id = it->first;
				auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("EngineModule::ObjectInstanceHandler");
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

	void ObjectInstanceHandler::unloadAll()
	{
		objects.clear();
		objectsToDelete.clear();
		//auto it = objects.begin();
		//while (it !=objects.end())
		//{
		//	it = objects.erase(it);
		//}
	}

	void ObjectInstanceHandler::unloadNonUnique()
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

	void ObjectInstanceHandler::persistGameObjects()
	{
		for (auto& i : objects)
		{
			i.second.persistIf(of::module::SaveSetting::PERSIST_ON_SAVE);
			i.second.persistIf(of::module::SaveSetting::SPECIAL_RE_CONSTRUCT);
		}
	}

	void ObjectInstanceHandler::resolveObjectReferences()
	{
		for (auto& i : objects)
		{
			i.second.resolveReferences();
		}
	}
}
