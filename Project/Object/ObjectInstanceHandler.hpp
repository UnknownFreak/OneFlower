#ifndef ObjectInstanceHandler_HPP
#define ObjectInstanceHandler_HPP

#include <module/IEngineModule.hpp>

#include "GameObject.hpp"
#include <unordered_map>

namespace EngineModule
{
	class ObjectInstanceHandler : public of::module::interface::IEngineResource<ObjectInstanceHandler>
	{
		std::function<void(GameObject*)> onAdd;
		std::function<void(GameObject*)> onDelete;
	public:
		GameObject* player = nullptr;
		std::unordered_map<of::common::uuid, GameObject> objects;
		std::unordered_map<GameObject*, float> objectsToDelete;

		GameObject* addObject();
		GameObject* addObject(const of::common::uuid& uuid);
		GameObject* getObject(const of::common::uuid& uuid);

		bool exists(const of::common::uuid& uuid) const;
		GameObject* getPlayer() const;

		void removeObject(GameObject* object, const float& delayedTime=0);
		void removeObject(const of::common::uuid objectId);

		void processDeletedObjects(const float& elapsedTime);

		void unload();

		void onDeleteAction(std::function<void(GameObject*)> fnPtr);
		void onAddAction(std::function<void(GameObject*)> fnPtr);

		of::module::EngineResourceType& getType() const
		{
			return type;
		}
	};
}
#endif