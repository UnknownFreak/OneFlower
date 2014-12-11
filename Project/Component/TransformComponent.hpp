#ifndef TransformComponent_HPP
#define TransformComponent_HPP
#include "IBaseComponent.hpp"
#include "../Vector.h"
#include <cereal/access.hpp>
class TransformComponent: public IBaseComponent<TransformComponent>
{
public:
	TransformComponent();

	TransformComponent(const TransformComponent &tc);
	//Relative to the Window
	Vector2<int> position;
	
	//Pixel count and not Multiply
	Vector2<int> size;

	//Yet TBD
	Vector2<int> rotation;
private:

	template<class Archive>
	friend void save(Archive &ar, const TransformComponent &tc);
	template<class Archive>
	friend void load(Archive &ar, TransformComponent &tc);
};





#endif