#include "TileCollider.hpp"

#include <Physics/Physics.hpp>

TileCollider::TileCollider(const glm::vec3& pos, const glm::vec2& size,
	const Enums::ColliderType& _colliderType, const bool& _isRoof): 
	ICollider(&t.pos, size.x, size.y, Enums::ColliderAlgorithm::SAT, _colliderType)
{
	t.pos = pos;
	isRoof = _isRoof;
	if (colliderType == Enums::ColliderType::NToSRamp)
	{
		collider.h += 64.f;
		convexCollider[2].y += 64.f;
		convexCollider[3].y += 64.f;
	}
	else if (colliderType == Enums::ColliderType::SToNRamp)
	{
		collider.h += 64.f;

		convexCollider[0].y -= 64;
		convexCollider[1].y -= 64;
	}
	requireUpdate = true;
	Update();
	Engine::GetModule<Physics::PhysicsEngine>().addCollider(this);
}

TileCollider::~TileCollider()
{
	Engine::GetModule<Physics::PhysicsEngine>().removeCollider(this);
}

void TileCollider::doParentSimulate(const float& )
{
	Update();
}

void TileCollider::Update()
{
	if (requireUpdate)
	{
		float extra_offset = 0.f;
		if (colliderType == Enums::ColliderType::SToNRamp)
			extra_offset = 64.f;
		updateColliderPos(*position, extra_offset);
		requireUpdate = false;
	}
}
