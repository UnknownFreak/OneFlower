#ifndef RigidComponent_HPP
#define RigidComponent_HPP
#include "IBaseComponent.hpp"
#include <vector>
#include "../Vector.h"
class RigidComponent:public IBaseComponent < RigidComponent >
{
public:

	//LOW: Remove this if not needed
	//TODO Add other constructors
	RigidComponent();
	~RigidComponent();
	bool inMotion();
	void replaceForce(Vector2 dir,float power);
	//std::vector<std::pair<Vector2,double>> forceQueue;

	//Absolute Pixel not half pixel
	Vector2 size;

	//Pixel position relative to Transform
	Vector2 position;

	Vector2 direction;
	double force;

	//Colliding
	bool colliding = false;

	//Colliding Object. [0] up and than go Clock-Wise
	//GameObject* colisionDirection[4];

	bool gravity = false;

	//Mass in Kilogram
	int mass = 10;

	std::vector<GameObject*> entered;

protected:
	void attachOn(GameObject* go);
private:


};

#endif