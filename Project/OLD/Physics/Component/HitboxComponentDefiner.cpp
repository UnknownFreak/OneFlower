#include "HitboxComponent.hpp"
#include <Core\Component\GameObject.h>
#include <Core\Component\TransformComponent.hpp>

#include <Core\IEngineResource\EngineResourceManager.hpp>

#include <Graphic\Component\RenderComponent.h>

#include <Physics\Physics.hpp>

const unsigned int IBaseComponent<Component::HitboxComponent>::typeID = 1003;
Core::String IBaseComponent<Component::HitboxComponent>::componentName = "HitBoxComponent";

namespace Component
{
	HitboxComponent::HitboxComponent() :bounding(0, 0, 128, 128)
	{
	}
	HitboxComponent::HitboxComponent(const HitboxComponent &hc) : bounding(hc.bounding.position, hc.bounding.size)
	{
	}
	HitboxComponent::HitboxComponent(float x, float y, int w, int h) : bounding(x, y, w, h)
	{
	}
	HitboxComponent::~HitboxComponent()
	{
		Engine::Get<PhysicsEngine>().removePhysics(this);
	}

	void HitboxComponent::registerCollisionCheck(BaseComponent* component)
	{
		collisionCall.push_back(component);
	}

	HitboxComponent * HitboxComponent::copy() const
	{
		return new HitboxComponent(*this);
	}
	void HitboxComponent::attachOn(GameObject* go)
	{
		BaseComponent::attachOn(go);
		//Dont put this in constructors, Cause rigidcomponent will call this twice from constructor hierarchy calls

		if (bounding.size.x == 0 || bounding.size.y == 0)
		{
			RenderComponent* rc = attachedOn->GetComponent<RenderComponent>();
			if (rc)
			{
				bounding.size.x = 64;
				bounding.size.y = 64;
			}
			else
			{
				bounding.size.x = 64;
				bounding.size.y = 64;
			}
		}
		Engine::Get<PhysicsEngine>().addPhysics(this);
	}
}