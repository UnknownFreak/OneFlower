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
	ProjectileComponent();

	void attachOn(GameObject * go);
	void shoot(Vector2 mouse);
	void updateOne();
	void updateTwo();
	void updateThree();

private:
	//speed of projectile
	double velosity = 0;
	double speed;
	double x;
	double dt;
	Vector2 destination;
};
#endif
