#include "EntityCollider.hpp"

#include <Physics/Physics.hpp>
#include <Module/Globals.hpp>
#include <Object/GameObject.hpp>
#include <functional>

Enums::ComponentType Component::IBase<Collider>::typeID = Enums::ComponentType::Collider;
Core::String Component::IBase<Collider>::componentName = "Collider";
Collider::Collider() : Interfaces::ICollider(nullptr, 64.f, 64.f, Enums::ColliderAlgorithm::SAT, Enums::ColliderType::Entity)
{
}

Collider::Collider(const Core::Vector2f& size) : Interfaces::ICollider(nullptr, size.x, size.y, Enums::ColliderAlgorithm::SAT, Enums::ColliderType::Entity)
{
}

Collider::Collider(const Core::Vector2f& size, const Core::Vector2f& nHitboxOffset) : Collider(size)
{
	hitboxOffset = nHitboxOffset;
}

Collider::Collider(const Collider& copy) : Interfaces::ICollider(copy), hitboxOffset(copy.hitboxOffset)
{
}

Collider::~Collider()
{
	detach();
}

void Collider::detach()
{
	if (attachedOn && isAttached)
	{
		isAttached = false;
		Engine::GetModule<Physics::PhysicsEngine>().removeCollider(this);
	}
}

std::unique_ptr<Component::Base> Collider::ucopy() const
{
	return std::make_unique<Collider>(*this);
}

void Collider::attachOn(GameObject* go)
{
	//if(attachedOn)
	//	Engine::GetModule<Physics::PhysicsEngine>().removeCollider(this);

	Collider::Base::attachOn(go);
	transform = go->getComponent<Component::Transform>();

	position = &transform->pos;
		Engine::GetModule<Physics::PhysicsEngine>().addCollider(this);
	isAttached = true;
}

void Collider::doParentSimulate(const float& fElapsedTime)
{
	attachedOn->Simulate(fElapsedTime,
		(transform->moving || transform->falling) || (colliderType == Enums::ColliderType::StaticEntity && collider.pos != transform->pos.toVector2() + hitboxOffset));
}


