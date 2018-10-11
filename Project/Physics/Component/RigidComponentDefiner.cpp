#include "RigidComponent.hpp"
#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Physics\Physics.hpp>

const unsigned int Component::IBaseComponent<Component::RigidComponent>::typeID = 10905;
Core::String Component::IBaseComponent<Component::RigidComponent>::componentName = "RigidComponent";

namespace Component
{
	//LOW: Remove this if not needed
	RigidComponent::RigidComponent() : RigidComponent(0.f, 0.f, 128.f, 128.f)
	{
	}
	RigidComponent::RigidComponent(const RigidComponent & rc) : bounding(rc.bounding.x, rc.bounding.y, rc.bounding.w, rc.bounding.h),
		ICollider(bounding.x, bounding.y, bounding.w, bounding.h)
	{
	}
	RigidComponent::RigidComponent(float x, float y, float w, float h) : bounding(x, y, w, h),
		ICollider(bounding.x, bounding.y, bounding.w, bounding.h)
	{
	}
	RigidComponent::~RigidComponent()
	{
		//Engine::Physics.removePhysics(this);
		Engine::GetModule<PhysicsEngine>().removePhysics(this);
	}
	RigidComponent * RigidComponent::copy() const
	{
		return new RigidComponent(*this);
	}

	void RigidComponent::attachOn(GameObject* go)
	{
		//Dont put this in constructors, Cause rigidcomponent will call this twice from constructor hierarchy calls
		Base::attachOn(go);
		Engine::GetModule<PhysicsEngine>().addPhysics(this);
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