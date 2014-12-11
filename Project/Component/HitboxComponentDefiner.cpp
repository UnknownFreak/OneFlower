#include "HitboxComponent.hpp"
const unsigned int IBaseComponent<HitboxComponent>::typeID = 1003;
std::string IBaseComponent<HitboxComponent>::componentName = "HitBoxComponent";
HitboxComponent::HitboxComponent():size(1,1),position(0,0)
{
	//size = Vector2<int>(1,1);
	//position = Vector2<int>(0,0);
	REGISTER_EDITOR_VARIABLE(Vector2<int>, position, Position);
	REGISTER_EDITOR_VARIABLE(Vector2<double>, size, Size);
}
HitboxComponent::HitboxComponent(const HitboxComponent &hc)
{
	REGISTER_EDITOR_VARIABLE(Vector2<int>, position, Position);
	REGISTER_EDITOR_VARIABLE(Vector2<double>, size, Size);

	this->position.x = hc.position.x;
	this->position.y = hc.position.y;
	this->size.x = hc.size.x;
	this->size.y = hc.size.y;
}