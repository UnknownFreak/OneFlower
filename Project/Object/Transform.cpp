#include "Transform.hpp"
#include "GameObject.hpp"

Enums::ComponentType Component::IBase<Component::Transform>::typeID = Enums::ComponentType::Transform;
Core::String Component::IBase<Component::Transform>::componentName = "Transform";

namespace Component
{
	void Transform::jump()
	{
		if (falling)
			return;
		jumpSpeed = -.7f;
		falling = true;
	}

	void Transform::move(const Core::Vector2f& direction)
	{
		moving = true;
		Core::Vector2f newDir;
		if (stats)
		{
			newDir = direction * stats->getSpeed();
			//pos += newDir;
			lastDirection += newDir;
		}
		else
		{
			//pos += direction;
			lastDirection += direction;
		}
	}

	void Transform::lookAt(const Core::Vector2f& direction)
	{
		auto thePos = pos.toVector2();
		auto theOffset = thePos + direction;
		facingAngle = thePos.angle<float>(theOffset) - 90.f;
	}

	void Transform::attachOn(GameObject* go)
	{
		Base::attachOn(go);
		stats = go->getComponent<Component::Stats>();
		moving = true;
	}

	void Transform::onCollision(Interfaces::ICollider*)
	{
	}

	void Transform::Simulate(const float&)
	{
	}

	void Transform::onDeath()
	{
	}

	void Transform::Update()
	{
		//directionCounter++;
		lookAt(lastDirection);
		pos += lastDirection;
		buffered = pos;
		//if (directionCounter > 10 && !moving)
		//{
		//	directionCounter = 0;
		//}
		//else if (directionCounter > 50 && moving)
		//{
		//	lastDirection = { 0.f, 0.f };
		//	directionCounter = 0;
		//}
		lastDirection = { 0.f, 0.f };
		moving = false;
	}
}
