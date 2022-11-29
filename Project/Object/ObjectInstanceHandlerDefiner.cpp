#include "ObjectInstanceHandler.hpp"

#include <imgui/imgui.h>

Enums::EngineResourceType Interfaces::IEngineResource<EngineModule::ObjectInstanceHandler>::type = Enums::EngineResourceType::ObjectInstanceHandler;

GameObject* EngineModule::ObjectInstanceHandler::addObject()
{
	of::common::uuid id;
	return addObject(id);
}

GameObject* EngineModule::ObjectInstanceHandler::addObject(const of::common::uuid& uuid)
{
	objects.insert({ uuid, GameObject() });
	objects[uuid].id = uuid;
	if (onAdd.operator bool())
	{
		onAdd.operator()(&objects[uuid]);
	}
	return &objects[uuid];
}

GameObject* EngineModule::ObjectInstanceHandler::getObject(const of::common::uuid& uuid)
{
	if (exists(uuid))
		return &objects.at(uuid);
	else if (uuid == of::common::uuid::nil())
		return player;
	return nullptr;
}

bool EngineModule::ObjectInstanceHandler::exists(const of::common::uuid& uuid) const
{
	return objects.find(uuid) != objects.end();
}

GameObject* EngineModule::ObjectInstanceHandler::getPlayer() const
{
	return player;
}

void EngineModule::ObjectInstanceHandler::removeObject(GameObject* object, const float& delayedtime)
{
	Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("EngineModule::ObjectInstanceHandler").Info("Removing object " + object->id.to_string());
	objectsToDelete[object] = delayedtime;
	if (onDelete.operator bool())
	{
		onDelete.operator()(object);
	}
}

void EngineModule::ObjectInstanceHandler::removeObject(const of::common::uuid objectId)
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
			auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("EngineModule::ObjectInstanceHandler");
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

void EngineModule::ObjectInstanceHandler::unload()
{
	// TODO: REwork, do a loop and sendOnDelete


	while (objects.size() > 0)
	{
		auto it = objects.begin();
		while (it !=objects.end())
		{
			if (onDelete)
			{
				onDelete(&it->second);
			}
			it = objects.erase(it);
		}
	}
}

void EngineModule::ObjectInstanceHandler::onDeleteAction(std::function<void(GameObject*)> fnPtr)
{
	onDelete = fnPtr;
}

void EngineModule::ObjectInstanceHandler::onAddAction(std::function<void(GameObject*)> fnPtr)
{
	onAdd = fnPtr;
}
