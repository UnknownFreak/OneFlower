#include "TransformComponent.hpp"
unsigned int IBaseComponent<TransformComponent>::typeID = 1005;

TransformComponent::TransformComponent():position(0,0),rotation(1,1),size(1,1)
{
}
TransformComponent::TransformComponent(const TransformComponent &tc)
{
	this->componentName = tc.componentName;
	this->position.x = tc.position.x;
	this->position.y = tc.position.y;
	this->rotation.x = tc.rotation.x;
	this->rotation.y = tc.rotation.y;
	this->size.x = tc.size.x;
	this->size.y = tc.size.y;
}