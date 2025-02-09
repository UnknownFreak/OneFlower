#include <component/doorHinge.hpp>

#include <component/Transform.hpp>
#include <object/GameObject.hpp>

#include <logger/Logger.hpp>

#include <courier/courier.hpp>
#include <engine/runMode.hpp>
#include <engine/courier/topic.hpp>

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
				mHinge = of::physics::get().createDoorHinge(mActor, mHingeOffset);

				if (subscriberId == courier::SubscriberId::NOT_SET)
				{
					using Topic = of::engine::courier::Topic;
					constexpr auto to = of::Topic::convert;
					subscriberId = courier::get().addSubscriber(
						to(Topic::PhysicsUpdate),
						courier::Subscriber(
							isAlive(),
							[&](const courier::Message&)
							{
								mActor->is<physx::PxRigidDynamic>()->addTorque({ 0.f, dir, 0.f }, physx::PxForceMode::eVELOCITY_CHANGE);
							}
						)
					);
				}
			}
			else
			{
				of::logger::get().getLogger("of::object::component::DoorHinge").Warning("Editor override, not creating a door hinge link!");
			}

		}
		else
		{
			of::logger::get().getLogger("of::object::component::DoorHinge").Warning("Trying to create a DoorHinge, but no collider was found. No hinge will be created!");
		}
	}
	void DoorHinge::initialize()
	{
	}

	void DoorHinge::deconstruct()
	{
		if (of::physics::get().hasShutDown() == false && mHinge != nullptr)
		{
			mHinge->release();
			mHinge = nullptr;
		}
		if (subscriberId != courier::SubscriberId::NOT_SET)
		{
			using Topic = of::engine::courier::Topic;
			auto constexpr from = of::Topic::convert;
			courier::get().removeSubscriber(from(Topic::PhysicsUpdate), subscriberId);
			subscriberId = courier::SubscriberId::NOT_SET;
		}
	}
}