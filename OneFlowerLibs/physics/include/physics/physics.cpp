#include "physics.hpp"

#include <module/logger/OneLogger.hpp>
#include <iostream>

of::module::EngineResourceType of::module::physics::PhysicsHandler::type = of::module::EngineResourceType::Physics;

namespace of::module::physics
{

	void PhysicsHandler::ErrorCallBack::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
	{
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("PhysX").Always(code, message, file, line);
		std::cout << message << " " << file << " " << line << std::endl;
	}

	PhysicsHandler::PhysicsHandler() : mAllocator(), mErrorCallback()
	{
		mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mAllocator, mErrorCallback);
		mPvd = physx::PxCreatePvd(*mFoundation);

		mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale(), false, mPvd);


		physx::PxSceneDesc d = physx::PxSceneDesc(mPhysics->getTolerancesScale());
		d.gravity = physx::PxVec3(0.f, -9.81f, 0.f);
		d.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
		d.filterShader = physx::PxDefaultSimulationFilterShader;

		mScene = mPhysics->createScene(d);
		mControllerManager = PxCreateControllerManager(*mScene);
	}

	PhysicsHandler::~PhysicsHandler()
	{
		mControllerManager->purgeControllers();
		mControllerManager->release();
		mScene->release();
		mPhysics->release();
		mFoundation->release();
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
		return mControllerManager->createController(desc);
	}
};