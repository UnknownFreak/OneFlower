#ifndef RigidComponent_HPP
#define RigidComponent_HPP
#include "IBaseComponent.hpp"
#include <vector>
#include "../Vector.h"
class RigidComponent:public IBaseComponent < RigidComponent >
{
public:

	//LOW: Remove this if not needed
	RigidComponent();
	~RigidComponent();
	//TODO Add other constructors

	//Absolute Pixel not half pixel
	Vector2 size;

	//Pixel position relative to Transform
	Vector2 position;

	//Colliding
	bool colliding = false;

	void attachOn(GameObject* go);

	std::vector<GameObject*> entered;
};

#endif