#ifndef MovementComponent_HPP
#define MovementComponent_HPP
#include "../../Vector.h"
#include "IBaseComponent.hpp"
#include <vector>
//Instantenous Movement, If accelreation is desired please use the appropriate component for it
class MovementComponent: public IBaseComponent < MovementComponent >
{

public:

	Vector2 direction;
	int distance;
	double speed;
	double rotation;
	std::vector<std::pair<Vector2,double>> movementsQueue;

public:

	//Return true if the object is in motion (Ex: Displacement, Rotation)
	bool inMotion();

	void addForce(Vector2 direction,double speed);
	//Replace the movement vectors
	void replaceMotion(Vector2 direction,double speed,int distance);
	void attachOn(GameObject* entity);

private:
	/*
	class SpeedVector
	{
	public:
	SpeedVector(Vector2 dir,double cSpeed);
	double speed;
	Vector2 direction;
	};
	//*/
	//Move at parameter direction with s Speed
	//void moveAt(Vector2 direction, double speed);
	//void update();
};
//*/
#endif