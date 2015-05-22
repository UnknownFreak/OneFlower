#include "ProjectilePatternComponent.hpp"
#include "TransformComponent.hpp"
#include "GameObject.h"
#include <cmath>
#include "BaseComponent.hpp"
#include "../Engine.hpp"

const unsigned int IBaseComponent<ProjectilePatternComponent>::typeID = 1024;
std::string IBaseComponent<ProjectilePatternComponent>::componentName = "ProjectilePatternComponent";

void ProjectilePatternComponent::attachOn(GameObject * go)
{
	BaseComponent::attachOn(go);
	REGISTER_EDITOR_VARIABLE(double, velosity, Speed);
	REGISTER_EDITOR_VARIABLE(Vector2, movementDirection, Direction);
	REGISTER_EDITOR_VARIABLE(double, distanceTraveled, DistanceTraveled);


}

void ProjectilePatternComponent::updateMousePos(Vector2 mouse)
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	velosity = 100;
	movementDirection = tcp->position.direction(&mouse);
	centerMid = mouse.y;
	startPos = tcp->position;

}

void ProjectilePatternComponent::followMouse()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	speed = velosity*Engine::time.deltaTime();
	tcp->move(movementDirection, speed);
}

void ProjectilePatternComponent::wavePattern()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	speed = velosity*Engine::time.deltaTime();
	tcp->move(movementDirection, speed);
	if (tcp->position.y < centerMid)
	{
		movementDirection.y += 5;
	}
	else
	{
		movementDirection.y -= 5;
	}
}

void ProjectilePatternComponent::missileX()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	speed = velosity*Engine::time.deltaTime();
	tcp->move(Vector2(x, Engine::mouse.pos.y), speed);

}

void ProjectilePatternComponent::missileY()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	speed = velosity*Engine::time.deltaTime();
	tcp->move(Vector2(Engine::mouse.pos.x, -1), speed);
}

void ProjectilePatternComponent::vPattern()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	speed = velosity*Engine::time.deltaTime();
	distanceTraveled = tcp->position.distance(&startPos);
	if (distanceTraveled < 100)
	{
		tcp->move(Vector2(0, -1), speed);
		velosity = 1000;
	}
	else
	{
		tcp->move(movementDirection, speed);
	}
	if (distanceTraveled > 300)
	{
		velosity = 0;
	}
}