std::tuple<Core::Vector2f, bool>  Collider::Collides(ICollider* other)
{
	if (other->colliderType == Enums::ColliderType::Floor)
	{
		if (std::get<bool>(ICollider::Collides(other)))
		{
			floor = other;
		}
		else if (other->isRoof && within(other->position->z, 0.2f, -0.1f))
		{
			transform->jumpSpeed = 0.f;
			transform->pos.z -= .1f;
		}
		else if (floor && std::get<bool>(ICollider::Collides(floor)) == false)
		{
			floor = nullptr;
		}
	}
	else if (other->colliderType == Enums::ColliderType::Entity)
	{
		auto val = ICollider::Collides(other);
		auto collides = std::get<bool>(val);
		if (collides)
		{
			attachedOn->onCollision(other);
			transform->moving = true;
		}
	}

	else if (other->colliderType == Enums::ColliderType::Wall || other->colliderType == Enums::ColliderType::StaticEntity)
	{
		auto val = ICollider::Collides(other);
		if (std::get<bool>(val))
		{
			transform->moving = true;

			Core::Vector2f vec = std::get<Core::Vector2f>(val);
			// prevent sliding when colliding direct on that axis

			transform->lastDirection -= vec;
		}
		//if (transform->lastDirection.x == 0)
		//	vec.x = 0;
		//if (transform->lastDirection.y == 0)
		//	vec.y = 0;
		//transform->pos -= vec;
		//lastDirection = {};
	}
	if (other->colliderType == Enums::ColliderType::NToSRamp || other->colliderType == Enums::ColliderType::SToNRamp ||
		other->colliderType == Enums::ColliderType::EToWRamp || other->colliderType == Enums::ColliderType::WToERamp)
	{
		auto val = ICollider::Collides(other);
		Core::Vector2f vec = std::get<Core::Vector2f>(val);
		if (other->colliderType == Enums::ColliderType::SToNRamp)
		{
			auto d = (transform->pos.y - (other->convexCollider.getPosition().y - Globals::Z_OFFSET));
			auto nz = other->position->z + std::abs((d / Globals::Z_OFFSET));

			if (nz > other->position->z + 1.f)
			{
				nz = other->position->z + 1.f;
			}
			if (transform->pos.z < nz)
				transform->pos.z = nz;

		}
		if (other->colliderType == Enums::ColliderType::NToSRamp)
		{
			auto d = (transform->pos.y + convexCollider.getLocalBounds().height - (other->convexCollider.getPosition().y));
			auto nz = other->position->z + (1.1f * std::abs((d / Globals::Z_OFFSET / 2.f)));
			if (nz > other->position->z + 1.f)
			{
				nz = other->position->z + 1.f;
			}
			if (transform->pos.z < nz)
				transform->pos.z = nz;
		}
		if (other->colliderType == Enums::ColliderType::WToERamp)
		{
			auto d = (transform->pos.x - (other->convexCollider.getPosition().x - Globals::Z_OFFSET));
			auto nz = other->position->z + std::abs(d / (Globals::Z_OFFSET));
			if (nz > other->position->z + 1.f)
			{
				nz = other->position->z + 1.f;
			}
			if (transform->pos.z < nz)
				transform->pos.z = nz;

		}
		if (other->colliderType == Enums::ColliderType::EToWRamp)
		{
			auto d = (transform->pos.x + convexCollider.getLocalBounds().width - (other->convexCollider.getPosition().x));
			auto nz = other->position->z + std::abs(d / (Globals::Z_OFFSET));
			if (nz > other->position->z + 1.f)
			{
				nz = other->position->z + 1.f;
			}
			if (transform->pos.z < nz)
				transform->pos.z = nz;

		}
	}
	return { {0,0}, false };
}

void Collider::onCollision(Interfaces::ICollider*)
{
}

void Collider::Update()
{
	//if(collider.pos == transform->pos.toVector2() + hitboxOffset)
	//	return;
	Core::FloatRect /*cBefore = collider, */ dBefore = drawBox;
	ICollider::updateColliderPos(transform->pos.toVector2() + hitboxOffset, 0);
	//Engine::GetModule<Physics::PhysicsEngine>().addCollider(this);
	//collider = cBefore;
	//drawBox = dBefore;
	Engine::GetModule<Physics::PhysicsEngine>().updateCollider(this, this, dBefore);
	//ICollider::updateColliderPos(transform->pos.toVector2() + hitboxOffset, 0);
}

void Collider::onDeath()
{
}

void Collider::Simulate(const float& fElapsedTime)
{
	if (colliderType == Enums::ColliderType::StaticEntity)
		return;

	transform->pos.z -= (9.f * transform->jumpSpeed) * fElapsedTime;
	if (floor)
	{
		if (position->z < floor->position->z)
		{
			transform->pos.z = floor->position->z;
			transform->falling = false;
			fallTime = 0.f;
		}
	}
	transform->jumpSpeed += 2.f * fElapsedTime;
	if (transform->jumpSpeed > 1.f)
	{
		transform->jumpSpeed = 1.f;
	}
	if (transform->jumpSpeed > 0.f)
		fallTime += fElapsedTime;
	if (fallTime > 0.1f)
	{
		transform->falling = true;
		if (fallTime > 2.0f)
		{
			attachedOn->sendMessage("Anim", "fallingFast");
		}
		else
			attachedOn->sendMessage("Anim", "falling");

	}
	if (transform->pos.z < -1.f)
		transform->pos.z = -1;
}

void Collider::postUpdate()
{
	transform->pos += transform->lastDirection;
	transform->lastDirection = { 0.f, 0.f };
	transform->buffered = transform->pos;
}
