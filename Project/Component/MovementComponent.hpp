#ifndef MovementComponent_HPP
#define MovementComponent_HPP
#include "../Vector.h"
#include "IBaseComponent.hpp"
#include <vector>
//Instantenous Movement, If accelreation is desired please use the appropriate component for it
class MovementComponent: public IBaseComponent<MovementComponent>
{
public:

	//Return true if the object is moving
	bool inMotion();
	
	void addForce(Vector2 direction,double speed);
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
protected:

	Vector2 direction;
	int distance;
	double speed;
	double rotation;
	std::vector<std::pair<Vector2,double>> forces;


	//Move at parameter direction with s Speed
	//void moveAt(Vector2 direction, double speed);
	//void update();
};
//*/
#endif