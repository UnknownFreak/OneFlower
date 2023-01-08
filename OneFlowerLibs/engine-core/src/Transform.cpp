#include <object/component/Transform.hpp>

#include <utils/common/uuid.hpp>

#pragma warning (push)
#pragma warning (disable: 4201)
#include <glm/gtx/vector_angle.hpp>
#pragma warning (pop)

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

	void Transform::update(const float&)
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

	void Transform::onMessage(const messaging::Message& message)
	{
		using namespace messaging;
		if (message.messageTopic == Topic::of(Topics::REQUEST_DATA) && message.messageBody->bodyType == BodyType::REQUEST_DATA)
		{
			auto ref = ((RequestData*)message.messageBody.get());
			if (ref->topic == Topic::of(Topics::TRANSFORM_SPEED_MODIFIER))
			{
				post(ref->id, ref->topic, std::make_shared<FloatPtr>(&speedModifier));
			}
		}
	}
	void component::Transform::initialize()
	{
		moving = true;
	}
}
