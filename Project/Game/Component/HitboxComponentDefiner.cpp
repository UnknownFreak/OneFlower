#include "HitboxComponent.hpp"
#include "../../Engine.hpp"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.hpp"
const unsigned int IBaseComponent<HitboxComponent>::typeID = 1003;
std::string IBaseComponent<HitboxComponent>::componentName = "HitBoxComponent";
HitboxComponent::HitboxComponent():bounding(0,0,1,1)
{

}
HitboxComponent::HitboxComponent(const HitboxComponent &hc) : bounding(hc.bounding.position.x,hc.bounding.position.y,hc.bounding.size.x,hc.bounding.size.y)
{

}
HitboxComponent::HitboxComponent(int x,int y,int w,int h) : bounding(x,y,w,h)
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

	REGISTER_EDITOR_VARIABLE(Vector2,bounding.position,Position);
	REGISTER_EDITOR_VARIABLE(Vector2,bounding.size,Size);
	if(bounding.size.x == 0 || bounding.size.y == 0)
	{
		RenderComponent* rc = attachedOn->GetComponent<RenderComponent>();
		if(rc)
		{
			bounding.size.x = rc->size.x;
			bounding.size.y = rc->size.y;
		}
		else
		{
			bounding.size.x = 64;
			bounding.size.y = 64;
		}
	}
	Engine::Physics.addPhysics(this);
}