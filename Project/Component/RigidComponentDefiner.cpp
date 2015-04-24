#include "RigidComponent.hpp"
std::string IBaseComponent<RigidComponent>::componentName = "RigidComponent";
const unsigned int IBaseComponent<RigidComponent>::typeID = 10905;
#include "../Engine.hpp"

//LOW: Remove this if not needed
RigidComponent::RigidComponent():size(128,128)
{
}
RigidComponent::~RigidComponent()
{
	Engine::Physics.removePhysics(this);
}
void RigidComponent::attachOn(GameObject* go)
{
	//Dont put this in constructors, Cause rigidcomponent will call this twice from constructor hierarchy calls
	REGISTER_EDITOR_VARIABLE(Vector2,position,Position);
	REGISTER_EDITOR_VARIABLE(Vector2,size,Size);
	REGISTER_EDITOR_VARIABLE(int,this->Mass,Mass);
	REGISTER_EDITOR_VARIABLE(bool,gravity,Gravity);

	BaseComponent::attachOn(go);
	Engine::Physics.addPhysics(this);
}