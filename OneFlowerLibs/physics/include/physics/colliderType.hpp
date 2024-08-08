#pragma once


namespace of::physics
{
	enum class PxColliderType
	{
		Object,
		ObjectTrigger,
		TerrainCollider,
		Unknown
	};


	inline const char* to_string(const PxColliderType t)
	{
		switch (t)
		{
		case PxColliderType::Object:
			return "object";
		case PxColliderType::ObjectTrigger:
			return "object trigger";
		case PxColliderType::TerrainCollider:
			return "terrain collider";
		default:
			return "Unknown";
		}
	}
}