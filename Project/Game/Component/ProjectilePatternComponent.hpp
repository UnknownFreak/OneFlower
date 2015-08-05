#ifndef ProjectilePatternComponent_hpp
#define ProjectilePatternComponent_hpp
#include "IBaseComponent.hpp"
#include "../../Engine.hpp"
#define PI 3.14159
#define G 9.081

class GameObject;
class ProjectilePatternComponent: public IBaseComponent < ProjectilePatternComponent >
{
public:
	void attachOn(GameObject * go);
	void updateMousePos(Vector2 mouse);
	void followMouse();
	void wavePattern();
	void missileX();
	void missileY();
	void vPattern();

private:
	//speed of projectile
	double velosity = 100;
	double speed;
	double x = 0;
	double y = -1;
	double centerMid = 0;
	double distanceTraveled = 0;
	Vector2 startPos;
	Vector2 movementDirection;
};
#endif