#include "TransformComponent.hpp"
namespace Component
{
	//#include <math.h>
	//#include "../../Engine.hpp"
	/*
	void Transform::moveTo(Vector2 newPosition)
	{
		//HIGH: Remove this or insert HitCollision test before moving toward new position
		position = newPosition;
	}
	/*
	void Transform::move(Vector2 dir,double s)
	{
		if(!dir.normalized)
		{
			dir.normalize();
		}
		position.x += dir.x*s;
		position.y += dir.y*s;
	}
	//*/
	double Transform::distance(Transform* target)
	{
		return	position.distance(&target->position);
	}
	double Transform::angle(Transform* target)
	{
		return position.angle(&target->position);
	}
	Core::Vector2 Transform::DirectionTowards(Transform* target)
	{
		return Core::Vector2();
	}


}