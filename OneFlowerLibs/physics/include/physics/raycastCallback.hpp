#pragma once
#include <PxQueryReport.h>

#include <glm/vec3.hpp>
#include <physics/objectType.hpp>

namespace of::physics
{
	class RaycastCallback : public physx::PxRaycastCallback
	{
		physx::PxRaycastHit one[1];
	public:

		RaycastCallback();

		virtual physx::PxAgain processTouches(const physx::PxRaycastHit* buffer, physx::PxU32 nbHits);

		glm::vec3 hitObjectPos;
		glm::vec3 hitPos;
		ObjectType hit;
	};
}
