#pragma once

#include <utils/common/uuid.hpp>


#include <module/IEngineModule.hpp>
#include <module/EngineResourceTypes.hpp>
#include <module/logger/OneLogger.hpp>

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

#include <map>
#include <vector>

namespace of::resource
{
	class Model;
}



namespace of::module::physics
{

	namespace {
		class DisableActor
		{
			physx::PxActor* a;
		public:

			DisableActor(physx::PxActor* a) : a(a)
			{

			}

			virtual  void           run()
			{
				//a->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);
				//a->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, true);
			}
		};
	}

	class PhysicsHandler : public interface::IEngineResource<PhysicsHandler>
	
	{

		class SimulationCallback :public physx::PxSimulationEventCallback
		{
			std::vector<DisableActor> disableActorTasks;
		public:


			// Inherited via PxSimulationEventCallback
			virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override;
			virtual void onWake(physx::PxActor** actors, physx::PxU32 count) override;
			virtual void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
			virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
			virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
			virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override;

			void finishTasks()
			{
				for (auto& x : disableActorTasks)
				{
					x.run();
				}
				disableActorTasks.clear();
			}
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

		void attachTriggerShape(physx::PxRigidActor* actor, of::resource::Model& triggerShape, float scale);

		template <class T>
		T* createActor(const glm::vec3& pos, of::resource::Model& collisionModel, const bool& isTriggerShape=false, const bool& addToScene=true/*, material type, collisionMesh*/)
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
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Physics::createActor").Error("Invalid type argument passed, no actor is created");
				*/
				return nullptr;
			}
		}
	};
}