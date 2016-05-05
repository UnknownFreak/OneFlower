#include "Movement.hpp"


void Physics::Movement::addTranslation(Vector2 dir,double force)
{
	direction += dir;
	speed += force;
}
void Physics::Movement::reset()
{
	speed = 0;
	torque = 0;
	rotation.x = 0;
	rotation.y = 0;
	direction.x = 0;
	direction.y = 0;
}
