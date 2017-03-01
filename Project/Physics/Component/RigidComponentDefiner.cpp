#include "RigidComponent.hpp"
#include "../PhysicsCore.hpp"

const unsigned int IBaseComponent<Component::RigidComponent>::typeID = 10905;
Core::String IBaseComponent<Component::RigidComponent>::componentName = "RigidComponent";

namespace Component
{
	//LOW: Remove this if not needed
	RigidComponent::RigidComponent() :bounding(0, 0, 128, 128)
	{
	}
	RigidComponent::~RigidComponent()
	{
		//Engine::Physics.removePhysics(this);
		Engine::Physics.removePhysics(this);
	}
	RigidComponent * RigidComponent::copy()
	{
		return new RigidComponent(*this);
	}

	void RigidComponent::attachOn(GameObject* go)
	{
		//Dont put this in constructors, Cause rigidcomponent will call this twice from constructor hierarchy calls

		BaseComponent::attachOn(go);
		Engine::Physics.addPhysics(this);
	}
	/*
	bool RigidComponent::inMotion()
	{
		if(force)
			return true;
		return false;
	}
	//*/
	/*
	void RigidComponent::replaceForce(Vector2 dir,float power)
	{
		if(dir.normalize())
			direction = dir;
		force = power;
	}
	//*/
}