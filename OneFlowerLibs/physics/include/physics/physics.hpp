#pragma once

#include <module/IEngineModule.hpp>
#include <module/EngineResourceTypes.hpp>

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

namespace of::module::physics
{
	class PhysicsHandler : public interface::IEngineResource<PhysicsHandler>
	{

		class ErrorCallBack : public physx::PxErrorCallback
		{
		public:
			virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;
		};

		physx::PxDefaultAllocator mAllocator;
		ErrorCallBack mErrorCallback;

		physx::PxFoundation* mFoundation;
		physx::PxPvd* mPvd;
		physx::PxPhysics* mPhysics;
		physx::PxScene* mScene;
		physx::PxControllerManager* mControllerManager;

	public:

		PhysicsHandler();
		~PhysicsHandler();

		void simulate(const float dt);

		EngineResourceType& getType() const;

		physx::PxController* createActorController(const glm::vec3& pos);

		template <class T>
		T* createActor(const glm::vec3& pos/*, material type, collisionMesh*/ )
		{
			if constexpr (std::same_as<T, physx::PxRigidStatic>)
			{

			}
			else if constexpr (std::same_as<T, physx::PxRigidDynamic>)
			{

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