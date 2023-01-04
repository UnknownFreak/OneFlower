#include "AttachToParent.hpp"
#include <utils/common/uuid.hpp>

#include <object/GameObject.hpp>
#include <object/component/Transform.hpp>

//of::common::uuid of::object::component::IBase<of::object::component::AttachToParent>::typeID = of::common::uuid("6e45ab1c-7a29-417b-b9fb-d6db1789696b");
//of::common::String of::object::component::IBase<of::object::component::AttachToParent>::componentName = "AttachToParent";

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
