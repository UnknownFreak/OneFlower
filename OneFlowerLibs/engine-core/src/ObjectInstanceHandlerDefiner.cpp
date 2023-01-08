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
		objects.insert({ uuid, object::GameObject() });
		objects[uuid].id = uuid;
		return &objects[uuid];
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

	void ObjectInstanceHandler::removeObject(object::GameObject* object, const float& delayedtime)
	{
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("EngineModule::ObjectInstanceHandler").Info("Removing object " + object->id.to_string());
		objectsToDelete[object] = delayedtime;
	}

	void ObjectInstanceHandler::removeObject(const of::common::uuid objectId)
	{
		removeObject(getObject(objectId));
	}

	void ObjectInstanceHandler::processDeletedObjects(const float& elapsedTime)
	{
		auto it = objectsToDelete.begin();
		while (it != objectsToDelete.end())
		{
			it->second -= elapsedTime;
			if (it->second < 0)
			{
				auto id = it->first->id;
				auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("EngineModule::ObjectInstanceHandler");
				logger.Fine("Processing removal of " + id.to_string());
				logger.Debug(of::common::toHex((size_t)&it->first));
				it->first->onDelete();
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
		//auto it = objects.begin();
		//while (it !=objects.end())
		//{
		//	it = objects.erase(it);
		//}
	}

	void ObjectInstanceHandler::unloadNonUnique()
	{
		// TODO: replace with std erase_if()???
		auto it = objects.begin();
		while (it != objects.end())
		{
			if (it->second.unique == false)
			{
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
			i.second.persist(of::module::SaveSetting::PERSIST_ON_SAVE);
			i.second.persist(of::module::SaveSetting::SPECIAL_RE_CONSTRUCT);
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
