#include "physics.hpp"

#include <graphics/model/Model.hpp>

#include <engine/settings.hpp>
#include <engine/paths.hpp>

#include <module/resource/MeshLoader.hpp>

#include <object/GameObject.hpp>

#include <iostream>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::physics::PhysicsHandler>::type = of::module::EngineResourceType::Physics;

namespace of::module::physics
{

	physx::PxFilterFlags CustomFilterShader(
		physx::PxFilterObjectAttributes attributes0,
		physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1,
		physx::PxFilterData filterData1,
		physx::PxPairFlags& pairFlags,
		const void* constantBlock,
		physx::PxU32 constantBlockSize)
	{

		return physx::PxDefaultSimulationFilterShader(
			attributes0, filterData0, attributes1, filterData1, pairFlags, constantBlock, constantBlockSize);
	}

	void PhysicsHandler::ErrorCallBack::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
	{
		of::engine::GetModule<of::logger::Logger>().getLogger("PhysX").Always(code, message, file, line);
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
			of::engine::GetModule<of::logger::Logger>().Error("Failed to load collision mesh");
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
			of::engine::GetModule<of::logger::Logger>().Error("Failed to load collision mesh");
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
		if (of::settings::get().usePvdDebugger())
		{
			mPvd = physx::PxCreatePvd(*mFoundation);
			physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
			mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
		}

		mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale(), false, mPvd);
		
		PxInitExtensions(*mPhysics, mPvd);

		mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

		physx::PxSceneDesc d = physx::PxSceneDesc(mPhysics->getTolerancesScale());
		d.gravity = physx::PxVec3(0.f, -9.81f, 0.f);
		d.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
		d.filterShader = CustomFilterShader;

		mScene = mPhysics->createScene(d);
		if (of::settings::get().usePvdDebugger())
		{
			mScene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
			mScene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			mScene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
		}
		
		mControllerManager = PxCreateControllerManager(*mScene);

		mScene->setSimulationEventCallback(&mSimulationCallback);


		mInitialized = true;

		mHeightPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 0), *mMaterial);
		mHeightPlane->setName("PlaneActor");
		physx::PxShape* s;
		((physx::PxRigidStatic*)mHeightPlane)->getShapes(&s, 1, 0);
		physx::PxFilterData f;
		f.word0 = getCollisionLayer(CollisionLayer::SWEEP_EDITOR);
		s->setQueryFilterData(f);

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

	void PhysicsHandler::attachTriggerShape(physx::PxRigidActor* actor, of::resource::Model& triggerShape, glm::vec3 offset, glm::vec3 scale)
	{
		if (actor->is<physx::PxRigidStatic>() == nullptr)
		{
			auto shape = mPhysics->createShape(physx::PxConvexMeshGeometry(GetObjectAsPxConvex(triggerShape), physx::PxMeshScale(physx::PxVec3(scale.x, scale.y, scale.z))), *mMaterial, false);
			shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
			shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
			shape->setLocalPose(physx::PxTransform(offset.x, offset.y, offset.x));
			actor->attachShape(*shape);
			shape->setQueryFilterData(physx::PxFilterData());
			shape->setSimulationFilterData(physx::PxFilterData());
			shape->release();
		}
		else
		{
			auto shape = mPhysics->createShape(physx::PxTriangleMeshGeometry(GetObjectAsPxMesh(triggerShape), physx::PxMeshScale(physx::PxVec3(scale.x, scale.y, scale.z))), *mMaterial, false);
			shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
			shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
			shape->setLocalPose(physx::PxTransform(offset.x, offset.y, offset.x));
			actor->attachShape(*shape);
			shape->release();
		}

	}

	void PhysicsHandler::attachBoxTriggerShape(physx::PxRigidActor* actor, glm::vec3 offset, glm::vec3 scale)
	{
		auto shape = mPhysics->createShape(physx::PxBoxGeometry(physx::PxVec3(scale.x, scale.y, scale.z)), *mMaterial, false);
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
		shape->setLocalPose(physx::PxTransform(offset.x, offset.y, offset.x));
		actor->attachShape(*shape);
		shape->release();
	}

	void PhysicsHandler::attachCylinderTriggerShape(physx::PxRigidActor* actor, glm::vec3 offset, glm::vec3 scale)
	{
		auto mesh = of::engine::GetModule<of::module::mesh::Loader>().requestModel("cylinder.swm",
			of::engine::path::meshes, true);
		auto shape = mPhysics->createShape(physx::PxConvexMeshGeometry(GetObjectAsPxConvex(mesh), physx::PxMeshScale(physx::PxVec3(scale.x, scale.y, scale.z))), *mMaterial, false);
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
		shape->setLocalPose(physx::PxTransform(offset.x, offset.y, offset.x));
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
				of::engine::GetModule<of::logger::Logger>().getLogger("PhysicsHandler").Error("Trigger actor or 'otherActor' is nullptr, skipping onTrigger activation");
			}
			else
			{
				ObjectType* trigger = (ObjectType*)pairs[i].triggerActor->userData;
				ObjectType* other = (ObjectType*)pairs[i].otherActor->userData;

				if (trigger)
				{
					// filtering is done via onCollision to check for self referencing.
					if (other)
					{
						trigger->go->onCollision(other->go);
					}
				}
				else
				{
					of::engine::GetModule<of::logger::Logger>().getLogger("PhysicsHandler").Error("Trigger actor has no userData!");
					std::cout << "trigger > " << pairs[i].triggerActor->getName() << ", " << pairs[i].otherActor->getName() << std::endl;
				}
			}
		}
	}
	void PhysicsHandler::SimulationCallback::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count)
	{
	}
};