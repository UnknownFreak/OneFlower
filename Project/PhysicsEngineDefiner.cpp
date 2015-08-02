#include "Physics.hpp"
#include "Engine.hpp"
//LOW Is this really needed?
#include "Vector.h"
#include "Component\RigidComponent.hpp"

void PhysicsEngine::addPhysics(RigidComponent* obj)
{
	if(obj)
		rigid.push_back(obj);
}
void PhysicsEngine::addPhysics(HitboxComponent* obj)
{
	if(obj)
		hitboxes.push_back(obj);
}

void PhysicsEngine::removePhysics(RigidComponent* obj)
{
	if(obj)
		for(size_t i = 0; i < rigid.size(); ++i)
			if(rigid[i] == obj)
			{
				rigid.erase(rigid.begin() + i);
				break;
			}
}
void PhysicsEngine::removePhysics(HitboxComponent* obj)
{
	if(obj)
		for(size_t i = 0; i < hitboxes.size(); ++i)
			if(obj == hitboxes[i])
			{
				hitboxes.erase(hitboxes.begin() + i);
				break;
			}
}

//LOW dont think this is needed, Only prototype
#include "Component\GameObject.h"
void PhysicsEngine::addPhysics(GameObject* obj)
{
	HitboxComponent* a = obj->GetComponent<HitboxComponent>();
	if(a)
		hitboxes.push_back(a);
}
PhysicsEngine::PhysicsEngine()
//:quad(0)
{
	size_t x = Engine::Graphic.view.render.getSize().x;
	size_t y = Engine::Graphic.view.render.getSize().y;

	////LOW: Use init list
	//quad.position[0].x = 0;
	//quad.position[0].y = 0;
	//quad.position[1].x = x;
	//quad.position[1].y = y;
}