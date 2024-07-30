#include <component/doorHinge.hpp>

#include <component/Transform.hpp>
#include <object/GameObject.hpp>

#include <logger/Logger.hpp>

#include <courier/courier.hpp>
#include <engine/runMode.hpp>

namespace of::component
{
	void DoorHinge::attached()
	{
		auto collider = attachedOn->get<Collider>();

		if (collider != nullptr)
		{
			mActor = collider->mActor;
			if (of::engine::getRunMode() != of::engine::RunMode::EDITOR)
			{
				mHinge = of::engine::GetModule<of::module::physics::PhysicsHandler>().createDoorHinge(mActor, mHingeOffset);

				auto& courier = of::engine::GetModule<of::courier::Courier>();

				courier.addSubscriber(
					of::courier::Topic::PhysicsUpdate,
					of::courier::Subscriber(
						instanceId, isAlive(),
						[&](const of::courier::Message&)
						{
							mActor->is<physx::PxRigidDynamic>()->addTorque({0.f, dir, 0.f}, physx::PxForceMode::eVELOCITY_CHANGE);
						}
					)
				);
			}
			else
			{
				of::engine::GetModule<of::logger::Logger>().getLogger("of::object::component::DoorHinge").Warning("Editor override, not creating a door hinge link!");
			}

		}
		else
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::object::component::DoorHinge").Warning("Trying to create a DoorHinge, but no collider was found. No hinge will be created!");
		}
	}
	void DoorHinge::initialize()
	{
	}

	void DoorHinge::deconstruct()
	{
		if (of::engine::GetModule<of::module::physics::PhysicsHandler>().hasShutDown() == false)
		{
			mHinge->release();
		}
		auto& courier = of::engine::GetModule<of::courier::Courier>();
		courier.removeSubscriber(of::courier::Topic::PhysicsUpdate, instanceId);
	}
}