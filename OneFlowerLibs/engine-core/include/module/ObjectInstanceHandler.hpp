#ifndef ObjectInstanceHandler_HPP
#define ObjectInstanceHandler_HPP

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

#include <object/GameObject.hpp>
#include <unordered_map>

namespace of::module
{

	class ObjectInstanceHandler : public of::module::interface::IEngineResource<ObjectInstanceHandler>
	{
		
	public:
		object::GameObject* player = nullptr;
		std::unordered_map<of::common::uuid, object::GameObject> objects;
		std::unordered_map<object::GameObject*, float> objectsToDelete;

		object::GameObject* addObject();
		object::GameObject* addObject(const of::common::uuid& uuid);
		object::GameObject* getObject(const of::common::uuid& uuid);

		bool exists(const of::common::uuid& uuid) const;
		object::GameObject* getPlayer() const;

		void removeObject(object::GameObject* object, const float& delayedTime=0);
		void removeObject(const of::common::uuid objectId);

		void processDeletedObjects(const float& elapsedTime);

		void unload();
		void unloadNonUnique();
		void persistGameObjects();
		void resolveObjectReferences();

		of::module::EngineResourceType& getType() const
		{
			return type;
		}
	};
}
#endif