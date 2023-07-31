#include "physics.hpp"
#include "physics.hpp"

#include <module/resource/Model.hpp>
#include <module/settings/EngineSettings.hpp>
#include <object/GameObject.hpp>

#include <iostream>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::physics::PhysicsHandler>::type = of::module::EngineResourceType::Physics;

namespace of::module::physics
{

	void PhysicsHandler::ErrorCallBack::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
	{
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("PhysX").Always(code, message, file, line);
		std::cout << message << " " << file << " " << line << std::endl;
	}

	physx::PxTriangleMesh* PhysicsHandler::GetObjectAsPxMesh(of::resource::Model& asset)
	{
		physx::PxTriangleMeshDesc desc;
		desc.points.count = (U32)asset.mesh->getVertexDataSize() / (sizeof(float) * 3u);
		desc.points.data = asset.mesh->getVertexDataPtr();
		desc.points.stride = sizeof(float) * 3u;

		desc.triangles.count = (U32)asset.mesh->getIndexDataSize() / (sizeof(U32) * 3u);
		desc.triangles.data = asset.mesh->getIndexDataPtr();
		desc.triangles.stride = sizeof(U32) * 3u;

		physx::PxCookingParams params(mPhysics->getTolerancesScale());

		auto mesh = PxCreateTriangleMesh(params, desc);
		if (mesh == nullptr)
		{
			of::engine::GetModule<of::module::logger::OneLogger>().Error("Failed to load collision mesh");
		}

		return mesh;
	}

	physx::PxConvexMesh* PhysicsHandler::GetObjectAsPxConvex(of::resource::Model& asset)
	{
		physx::PxConvexMeshDesc desc;

		desc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

		U32 vertexCount = (U32)asset.mesh->getVertexDataSize() / (sizeof(float) * 3u);


		desc.points.count = vertexCount;
		desc.points.data = asset.mesh->getVertexDataPtr();
		desc.points.stride = sizeof(float) * 3u;

		physx::PxCookingParams params(mPhysics->getTolerancesScale());

		auto mesh = PxCreateConvexMesh(params, desc);
		if (mesh == nullptr)
		{
			of::engine::GetModule<of::module::logger::OneLogger>().Error("Failed to load collision mesh");
		}

		return mesh;
	}

	PhysicsHandler::PhysicsHandler() : mShutDown(false), mInitialized(false), mAllocator(), mErrorCallback()
	{
	}

	PhysicsHandler::~PhysicsHandler()
	{
		if (mShutDown == false && mInitialized == true)
		{
			shutDown();
		}
	}

	void PhysicsHandler::Initialize()
	{
		mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mAllocator, mErrorCallback);
		mPvd = nullptr;
		if (of::engine::GetModule<of::module::Settings>().usePvdDebugger())
		{
			mPvd = physx::PxCreatePvd(*mFoundation);
			physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
			mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
		}

		mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale(), false, mPvd);

		mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

		physx::PxSceneDesc d = physx::PxSceneDesc(mPhysics->getTolerancesScale());
		d.gravity = physx::PxVec3(0.f, -9.81f, 0.f);
		d.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
		d.filterShader = physx::PxDefaultSimulationFilterShader;

		mScene = mPhysics->createScene(d);
		mControllerManager = PxCreateControllerManager(*mScene);

		mScene->setSimulationEventCallback(&mSimulationCallback);
		mInitialized = true;

		mHeightPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 0), *mMaterial);
		mHeightPlane->setName("PlaneActor");
		mScene->addActor(*mHeightPlane);
	}

	void PhysicsHandler::shutDown()
	{
		mControllerManager->purgeControllers();
		mControllerManager->release();
		mScene->release();
		mPhysics->release();
		mFoundation->release();
		mShutDown = true;
	}

	bool PhysicsHandler::hasShutDown() const
	{
		return mShutDown;
	}

	void PhysicsHandler::simulate(const float dt)
	{
		mScene->simulate(dt);
		mScene->fetchResults(true);
		mSimulationCallback.finishTasks();
	}

	EngineResourceType& PhysicsHandler::getType() const
	{
		return type;
	}

	physx::PxController* PhysicsHandler::createActorController(const glm::vec3& pos)
	{
		physx::PxCapsuleControllerDesc desc;
		desc.material = mPhysics->createMaterial(0.f, 0.f, 0.f);
		desc.height = 2.f;
		desc.radius = 1.f;
		desc.position = physx::PxExtendedVec3(pos.x, pos.y, pos.z);
		desc.nonWalkableMode = physx::PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
		return mControllerManager->createController(desc);
	}

	void PhysicsHandler::attachTriggerShape(physx::PxRigidActor* actor, of::resource::Model& triggerShape, float scale)
	{
		assert(scale > 1.f);
		auto shape = mPhysics->createShape(physx::PxConvexMeshGeometry(GetObjectAsPxConvex(triggerShape), physx::PxMeshScale(physx::PxVec3(scale))), *mMaterial, false);
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
		actor->attachShape(*shape);
		shape->release();
	}

	void PhysicsHandler::SimulationCallback::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count)
	{
	}
	void PhysicsHandler::SimulationCallback::onWake(physx::PxActor** actors, physx::PxU32 count)
	{
	}
	void PhysicsHandler::SimulationCallback::onSleep(physx::PxActor** actors, physx::PxU32 count)
	{
	}
	void PhysicsHandler::SimulationCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
	{
	}
	void PhysicsHandler::SimulationCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
	{
		for (physx::PxU32 i = 0; i < count; i++)
		{
			// ignore pairs when shapes have been deleted
			if (pairs[i].flags & (physx::PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER |
				physx::PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
				continue;

			if (pairs[i].triggerActor == nullptr || pairs[i].otherActor == nullptr)
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("PhysicsHandler").Error("Trigger actor or 'otherActor' is nullptr, skipping onTrigger activation");
			}
			else
			{
				of::object::GameObject* trigger = (of::object::GameObject*)pairs[i].triggerActor->userData;
				of::object::GameObject* other = (of::object::GameObject*)pairs[i].otherActor->userData;

				if (pairs[i].otherActor->getName() == "PlaneActor")
				{
					disableActorTasks.push_back(DisableActor(pairs[i].triggerActor));
				}

				if (trigger)
				{				// filtering is done via onCollision to check for self referencing.
					trigger->onCollision(other);
				}
				else
				{
					of::engine::GetModule<of::module::logger::OneLogger>().getLogger("PhysicsHandler").Error("Trigger actor has no userData!");
					std::cout << "trigger > " << pairs[i].triggerActor->getName() << ", " << pairs[i].otherActor->getName() << std::endl;
				}
			}
		}
	}
	void PhysicsHandler::SimulationCallback::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count)
	{
	}
};