#ifndef HitboxComponent_HPP
#define HitboxComponent_HPP
#include "IBaseComponent.hpp"
#include "../Vector.h"
#include "cereal\access.hpp"
class HitboxComponent:public IBaseComponent<HitboxComponent>
{
public:
	HitboxComponent();
	HitboxComponent(const HitboxComponent &hc);
	//Multiply
	Vector2<double> size;
	//Pixel position relative to Transform
	Vector2<int> position;

	void OnClick();
private:
	template <class Archive>
	void save(Archive &ar, const HitboxComponent &hc);
	template <class Archive>
	void load(Archive &ar,HitboxComponent &hc);
};
#endif