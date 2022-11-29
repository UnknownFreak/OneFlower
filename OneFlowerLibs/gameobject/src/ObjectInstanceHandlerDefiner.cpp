#include <module/ObjectInstanceHandler.hpp>

#include <gameobject/GameObject.hpp>

#include <module/ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::ObjectInstanceHandler>::type = of::module::EngineResourceType::ObjectInstanceHandler;

namespace of::module
{

	using namespace of::object;
	GameObject* ObjectInstanceHandler::addObject()
	{
		common::uuid id;
		return addObject(id);
	}

	GameObject* ObjectInstanceHandler::addObject(const common::uuid& uuid)
	{
		objects.insert({ uuid, GameObject() });
		objects[uuid].id = uuid;
		if (onAdd.operator bool())
		{
			onAdd.operator()(&objects[uuid]);
		}
		return &objects[uuid];
	}

	GameObject* ObjectInstanceHandler::getObject(const common::uuid& uuid)
	{
		if (exists(uuid))
			return &objects.at(uuid);
		else if (uuid == common::uuid::nil())
			return player;
		return nullptr;
	}

	bool ObjectInstanceHandler::exists(const common::uuid& uuid) const
	{
		return objects.find(uuid) != objects.end();
	}

	GameObject* ObjectInstanceHandler::getPlayer() const
	{
		return player;
	}

	void ObjectInstanceHandler::removeObject(GameObject* object, const float& delayedtime)
	{
		of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("module::ObjectInstanceHandler").Info("Removing object " + object->id.to_string());
		objectsToDelete[object] = delayedtime;
		if (onDelete.operator bool())
		{
			onDelete.operator()(object);
		}
	}

	void ObjectInstanceHandler::removeObject(const common::uuid objectId)
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
				auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("module::ObjectInstanceHandler");
				logger.Info("Processing removal of " + id.to_string());
				logger.Debug(common::toHex((size_t)&it->first));
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

	void ObjectInstanceHandler::unload()
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

	void ObjectInstanceHandler::onDeleteAction(std::function<void(GameObject*)> fnPtr)
	{
		onDelete = fnPtr;
	}

	void ObjectInstanceHandler::onAddAction(std::function<void(GameObject*)> fnPtr)
	{
		onAdd = fnPtr;
	}
}
