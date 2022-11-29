#ifndef ObjectInstanceHandler_HPP
#define ObjectInstanceHandler_HPP

#include <module/IEngineModule.hpp>
#include <utils/common/uuid.hpp>

#include <unordered_map>

namespace of::object
{
	class GameObject;
}

namespace of::module
{
	class ObjectInstanceHandler : public interface::IEngineResource<ObjectInstanceHandler>
	{
		std::function<void(object::GameObject*)> onAdd;
		std::function<void(object::GameObject*)> onDelete;
	public:
		object::GameObject* player = nullptr;
		std::unordered_map<common::uuid, object::GameObject> objects;
		std::unordered_map<object::GameObject*, float> objectsToDelete;

		object::GameObject* addObject();
		object::GameObject* addObject(const common::uuid& uuid);
		object::GameObject* getObject(const common::uuid& uuid);

		bool exists(const common::uuid& uuid) const;
		object::GameObject* getPlayer() const;

		void removeObject(object::GameObject* object, const float& delayedTime=0);
		void removeObject(const common::uuid objectId);

		void processDeletedObjects(const float& elapsedTime);

		void unload();

		void onDeleteAction(std::function<void(object::GameObject*)> fnPtr);
		void onAddAction(std::function<void(object::GameObject*)> fnPtr);

		of::module::EngineResourceType& getType() const
		{
			return type;
		}
	};
}
#endif