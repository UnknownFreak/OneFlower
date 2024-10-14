#pragma once

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

#include <map>

#include <physics/colliderType.hpp>
#include <physics/errorCallback.hpp>
#include <physics/objectType.hpp>
#include <physics/simulationCallback.hpp>

namespace of::gfx
{
	struct Mesh;
}

namespace of::object
{
	class GameObject;
}

namespace of::physics
{

	enum class CollisionLayer
	{
		NONE = 0,
	// if object should hit ground
		GROUND = 1,

	// if object hit statics
		STATIC = 1 << 1,

		NORMAL_STATIC = GROUND | STATIC,

	// if object hit rigids, .e.g player/ actors
		RIGID = 1 << 2,

		DOOR = RIGID,
		NORMAL_RIGID = NORMAL_STATIC | RIGID,

	// used for hitscan & sweeps to detect player, used by enemy attacks
		SWEEP_PLAYER = 1 << 4,

	// used for hitscan & sweeps to detect actors that can be HIT
		SWEEP_ACTOR = 1 << 5,
		
	// used for environmental, or special attacks that can hit both player and actors
		SWEEP_BOTH =  SWEEP_PLAYER | SWEEP_ACTOR,

		SWEEP_EDITOR = 1<<6,

	};

	inline physx::PxU32 getCollisionLayer(const CollisionLayer layer)
	{
		return (physx::PxU32)layer;
	}


	class PhysicsHandler
	{
		bool mShutDown;
		bool mInitialized;

		physx::PxDefaultAllocator mAllocator;
		ErrorCallBack mErrorCallback;
		SimulationCallback mSimulationCallback;

		physx::PxFoundation* mFoundation;
		physx::PxPvd* mPvd;
		physx::PxPhysics* mPhysics;
		physx::PxScene* mScene;
		physx::PxControllerManager* mControllerManager;
		physx::PxMaterial* mMaterial;

		physx::PxTriangleMesh* GetObjectAsPxMesh(std::shared_ptr<of::gfx::Mesh> asset);
		physx::PxConvexMesh* GetObjectAsPxConvex(std::shared_ptr<of::gfx::Mesh> asset);

		//pair<id, id>, shape*?
		//meshid, materialid?
		//materialTypeStruct could contin mesh reference & use it's own id, then no pair is needed
		/*
		struct materialType
		{
			materialTypeenum;
			of::common::uuid mId;
			of::resource::Model& model;
			material list;

		};

		//material type contains enum of generic material type, e.g. wood/ metal/ ice, etc.
		// material list contains the material specific differences, e.g a door with wooden frame/ large metal decorations
		// that can then be designed in the collision mesh itself.
		*/

		std::map<of::common::uuid, physx::PxShape*> mTriangleShapes;
		std::map<of::common::uuid, physx::PxShape*> mConvexShapes;

		physx::PxActor* mHeightPlane;

	public:

		PhysicsHandler();
		~PhysicsHandler();

		void Initialize();
		void shutDown();
		bool hasShutDown() const;

		void simulate(const float dt);

		physx::PxController* createActorController(const glm::vec3& pos);

		physx::PxFixedJoint* createJoint(physx::PxRigidActor* p1, physx::PxRigidActor* p2);

		bool castRay(glm::vec3 start, glm::vec3 end, glm::vec3& hitOut, glm::vec3& hitObjectPos, ObjectType& objectTypeInfo, CollisionLayer layer = CollisionLayer::NONE);

		physx::PxD6Joint* createDoorHinge(physx::PxRigidActor* p, const glm::vec3& hingePosRelOffset);

		void attachTriggerShape(physx::PxRigidActor* actor, std::shared_ptr<of::gfx::Mesh> triggerShape, glm::vec3 offset, glm::vec3 scale);

		void attachBoxTriggerShape(physx::PxRigidActor* actor, glm::vec3 offset, glm::vec3 scale);
		void attachCylinderTriggerShape(physx::PxRigidActor* actor, glm::vec3 offset, glm::vec3 scale);

		private:

			physx::PxRigidStatic* createStatic(const glm::vec3& pos, std::shared_ptr<of::gfx::Mesh> collisionModel, const bool iSTriggerShape, const bool addToScene);
			physx::PxRigidDynamic* createDynamic(const glm::vec3& pos, std::shared_ptr<of::gfx::Mesh> collisionModel, const bool iSTriggerShape, const bool addToScene);
			nullptr_t invalidActor();

		public:

		template <class T>
		T* createActor(const glm::vec3& pos, std::shared_ptr<of::gfx::Mesh> collisionModel, const bool isTriggerShape=false, const bool addToScene=true/*, material type, collisionMesh*/)
		{
			if constexpr (std::same_as<T, physx::PxRigidStatic>)
			{
				return createStatic(pos, collisionModel, isTriggerShape, addToScene);
				
			}
			else if constexpr (std::same_as<T, physx::PxRigidDynamic>)
			{
				return createDynamic(pos, collisionModel, isTriggerShape, addToScene);
			}
			else
			{
				return (T*)invalidActor();
			}
		}
	};

	void init();
	void shutdown();
	PhysicsHandler& get();
}