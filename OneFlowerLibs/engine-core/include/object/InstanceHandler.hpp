#pragma once

#include <object/GameObject.hpp>
#include <unordered_map>

namespace of::object
{

	class InstanceHandler
	{
		
	public:
		// TODO: move to private
		object::GameObject* player = nullptr;
		std::unordered_map<of::common::uuid, object::GameObject> objects;
		std::unordered_map<of::common::uuid, float> objectsToDelete;

		object::GameObject* createPlayer();
		//save state, unloadmode
		/*
		* static = never
		* interactables = on_interact
		* 
		SaveState{
			NEVER,
			ON_INTERACT,
			ON_SAVE,
			SPECIAL_RE_CONSTRUCT

		}
		UnloadMode
		{
		Default, = normal objects & enemies
		Never, = player & player summons & attached effects
		IfDead, same as never, but only if it dies, e.g chase npc through levels, never unloads it, but only once it dies.
		}
		
		*/
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

		InstanceHandler& operator=(const InstanceHandler&) = delete;
	};

	InstanceHandler& get();
	GameObject* addObject();
	GameObject* addObject(const of::common::uuid& id);
	GameObject* getObject(const of::common::uuid& id);
	void removeObject(const of::common::uuid& id, const float delayedTime = 0.f);
}
