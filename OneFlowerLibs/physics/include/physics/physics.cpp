#include "physics.hpp"

#include <physics/raycastCallback.hpp>

#include <graphics/model/Model.hpp>
#include <module/resource/MeshLoader.hpp>

#include <engine/settings.hpp>
#include <engine/paths.hpp>

#include <logger/Logger.hpp>

of::physics::PhysicsHandler* g_physics = nullptr;

namespace of::physics
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
			of::logger::get().Error("Failed to load collision mesh");
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
			of::logger::get().Error("Failed to load collision mesh");
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
		d.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(of::settings::get().getPhysicsThreadCount());
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
		mMaterial->release();
		PxCloseExtensions();
		mPhysics->release();
		if (of::settings::get().usePvdDebugger())
		{
			mPvd->release();
		}
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

	physx::PxFixedJoint* PhysicsHandler::createJoint(physx::PxRigidActor* p1, physx::PxRigidActor* p2)
	{
		return physx::PxFixedJointCreate(*mPhysics, p1, p1->getGlobalPose(), p2, p2->getGlobalPose());
	}


	bool PhysicsHandler::castRay(glm::vec3 start, glm::vec3 end, glm::vec3& hitOut, glm::vec3& hitObjectPos, ObjectType& objectTypeInfo, CollisionLayer layer)
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

	physx::PxD6Joint* PhysicsHandler::createDoorHinge(physx::PxRigidActor* p, const glm::vec3& hingePosRelOffset)
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
		auto l = physx::PxJointLimitPyramid(0, physx::PxPi / 2, 0.f, 0.1f);
		//auto l = physx::PxJointLimitPyramid(-physx::PxPi+0.01f, physx::PxPi - 0.01f, 0.f, 0.1f);
		joint->setPyramidSwingLimit(l);

		if (of::settings::get().usePvdDebugger())
		{
			joint->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);
		}
		return joint;
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

	physx::PxRigidStatic* PhysicsHandler::createStatic(const glm::vec3& pos, of::resource::Model& collisionModel, const bool isTriggerShape, const bool addToScene)
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
	physx::PxRigidDynamic* PhysicsHandler::createDynamic(const glm::vec3& pos, of::resource::Model& collisionModel, const bool isTriggerShape, const bool addToScene)
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

	nullptr_t PhysicsHandler::invalidActor()
	{
		
		of::logger::get().getLogger("of::physics::createActor").Error("Invalid type argument passed, no actor is created");
		return nullptr;
	}


	void init()
	{
		if (g_physics == nullptr)
		{
			g_physics = new PhysicsHandler();
			// TODO: remove initialize call and move all that logic into constructor
			g_physics->Initialize();
		}
	}
	
	void shutdown()
	{
		if (g_physics != nullptr)
		{
			g_physics->shutDown();
			delete g_physics;
			g_physics = nullptr;
		}
	}

	PhysicsHandler& get()
	{
		return *g_physics;
	}

};