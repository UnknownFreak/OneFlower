#include <physics/raycastCallback.hpp>

#include <PxRigidActor.h>

namespace of::physics
{
	RaycastCallback::RaycastCallback() : physx::PxRaycastCallback(one, 1), hitObjectPos(0), hitPos(0), hit{}
	{
	}

	physx::PxAgain RaycastCallback::processTouches(const physx::PxRaycastHit* buffer, physx::PxU32 nbHits)
	{
		float d = 10000000.f;
		for (physx::PxU32 i = 0; i < nbHits; i++)
		{
			if (buffer[i].distance < d)
			{
				auto p = buffer[i].actor->getGlobalPose().p;
				hitObjectPos.x = p.x;
				hitObjectPos.y = p.y;
				hitObjectPos.z = p.z;
				d = buffer[i].distance;
				hitPos.x = buffer[i].position.x;
				hitPos.y = buffer[i].position.y;
				hitPos.z = buffer[i].position.z;
				if (buffer[i].actor->userData == nullptr)
				{
					hit.hitType = PxColliderType::Unknown;
					hit.objectId = of::common::uuid::nil();
				}
				else
				{
					hit = *(ObjectType*)buffer[i].actor->userData;
				}
				hit.hitActor = buffer[i].actor;

			}
		}
		return true;
	};
}