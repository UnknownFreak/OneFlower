#ifndef PlayerComponent_HPP
#define PlayerComponent_HPP
#include "IBaseComponent.hpp"
#include "../../Vector.h"

class MovementComponent;
class GameObject;
class PlayerComponent:public IBaseComponent < PlayerComponent >
{
public:

protected:
	void attachOn(GameObject* attachingOn);

private:
	/*
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	//*/
	void manoeuvre(Vector2 direction);
};

#endif