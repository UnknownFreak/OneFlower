#include <object/component/Transform.hpp>

#include <utils/common/uuid.hpp>

#pragma warning (push)
#pragma warning (disable: 4201)
#include <glm/gtx/vector_angle.hpp>
#pragma warning (pop)

of::common::uuid of::object::component::IBase<of::object::component::Transform>::typeID = of::common::uuid("e6f52003-0e92-4118-8ab0-b5d54b680c81");
of::common::String of::object::component::IBase<of::object::component::Transform>::componentName = "Transform";

namespace of::object::component
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
		//glm::vec2 newDir;
		//if (stats)
		//{
		//	newDir = direction * stats->getSpeed() * 0.05f;
		//	//pos += newDir;
		//	lastDirection += newDir;
		//}
		//else
		//{
		//	//pos += direction;
		lastDirection += direction * speedModifier * 0.05f;
		//}
	}

	void Transform::lookAt(const glm::vec2& direction)
	{
		auto thePos = glm::vec2(pos);
		auto theOffset = thePos + direction;
		facingAngle = glm::angle(thePos, theOffset) - 90;
	}

	void Transform::attachOn(GameObject* go)
	{
		using namespace of::object::messaging;
		Base::attachOn(go);
		post(Topic::of(Topics::TRANSFORM_SPEED_MODIFIER), std::make_shared<FloatPtr>(&speedModifier));
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

	void of::object::component::Transform::onMessage(const messaging::Message& message)
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
