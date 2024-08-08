#pragma once

#include <utils/common/uuid.hpp>

#include <physics/colliderType.hpp>

#include <PxActor.h>

namespace of::object
{
	class GameObject;
}

namespace of::physics
{
	struct ObjectType
	{
		PxColliderType hitType;
		of::common::uuid objectId;
		physx::PxActor* hitActor = nullptr;
		of::object::GameObject* go = nullptr;;
	};
}