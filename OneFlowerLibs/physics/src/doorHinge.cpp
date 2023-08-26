#include <object/component/doorHinge.hpp>

#include <object/component/Transform.hpp>
#include <object/GameObject.hpp>

#include <module/logger/OneLogger.hpp>

namespace of::object::component
{
	void DoorHinge::initialize()
	{
		auto collider = attachedOn->get<Collider>();

		if (collider != nullptr)
		{
			mActor = collider->mActor;
			mHinge = of::engine::GetModule<of::module::physics::PhysicsHandler>().createDoorHinge(mActor, mHingeOffset);
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
	}
}