#include "Transform.hpp"
#include "GameObject.hpp"

#pragma warning (push)
#pragma warning (disable: 4201)
#include <glm/gtx/vector_angle.hpp>
#pragma warning (pop)

Enums::ComponentType Component::IBase<Component::Transform>::typeID = Enums::ComponentType::Transform;
of::common::String Component::IBase<Component::Transform>::componentName = "Transform";

namespace Component
{
	void Transform::jump()
	{
		if (falling)
			return;
		jumpSpeed = -.7f;
		falling = true;
	}

	void Transform::move(const glm::vec2& direction)
	{
		moving = true;
		glm::vec2 newDir;
		if (stats)
		{
			newDir = direction * stats->getSpeed() * 0.05f;
			//pos += newDir;
			lastDirection += newDir;
		}
		else
		{
			//pos += direction;
			lastDirection += direction;
		}
	}

	void Transform::lookAt(const glm::vec2& direction)
	{
		auto thePos = glm::vec2(pos);
		auto theOffset = thePos + direction;
		facingAngle = glm::angle(thePos, theOffset) - 90;
	}

	void Transform::attachOn(GameObject* go)
	{
		Base::attachOn(go);
		stats = go->getComponent<Component::Stats>();
		moving = true;
	}

	void Transform::onCollision(GameObject*)
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
		//lookAt(lastDirection);
		pos += glm::vec3(lastDirection, 0.f);
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
