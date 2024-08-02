#pragma once

#include <utils/common/uuid.hpp>


#include <module/IEngineModule.hpp>
#include <module/EngineResourceTypes.hpp>
#include <logger/Logger.hpp>

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

#include <map>
#include <vector>
#include <engine/settings.hpp>

#include <iostream>

namespace of::resource
{
	class Model;
}

namespace of::object
{
	class GameObject;
}

namespace of::module::physics
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

	enum class ColliderType
	{
		Object,
		ObjectTrigger,
		TerrainCollider,
		Unknown
	};

	inline const char* to_string(ColliderType& t)
	{
		switch (t)
		{
		case ColliderType::Object:
			return "object";
		case ColliderType::ObjectTrigger:
			return "object trigger";
		case ColliderType::TerrainCollider:
			return "terrain collider";
		default:
			return "Unknown";
		}
	}

	struct ObjectType
	{
		ColliderType hitType;
		of::common::uuid objectId;
		physx::PxActor* hitActor = nullptr;
		of::object::GameObject* go = nullptr;;
	};


	class PhysicsHandler : public interface::IEngineResource<PhysicsHandler>
	
	{

		class SimulationCallback :public physx::PxSimulationEventCallback
		{
		public:


			// Inherited via PxSimulationEventCallback
			virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override;
			virtual void onWake(physx::PxActor** actors, physx::PxU32 count) override;
			virtual void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
			virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
			virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
			virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override;
		};

		class RaycastCallback : public physx::PxRaycastCallback
		{
			physx::PxRaycastHit one[1];
		public:

			RaycastCallback(): physx::PxRaycastCallback(one, 1), hitPos(0)
			{
			}

			virtual physx::PxAgain processTouches(const physx::PxRaycastHit* buffer, physx::PxU32 nbHits)
			{
				float d = 10000000.f;
				for(physx::PxU32 i = 0; i < nbHits; i++)
				{
					if (buffer[i].distance < d)
					{
						auto p = buffer[i].actor->getGlobalPose().p;
						hitObjectPos.x = p.x;
						hitObjectPos.y = p.y;
						hitObjectPos.z = p.z;
						d = buffer[i].distance;
						hitPos.x = buffer[i].position.x;
						hitPos.y = buffer[i].position.y;
						hitPos.z = buffer[i].position.z;
						if (buffer[i].actor->userData == nullptr)
						{
							hit.hitType = ColliderType::Unknown;
							hit.objectId = of::common::uuid::nil();
						}
						else
						{
							hit = *(ObjectType*)buffer[i].actor->userData;
						}
						hit.hitActor = buffer[i].actor;

					}
				}
				return true;
			};

			glm::vec3 hitObjectPos;
			glm::vec3 hitPos;
			ObjectType hit;
		};

		class ErrorCallBack : public physx::PxErrorCallback
		{
		public:
			virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;
		};

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

		physx::PxTriangleMesh* GetObjectAsPxMesh(of::resource::Model& asset);
		physx::PxConvexMesh* GetObjectAsPxConvex(of::resource::Model& asset);

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

		EngineResourceType& getType() const;

		physx::PxController* createActorController(const glm::vec3& pos);

		physx::PxFixedJoint* createJoint(physx::PxRigidActor* p1, physx::PxRigidActor* p2)
		{
			return physx::PxFixedJointCreate(*mPhysics, p1, p1->getGlobalPose(), p2, p2->getGlobalPose());
		}

		bool castRay(glm::vec3 start, glm::vec3 end, glm::vec3& hitOut, glm::vec3& hitObjectPos, ObjectType& objectTypeInfo, CollisionLayer layer = CollisionLayer::NONE)
		{
			physx::PxQueryFilterData fd;
			fd.data.word0 = getCollisionLayer(layer);
			//fd.flags |= physx::PxQueryFlag::eANY_HIT;
			RaycastCallback raycastCB = RaycastCallback();
			physx::PxVec3 unitDir(end.x, end.y, end.z);
			bool b = mScene->raycast(physx::PxVec3(start.x, start.y, start.z), physx::PxVec3(end.x, end.y, end.z), 10000.f, raycastCB,
				physx::PxHitFlag::eDEFAULT, fd);
			if (b)
			{
				hitOut = raycastCB.hitPos;
				hitObjectPos = raycastCB.hitObjectPos;
				objectTypeInfo = raycastCB.hit;
			}
			return b;
		}

		physx::PxD6Joint* createDoorHinge(physx::PxRigidActor* p, const glm::vec3& hingePosRelOffset)
		{
			auto offset = physx::PxTransform(physx::PxVec3(0));
			offset.p.x = hingePosRelOffset.x;
			offset.p.y = hingePosRelOffset.y;
			offset.p.z = hingePosRelOffset.z;
			auto joint = physx::PxD6JointCreate(*mPhysics, p, physx::PxTransform(offset), nullptr, p->getGlobalPose());
			//joint->setMotion(physx::PxD6Axis::eTWIST, physx::PxD6Motion::eFREE);
			joint->setMotion(physx::PxD6Axis::eSWING1, physx::PxD6Motion::eLIMITED);
			//joint->setMotion(physx::PxD6Axis::eSWING2, physx::PxD6Motion::eFREE);
			//joint->setMotion(physx::PxD6Axis::eX, physx::PxD6Motion::eFREE);
			//joint->setMotion(physx::PxD6Axis::eZ, physx::PxD6Motion::eFREE);
			//joint->setMotion(physx::PxD6Axis::eY, physx::PxD6Motion::eFREE);
			auto l = physx::PxJointLimitPyramid(0, physx::PxPi/2, 0.f, 0.1f);
			//auto l = physx::PxJointLimitPyramid(-physx::PxPi+0.01f, physx::PxPi - 0.01f, 0.f, 0.1f);
			joint->setPyramidSwingLimit(l);

			if (of::settings::get().usePvdDebugger())
			{
				joint->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);
			}
			return joint;
		}

		void attachTriggerShape(physx::PxRigidActor* actor, of::resource::Model& triggerShape, glm::vec3 offset, glm::vec3 scale);

		void attachBoxTriggerShape(physx::PxRigidActor* actor, glm::vec3 offset, glm::vec3 scale);
		void attachCylinderTriggerShape(physx::PxRigidActor* actor, glm::vec3 offset, glm::vec3 scale);


		template <class T>
		T* createActor(const glm::vec3& pos, of::resource::Model& collisionModel, const bool isTriggerShape=false, const bool addToScene=true/*, material type, collisionMesh*/)
		{
			if constexpr (std::same_as<T, physx::PxRigidStatic>)
			{
				auto actor = mPhysics->createRigidStatic(physx::PxTransform(physx::PxVec3(pos.x, pos.y, pos.z)));
				/*if (mTriangleShapes.find(collisionModel.mId) == mTriangleShapes.end())
				{
					mTriangleShapes[collisionModel.mId] = 
				}*/
				auto shape = mPhysics->createShape(physx::PxTriangleMeshGeometry(GetObjectAsPxMesh(collisionModel)), *mMaterial, false);

				if (isTriggerShape)
				{
					shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
					shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
				}
				actor->attachShape(*shape);
				shape->release();

				if (addToScene)
				{
					mScene->addActor(*actor);
				}
				return actor;
			}
			else if constexpr (std::same_as<T, physx::PxRigidDynamic>)
			{
				auto actor = mPhysics->createRigidDynamic(physx::PxTransform(physx::PxVec3(pos.x, pos.y, pos.z)));
				/*if (mTriangleShapes.find(collisionModel.mId) == mTriangleShapes.end())
				{
					mTriangleShapes[collisionModel.mId] =
				}*/
				auto shape = mPhysics->createShape(physx::PxConvexMeshGeometry(GetObjectAsPxConvex(collisionModel)), *mMaterial, false);
				if (isTriggerShape)
				{
					shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
					shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
				}

				actor->attachShape(*shape);
				shape->release();

				if (addToScene)
				{
					mScene->addActor(*actor);
				}
				return actor;
			}
			else
			{
				/*
				of::engine::GetModule<of::logger::Logger>().getLogger("Physics::createActor").Error("Invalid type argument passed, no actor is created");
				*/
				return nullptr;
			}
		}
	};
}