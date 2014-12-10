#include "HitboxComponent.hpp"
unsigned int IBaseComponent<HitboxComponent>::typeID = 1003;
HitboxComponent::HitboxComponent():size(1,1),position(0,0)
{
	//size = Vector2<int>(1,1);
	//position = Vector2<int>(0,0);
}
HitboxComponent::HitboxComponent(const HitboxComponent &hc)
{
	this->componentName = hc.componentName;
	this->position.x = hc.position.x;
	this->position.y = hc.position.y;
	this->size.x = hc.size.x;
	this->size.y = hc.size.y;
}