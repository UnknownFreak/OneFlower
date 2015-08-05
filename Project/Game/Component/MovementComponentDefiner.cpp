#include "MovementComponent.hpp"
#include "IBaseComponent.hpp"
#include "../../Vector.h"

#include "GameObject.h"
#include "TransformComponent.hpp"
#include "../../Engine.hpp"

const unsigned int IBaseComponent<MovementComponent>::typeID = 14564;
std::string IBaseComponent<MovementComponent>::componentName = "MovementComponent";
void MovementComponent::attachOn(GameObject* entity)
{
	BaseComponent::attachOn(entity);
	Engine::game.addMotionObject(entity);
}
bool MovementComponent::inMotion()
{
	if(speed)
		return true;
	if(rotation)
		return true;
	//	if(distance)
	//	return true;

	return false;
}
void MovementComponent::addForce(Vector2 direction,double speed)
{
	forces.push_back(std::make_pair(direction,speed));
}
void MovementComponent::replaceMotion(Vector2 dir,double s,int dist)
{
	direction = dir;
	speed = s;
	distance = dist;
}

/*
MovementComponent::SpeedVector::SpeedVector(Vector2 dir,double cSpeed)
{
direction = dir;
speed  = cSpeed;
}
//*/

/*
void MovementComponent::moveAt(Vector2 direction,double speed)
{
Vector2& position = attachedOn->GetComponent<TransformComponent>()->position;
if(!direction.normalized)
direction.normalize();

position.x += direction.x*speed;
position.y += direction.y*speed;
}

//*/