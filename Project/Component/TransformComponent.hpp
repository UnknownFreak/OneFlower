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
	Vector2 position;
	
	//Pixel count and not Multiply
	Vector2 size;

	//Yet TBD
	Vector2 rotation;
	bool a = true;
	void attachOn(GameObject* go);

	//Move towrads Absolute World coordinates with Pixel Per Seconds
	void moveTo(double x,double y,double s);
	
	
	//Move relative 
	void move(Vector2 dir,double s);

	//Get the angle towards target
	double angle(TransformComponent* target);


	//Get distance towards target in Pixels
	double distance(TransformComponent* target);
private:

	template<class Archive>
	friend void save(Archive &ar, const TransformComponent &tc);
	template<class Archive>
	friend void load(Archive &ar, TransformComponent &tc);
};





#endif