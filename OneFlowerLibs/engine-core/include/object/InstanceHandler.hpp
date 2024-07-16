#ifndef InstanceHandler_HPP
#define InstanceHandler_HPP

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

#include <object/GameObject.hpp>
#include <unordered_map>

namespace of::object
{

	class InstanceHandler : public of::module::interface::IEngineResource<InstanceHandler>
	{
		
	public:
		// TODO: move to private
		object::GameObject* player = nullptr;
		std::unordered_map<of::common::uuid, object::GameObject> objects;
		std::unordered_map<of::common::uuid, float> objectsToDelete;

		object::GameObject* addObject();
		object::GameObject* addObject(const of::common::uuid& uuid);
		object::GameObject* getObject(const of::common::uuid& uuid);

		bool exists(const of::common::uuid& uuid) const;
		object::GameObject* getPlayer() const;

		void removeObject(const of::common::uuid& objectId, const float delayedTime=0.f);

		void processDeletedObjects(const float elapsedTime);

		void unloadAll();
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