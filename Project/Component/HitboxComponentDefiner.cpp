#include "HitboxComponent.hpp"
#include "../Engine.hpp"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.hpp"
const unsigned int IBaseComponent<HitboxComponent>::typeID = 1003;
std::string IBaseComponent<HitboxComponent>::componentName = "HitBoxComponent";
HitboxComponent::HitboxComponent():size(0,0),position(0,0)
{
}
HitboxComponent::HitboxComponent(const HitboxComponent &hc) : size(hc.size),position(hc.position)
{
}
HitboxComponent::HitboxComponent(int width,int height) : size(width,height),position(0,0)
{
}
HitboxComponent::~HitboxComponent()
{
	Engine::Physics.removePhysics(this);
}

void HitboxComponent::registerCollisionCheck(BaseComponent* component)
{
	collisionCall.push_back(component);
}

void HitboxComponent::attachOn(GameObject* go)
{
	BaseComponent::attachOn(go);
	//Dont put this in constructors, Cause rigidcomponent will call this twice from constructor hierarchy calls
	REGISTER_EDITOR_VARIABLE(Vector2,position,Position);
	REGISTER_EDITOR_VARIABLE(Vector2,size,Size);
	if(size.x == 0 || size.y == 0)
	{
		RenderComponent* rc = attachedOn->GetComponent<RenderComponent>();
		if(rc)
		{
			size.x = rc->size.x;
			size.y = rc->size.y;
		}
		else
		{
			size.x = 64;
			size.y = 64;
		}
	}
	Engine::Physics.addPhysics(this);
}