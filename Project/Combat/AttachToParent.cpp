#include "AttachToParent.hpp"

#include <Object/GameObject.hpp>

Enums::ComponentType Component::IBase<Component::AttachToParent>::typeID = Enums::ComponentType::AttachToParent;
Core::String Component::IBase<Component::AttachToParent>::componentName = "AttachToParent";

namespace Component
{

	AttachToParent::AttachToParent(GameObject* objectToFollow) : objectToFollow(objectToFollow)
	{
	}

	void AttachToParent::Update()
	{
		attachedOn->getComponent<Transform>()->pos = objectToFollow->getComponent<Transform>()->buffered;
	}

	void AttachToParent::Simulate(const float&)
	{
	}

	void AttachToParent::onDeath()
	{
	}

	void AttachToParent::onCollision(GameObject*)
	{
	}
};
