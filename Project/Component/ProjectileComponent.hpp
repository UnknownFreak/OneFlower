#ifndef ProjectileComponent_hpp
#define ProfectileComponent_hpp
#include "IBaseComponent.hpp"
#include "../Engine.hpp"
#define PI 3.14159
#define G 9.081

class GameObject;
class ProjectileComponent : public IBaseComponent < ProjectileComponent >
{
public:
	void attachOn(GameObject * go);
	void shoot(Vector2 mouse);
	void updateOne();
	void updateTwo();
	void updateThree();

private:
	//speed of projectile
	double velosity = 100;
	double speed;
	double x = 500;
	double y = 0;
	double centerMid = 0;
	float distance;
	Vector2 wave;
	Vector2 movementDirection;
};
#endif
