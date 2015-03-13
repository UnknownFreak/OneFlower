#include "Vector.h"
#include <cmath>
#include <Windows.h>
#include "Engine.hpp"
Vector2::Vector2()
{
	x = 0;
	y = 0;
}
Vector2::Vector2(int a,int b)
{
	x = a;
	y = b;
}
double Vector2::distance(Vector2* target)
{
	double px = ((target->x - x) * (target->x - x));
	double py = ((target->y - y) * (target->y - y));

	return  std::sqrt(px + py);
	
}

double Vector2::angle(Vector2* target)
{
	double deltaX = target->x - x;
	double deltaY = target->y - y;

	int angleInDegree = std::atan2(deltaY,deltaX) * 180 / 3.14159265358979323846;
	return angleInDegree;
}
Vector2 Vector2::direction(Vector2* target)
{
	//LOW: use operator
	return Vector2(target->x - x,target->y - y);
}





bool Vector2::normalize()
{

	float len = sqrt(x*x + y*y);
	if(len != 0)
	{
		x = x / len;
		y = y / len;
		normalized = true;
		return true;
	}
	else
		return false;	//MessageBox(NULL,"Divided by 0","Law of Physics says No",0);

	//LOW: Fix this someday and be sure to check some math site this time to. 15/02/13
}
void Vector2::operator+=(Vector2& right)
{
	x += right.x;
	y += right.y;
}
void Vector2::operator-=(Vector2& right)
{
	x -= right.x;
	y -= right.y;
}
void Vector2::operator*=(Vector2& right)
{
	x *= right.x;
	y *= right.y;
}
Vector2 Vector2::operator-(Vector2 right)
{
	Vector2 left(x,y);
	left.x -= right.x;
	left.y -= right.y;


	return left;
}