#ifndef PlayerComponent_HPP
#define PlayerComponent_HPP
#include "IBaseComponent.hpp"
#include "../../Vector.h"

class RigidComponent;
class GameObject;
class PlayerComponent:public IBaseComponent < PlayerComponent >
{
public:
#ifdef _EDITOR_
	void setMovementSpeed(int speed);
#endif
protected:
	void attachOn(GameObject* attachingOn);

private:
	RigidComponent* rigid;
	int movementSpeed = 150;


	//HIGH: Fix the double movementspeed bug by holdind down two buttons
	void manoeuvre(Vector2 direction);
};

#endif