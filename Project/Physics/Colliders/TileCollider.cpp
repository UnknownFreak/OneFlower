#include "TileCollider.hpp"

#include <Physics/Physics.hpp>

TileCollider::TileCollider(const Core::Vector3f& pos, const Core::Vector2f& size,
	const Enums::ColliderType& _colliderType, const bool& _isRoof): 
	ICollider(&t.pos, size.x, size.y, Enums::ColliderAlgorithm::SAT, _colliderType)
{
	t.pos = pos;
	isRoof = _isRoof;
	if (colliderType == Enums::ColliderType::NToSRamp)
	{
		collider.h += 64.f;
		drawBox.h += 64.f;
		auto p = convexCollider.getPoint(2);
		convexCollider.setPoint(2, { p.x, p.y + 64.f });
		p = convexCollider.getPoint(3);
		convexCollider.setPoint(3, { p.x, p.y + 64.f});
	}
	else if (colliderType == Enums::ColliderType::SToNRamp)
	{
		collider.h += 64.f;
		drawBox.h += 64.f;

		auto p = convexCollider.getPoint(0);
		convexCollider.setPoint(0, { p.x, p.y - 64.f });
		p = convexCollider.getPoint(1);
		convexCollider.setPoint(1, { p.x, p.y - 64.f });
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
		updateColliderPos(position->toVector2(), extra_offset);
		requireUpdate = false;
	}
}

void TileCollider::buildRenderableHitbox(sf::VertexArray& arr) const
{
	sf::Color c(sf::Color::Green);
	if (colliderType == Enums::ColliderType::Floor)
		c = sf::Color::Red;
	else if (colliderType == Enums::ColliderType::Void)
		c = sf::Color::Blue;

	arr.append(sf::Vertex({ collider.x + 1, collider.y + 1 + (position->z * Globals::Z_OFFSET) }, c));
	arr.append(sf::Vertex({ collider.x + 1, collider.y - 1 + collider.h + (position->z * Globals::Z_OFFSET) }, c));

	arr.append(sf::Vertex({ collider.x + 1 , collider.y - 1 + collider.h + (position->z * Globals::Z_OFFSET) }, c));
	arr.append(sf::Vertex({ collider.x - 1 + collider.w, collider.y - 1 + collider.h + (position->z * Globals::Z_OFFSET) }, c));

	arr.append(sf::Vertex({ collider.x - 1 + collider.w , collider.y - 1 + collider.h + (position->z * Globals::Z_OFFSET) }, c));
	arr.append(sf::Vertex({ collider.x - 1 + collider.w , collider.y + 1 + (position->z * Globals::Z_OFFSET) }, c));

	arr.append(sf::Vertex({ collider.x - 1 + collider.w, collider.y + 1 + (position->z * Globals::Z_OFFSET) }, c));
	arr.append(sf::Vertex({ collider.x + 1, collider.y + 1 + (position->z * Globals::Z_OFFSET) }, c));
}
