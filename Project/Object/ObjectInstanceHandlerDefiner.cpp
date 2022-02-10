#include "ObjectInstanceHandler.hpp"

Enums::EngineResourceType Interfaces::IEngineResource<EngineModule::ObjectInstanceHandler>::type = Enums::EngineResourceType::ObjectInstanceHandler;

GameObject* EngineModule::ObjectInstanceHandler::addObject()
{
	Core::uuid id;
	return addObject(id);
}

GameObject* EngineModule::ObjectInstanceHandler::addObject(const Core::uuid& uuid)
{
	objects.insert({ uuid, GameObject() });
	objects[uuid].id = uuid;
	return &objects[uuid];
}

GameObject* EngineModule::ObjectInstanceHandler::getObject(const Core::uuid& uuid)
{
	if (exists(uuid))
		return &objects.at(uuid);
	else if (uuid == Core::uuid::nil())
		return player;
	return nullptr;
}

bool EngineModule::ObjectInstanceHandler::exists(const Core::uuid& uuid) const
{
	return objects.find(uuid) != objects.end();
}

GameObject* EngineModule::ObjectInstanceHandler::getPlayer() const
{
	return player;
}

void EngineModule::ObjectInstanceHandler::removeObject(GameObject* object, const float& delayedtime)
{
	Engine::GetModule<EngineModule::Logger::OneLogger>().Fine("Removing object " + object->id.to_string());
	objectsToDelete[object] = delayedtime;
}

void EngineModule::ObjectInstanceHandler::removeObject(const Core::uuid objectId)
{
	removeObject(getObject(objectId));
}

void EngineModule::ObjectInstanceHandler::processDeletedObjects(const float& elapsedTime)
{
	auto it = objectsToDelete.begin();
	while (it != objectsToDelete.end())
	{
		it->second -= elapsedTime;
		if (it->second < 0)
		{
			auto id = it->first->id;
			Engine::GetModule<EngineModule::Logger::OneLogger>().Fine("Processing removal of " + id.to_string());
			Engine::GetModule<EngineModule::Logger::OneLogger>().Debug(Core::toHex((size_t)&it->first));
			it->first->onDelete();
			objects.erase(id);
			it = objectsToDelete.erase(it);
		}
	}
}

void EngineModule::ObjectInstanceHandler::unload()
{
	while (objects.size() > 0)
	{
		objects.clear();
	}
}
