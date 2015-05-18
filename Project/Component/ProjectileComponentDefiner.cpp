#include "ProjectileComponent.hpp"
#include "TransformComponent.hpp"
#include "GameObject.h"
#include <cmath>
#include "BaseComponent.hpp"
#include "../Engine.hpp"

const unsigned int IBaseComponent<ProjectileComponent>::typeID = 1024;
std::string IBaseComponent<ProjectileComponent>::componentName = "ProjectileComponent";

void ProjectileComponent::attachOn(GameObject * go)
{
	BaseComponent::attachOn(go);
	REGISTER_EDITOR_VARIABLE(double, velosity, Speed);
	REGISTER_EDITOR_VARIABLE(double, x, Distance);
	REGISTER_EDITOR_VARIABLE(Vector2, movementDirection, Direction);
}

void ProjectileComponent::shoot(Vector2 mouse)
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	movementDirection = tcp->position.direction(&mouse);
	centerMid = mouse.y;

}

void ProjectileComponent::updateOne()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	speed = velosity*Engine::time.deltaTime();
	tcp->move(movementDirection, speed);
}

void ProjectileComponent::updateTwo()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	speed = velosity*Engine::time.deltaTime();
	tcp->move(movementDirection, speed);
	if (tcp->position.y < centerMid)
	{
		movementDirection.y += 10;
	}
	else
	{
		movementDirection.y -= 10;
	}
}

void ProjectileComponent::updateThree()
{

}