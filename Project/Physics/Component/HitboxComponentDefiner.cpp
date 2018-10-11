#include "HitboxComponent.hpp"
#include <Core\Component\GameObject.h>
#include <Core\Component\TransformComponent.hpp>

#include <Core\EngineModule\EngineModuleManager.hpp>

#include <Graphic\Component\RenderComponent.h>

#include <Physics\Physics.hpp>

const unsigned int Component::IBaseComponent<Component::HitboxComponent>::typeID = 1003;
Core::String Component::IBaseComponent<Component::HitboxComponent>::componentName = "HitBoxComponent";

namespace Component
{
	HitboxComponent::HitboxComponent() : HitboxComponent(0.f, 0.f, 128.f, 128.f)
	{
	}
	HitboxComponent::HitboxComponent(const HitboxComponent &hc) : bounding(hc.bounding.x, hc.bounding.y, hc.bounding.w, hc.bounding.h),
		ICollider(bounding.x, bounding.y, bounding.w, bounding.h)
	{
	}
	HitboxComponent::HitboxComponent(float x, float y, float w, float h) : bounding(x, y, w, h), ICollider(bounding.x, bounding.y, bounding.w, bounding.h)
	{
	}
	HitboxComponent::~HitboxComponent()
	{
		Engine::GetModule<PhysicsEngine>().removePhysics(this);
	}

	void HitboxComponent::registerCollisionCheck(Base* component)
	{
		collisionCall.push_back(component);
	}

	HitboxComponent * HitboxComponent::copy() const
	{
		return new HitboxComponent(*this);
	}
	void HitboxComponent::attachOn(GameObject* go)
	{
		Base::attachOn(go);
		//Dont put this in constructors, Cause rigidcomponent will call this twice from constructor hierarchy calls

		if (bounding.x == 0 || bounding.y == 0)
		{
			RenderComponent* rc = attachedOn->GetComponent<RenderComponent>();
			if (rc)
			{
				bounding.x = 64;
				bounding.y = 64;
			}
			else
			{
				bounding.x = 64;
				bounding.y = 64;
			}
		}
		Engine::GetModule<PhysicsEngine>().addPhysics(this);
	}
}