#include "TransformComponent.hpp"
namespace Component
{
	//#include <math.h>
	//#include "../../Engine.hpp"
	/*
	void TransformComponent::moveTo(Vector2 newPosition)
	{
		//HIGH: Remove this or insert HitCollision test before moving toward new position
		position = newPosition;
	}
	/*
	void TransformComponent::move(Vector2 dir,double s)
	{
		if(!dir.normalized)
		{
			dir.normalize();
		}
		position.x += dir.x*s;
		position.y += dir.y*s;
	}
	//*/
	double TransformComponent::distance(TransformComponent* target)
	{
		return	position.distance(&target->position);
	}
	double TransformComponent::angle(TransformComponent* target)
	{
		return position.angle(&target->position);
	}
	Core::Vector2 TransformComponent::DirectionTowards(TransformComponent* target)
	{
		return Core::Vector2();
	}


}