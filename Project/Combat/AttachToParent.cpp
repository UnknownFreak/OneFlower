#include "AttachToParent.hpp"
#include <utils/common/uuid.hpp>

#include <object/GameObject.hpp>
#include <object/component/Transform.hpp>


namespace of::object::component
{

	AttachToParent::AttachToParent(GameObject* objectToFollow) : objectToFollow(objectToFollow)
	{
	}

	void AttachToParent::Update()
	{
		attachedOn->get<Transform>()->pos = objectToFollow->get<Transform>()->buffered;
	}

	void AttachToParent::Simulate(const float&)
	{
	}

	void AttachToParent::onDeath()
	{
	}

	void AttachToParent::onMessage(const messaging::Message&)
	{
	}

	void AttachToParent::onCollision(GameObject*)
	{
	}
};
