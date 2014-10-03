#ifndef HitboxComponent_HPP
#define HitboxComponent_HPP
#include "IBaseComponent.hpp"
#include "../Vector.h"
class HitboxComponent:public IBaseComponent<HitboxComponent>
{
public:
	HitboxComponent();

	//Multiply
	Vector2<double> size;
	//Pixel position relative to Transform
	Vector2<int> position;

	void OnClick();
};
#endif