#include "AttachToParent.hpp"

#include <Object/GameObject.hpp>

Enums::ComponentType Component::IBase<Component::AttachToParent>::typeID = Enums::ComponentType::AttachToParent;
Core::String Component::IBase<Component::AttachToParent>::componentName = "AttachToParent";

Component::AttachToParent::AttachToParent(GameObject* objectToFollow) : objectToFollow(objectToFollow)
{
}

void Component::AttachToParent::Update()
{
	attachedOn->getComponent<Transform>()->pos = objectToFollow->getComponent<Transform>()->buffered;
}

void Component::AttachToParent::Simulate(const float& )
{
}

void Component::AttachToParent::onDeath()
{
}

void Component::AttachToParent::onCollision(Interfaces::ICollider*)
{
}
