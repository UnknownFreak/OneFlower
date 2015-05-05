#include "ProjectileComponent.hpp"
#include "TransformComponent.hpp"
#include "GameObject.h"
#include "BaseComponent.hpp"
#include "../Engine.hpp"

const unsigned int IBaseComponent<ProjectileComponent>::typeID = 1024;
std::string IBaseComponent<ProjectileComponent>::componentName = "ProjectileComponent";

ProjectileComponent::ProjectileComponent()
{

}

void ProjectileComponent::attachOn(GameObject * go)
{
	BaseComponent::attachOn(go);
	REGISTER_EDITOR_VARIABLE(double, velosity, Speed);
	REGISTER_EDITOR_VARIABLE(double, x, Distance);
	REGISTER_EDITOR_VARIABLE(double, dt, Time);

}

void ProjectileComponent::shoot(Vector2 mouse)
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	destination = mouse;
	tcp->moveTo(destination.x, destination.y, 5);
}

void ProjectileComponent::updateOne()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	//tcp->move(Vector2(Engine::mouse.pos), 5);
	tcp->moveTo(Engine::mouse.pos.x, Engine::mouse.pos.y, speed);
}

void ProjectileComponent::updateTwo()
{
	TransformComponent* tcp = attachedOn->GetComponent<TransformComponent>();
	x = tcp->position.distance(&Engine::mouse.pos);
	dt = Engine::time.deltaTime();
	speed = velosity*dt;
	//tcp->move(Vector2(1, -1), speed);
	tcp->moveTo(Engine::mouse.pos.x, Engine::mouse.pos.y, speed);
	//tcp->move(Vector2(0,10), speed);
	
}

void ProjectileComponent::updateThree()
{

}