#ifndef TransformComponent_HPP
#define TransformComponent_HPP
#include "IBaseComponent.hpp"
#include "../Vector.h"

class TransformComponent: public IBaseComponent<TransformComponent>
{
public:

	TransformComponent();
	//Relative to the Window
	Vector2<int> position;

	//Pixel count and not Multiply
	Vector2<int> size;

	//Yet TBD
	Vector2<int> rotation;
};






#endif