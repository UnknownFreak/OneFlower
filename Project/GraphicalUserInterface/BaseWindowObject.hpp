#ifndef BaseWindowObject_HPP
#define BaseWindowObject_HPP

#include "../Vector.h"
class BaseWindowObject
{
public:

	virtual ~BaseWindowObject() = default;
	virtual void draw() = 0
	{
	};
	virtual Vector2 getPosition();
	virtual Vector2 getSize();
	virtual void setPosition(Vector2 pos);
	virtual void setSize(Vector2 s);
	virtual void setPosition(double x, double y);
	virtual void setSize(double sizeX, double sizeY);
	int type = 0;
protected:
	Vector2 position;
	Vector2 size;

};




#endif