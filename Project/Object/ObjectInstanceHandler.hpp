#ifndef ObjectInstanceHandler_HPP
#define ObjectInstanceHandler_HPP

#include <Interfaces/IEngineModule.hpp>

#include "GameObject.hpp"
#include <unordered_map>

namespace EngineModule
{
	class ObjectInstanceHandler : public Interfaces::IEngineResource<ObjectInstanceHandler>
	{
		std::function<void(GameObject*)> onAdd;
		std::function<void(GameObject*)> onDelete;
	public:
		GameObject* player = nullptr;
		std::unordered_map<Core::uuid, GameObject> objects;
		std::unordered_map<GameObject*, float> objectsToDelete;

		GameObject* addObject();
		GameObject* addObject(const Core::uuid& uuid);
		GameObject* getObject(const Core::uuid& uuid);

		bool exists(const Core::uuid& uuid) const;
		GameObject* getPlayer() const;

		void removeObject(GameObject* object, const float& delayedTime=0);
		void removeObject(const Core::uuid objectId);

		void processDeletedObjects(const float& elapsedTime);

		void unload();

		void onDeleteAction(std::function<void(GameObject*)> fnPtr);
		void onAddAction(std::function<void(GameObject*)> fnPtr);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}
#endif