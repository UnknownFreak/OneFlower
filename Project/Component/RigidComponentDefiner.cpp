#include "RigidComponent.hpp"
std::string IBaseComponent<RigidComponent>::componentName = "RigidComponent";
 const unsigned int IBaseComponent<RigidComponent>::typeID = 10905;
#include "../Engine.hpp"

 //LOW: Remove this if not needed
RigidComponent::RigidComponent()
{

}
void RigidComponent::attachOn(GameObject* go)
{

	//Dont put this in constructors, Cause rigidcomponent will call this twice from constructor hierarchy calls
	REGISTER_EDITOR_VARIABLE(Vector2,position,Position);
	REGISTER_EDITOR_VARIABLE(Vector2,size,Size);

	BaseComponent::attachOn(go);
	Engine::Physics.addPhysics(this);
}