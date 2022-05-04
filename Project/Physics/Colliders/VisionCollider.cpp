#include "VisionCollider.hpp"
#include "EntityCollider.hpp"

#include <Physics/Physics.hpp>
#include <Module/Globals.hpp>
#include <Object/GameObject.hpp>
#include <functional>

Enums::ComponentType Component::IBase<VisionCollider>::typeID = Enums::ComponentType::VisionCollider;
Core::String Component::IBase<VisionCollider>::componentName = "VCollider";

VisionCollider::VisionCollider() : Interfaces::ICollider(nullptr, 64.f, 64.f, Enums::ColliderAlgorithm::SAT, Enums::ColliderType::VisionHitbox)
{
}

VisionCollider::VisionCollider(const Core::Vector2f& coneSize) : Interfaces::ICollider(nullptr, std::max(coneSize.x, coneSize.y)*2, std::max(coneSize.x, coneSize.y)*2, Enums::ColliderAlgorithm::SAT, Enums::ColliderType::VisionHitbox)
{
	hitboxOffset = { 16.f, 40.f };
	convexCollider.setPointCount(9+4);
	convexCollider.setPoint(0, { 0, 0 });
	convexCollider.setPoint(1, { coneSize.x, coneSize.y });
	convexCollider.setOrigin(0.f, 0.f);

	auto d = coneSize.x * 2;
	auto partSize = d / 11;
	for (size_t i = 0; i < 5; i++)
	{
		convexCollider.setPoint(i+2, { coneSize.x - (partSize * (i+1)), coneSize.y + (i+1) * (10 - i)});
		convexCollider.setPoint(9+2 - i, { -coneSize.x + (partSize * (i+1)), coneSize.y + (i+1) * (10 - i) });
	}
	convexCollider.setPoint(9+3, { -coneSize.x, coneSize.y });
}

VisionCollider::~VisionCollider()
{
	detach();
}

void VisionCollider::attachOn(GameObject* go)
{
	VisionCollider::Base::attachOn(go);
	transform = go->getComponent<Component::Transform>();

	position = &transform->pos;
	Engine::GetModule<Physics::PhysicsEngine>().addCollider(this);
	isAttached = true;
}

void VisionCollider::detach()
{
	if (attachedOn && isAttached)
	{
		Engine::GetModule<Physics::PhysicsEngine>().removeCollider(this);
		isAttached = false;
	}
}

void VisionCollider::doParentSimulate(const float& )
{

}


std::tuple<Core::Vector2f, bool>  VisionCollider::Collides(ICollider* other)
{
	if ((other->colliderType == Enums::ColliderType::Entity || other->colliderType == Enums::ColliderType::StaticEntity) && ((Collider*)other)->attachedOn != attachedOn)
	{
		auto val = ICollider::Collides(other);
		bool collides = std::get<bool>(val);
		if (collides && hitObject == false)
		{
			convexCollider.setOutlineColor(sf::Color::Red);
			attachedOn->onCollision(other);
		}
		else if (hitObject == false)
		{
			convexCollider.setOutlineColor(sf::Color::White);
		}
	}
	return { {0,0}, false };
}

void VisionCollider::onCollision(Interfaces::ICollider*)
{
}

void VisionCollider::Update()
{
	hitObject = false;
	Core::FloatRect cBefore = collider, dBefore = drawBox;
	updateColliderPos(transform->pos.toVector2() + hitboxOffset, 0);
	//Engine::GetModule<Physics::PhysicsEngine>().addCollider(this);
	//collider = cBefore;
	//drawBox = dBefore;

	Engine::GetModule<Physics::PhysicsEngine>().updateCollider(this, this, dBefore);
	//updateColliderPos(transform->pos.toVector2() + hitboxOffset, 0);
	convexCollider.setRotation(transform->facingAngle);

}

void VisionCollider::Simulate(const float&)
{
}

void VisionCollider::onDeath()
{
}

bool VisionCollider::isActive() const
{
	return attachedOn->objectState == Enums::ObjectState::Active;
}

void VisionCollider::updateColliderPos(const Core::Vector2f& pos, const float& extra_offset)
{
	Core::Vector2f newPos = { pos.x - (collider.w / 2) , pos.y - extra_offset - (collider.h / 2) };
	collider.pos = newPos;
	convexCollider.setPosition(pos.x, pos.y);
	//drawBox.pos = { pos.x, pos.y - extra_offset + (z * Globals::Z_OFFSET )};
	drawBox.pos = newPos;
	s.setPosition(convexCollider.getPosition().x, convexCollider.getPosition().y);
}