#include <object/component/AttachToParent.hpp>
#include <utils/common/uuid.hpp>

#include <object/GameObject.hpp>
#include <object/component/Transform.hpp>


namespace of::object::component
{

	AttachToParent::AttachToParent(GameObject* objectToFollow) : objectToFollow(objectToFollow)
	{
	}

	void AttachToParent::update(const float&)
	{
		attachedOn->get<Transform>()->pos = objectToFollow->get<Transform>()->buffered;
	}

	void AttachToParent::onMessage(const messaging::Message&)
	{
	}
};
