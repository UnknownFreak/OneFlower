#include <object/component/doorHinge.hpp>

#include <object/component/Transform.hpp>
#include <object/GameObject.hpp>

#include <module/logger/OneLogger.hpp>

#include <messaging/courier.hpp>
#include <engine/runMode.hpp>

namespace of::object::component
{
	void DoorHinge::initialize()
	{
		auto collider = attachedOn->get<Collider>();

		if (collider != nullptr)
		{
			mActor = collider->mActor;
			if (of::engine::getRunMode() != of::engine::RunMode::EDITOR)
			{
				mHinge = of::engine::GetModule<of::module::physics::PhysicsHandler>().createDoorHinge(mActor, mHingeOffset);

				auto& courier = of::engine::GetModule<of::messaging::Courier>();

				courier.addSubscriber(
					of::messaging::Topic::PhysicsUpdate,
					of::messaging::Subscriber(
						instanceId, warrantyFromThis(),
						[&](const of::messaging::Message&)
						{
							mActor->is<physx::PxRigidDynamic>()->addTorque({0.f, dir, 0.f}, physx::PxForceMode::eVELOCITY_CHANGE);
						}
					)
				);
			}
			else
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::object::component::DoorHinge").Warning("Editor override, not creating a door hinge link!");
			}

		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::object::component::DoorHinge").Warning("Trying to create a DoorHinge, but no collider was found. No hinge will be created!");
		}
	}

	void DoorHinge::deconstruct()
	{
		if (of::engine::GetModule<of::module::physics::PhysicsHandler>().hasShutDown() == false)
		{
			mHinge->release();
		}
		auto& courier = of::engine::GetModule<of::messaging::Courier>();
		courier.removeSubscriber(of::messaging::Topic::PhysicsUpdate, instanceId);
	}
}