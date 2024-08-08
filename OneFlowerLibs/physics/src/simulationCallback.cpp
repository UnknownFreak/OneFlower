#include <physics/simulationCallback.hpp>

#include <physics/objectType.hpp>
#include <object/GameObject.hpp>

#include <logger/Logger.hpp>

namespace of::physics
{
	void SimulationCallback::onConstraintBreak(physx::PxConstraintInfo* /*constraints*/, physx::PxU32 /*count*/)
	{
	}
	void SimulationCallback::onWake(physx::PxActor** /*actors*/, physx::PxU32 /*count*/)
	{
	}
	void SimulationCallback::onSleep(physx::PxActor** /*actors*/, physx::PxU32 /*count*/)
	{
	}
	void SimulationCallback::onContact(const physx::PxContactPairHeader& /*pairHeader*/, const physx::PxContactPair* /*pairs*/, physx::PxU32 /*nbPairs*/)
	{
	}
	void SimulationCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
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
	void SimulationCallback::onAdvance(const physx::PxRigidBody* const* /*bodyBuffer*/, const physx::PxTransform* /*poseBuffer*/, const physx::PxU32 /*count*/)
	{
	}
}