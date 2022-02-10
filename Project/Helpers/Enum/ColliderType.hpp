#ifndef ColliderType_HPP
#define ColliderType_HPP

namespace Enums
{
	enum class ColliderAlgorithm
	{
		Square,
		SAT,
		PolyDecomp,
	};

	enum class ColliderType
	{
		Wall,
		Floor,
		Entity,
		StaticEntity,
		HitBoxEntity,
		VisionHitbox,
		Void,
		NToSRamp,
		SToNRamp,
		EToWRamp,
		WToERamp
	};
}

#endif 