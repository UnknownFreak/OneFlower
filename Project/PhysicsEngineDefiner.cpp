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







//LOW dont think this is needed, Only prototype
#include "Component\GameObject.h"
void PhysicsEngine::addPhysics(GameObject* obj)
{
	HitboxComponent* a = obj->GetComponent<HitboxComponent>();
	if(a)
		hitboxes.push_back(a);

}
PhysicsEngine::PhysicsEngine():quad(0)
{
	size_t x = Engine::Window.View.getSize().x;
	size_t y = Engine::Window.View.getSize().y;

	//LOW: Use init list
	quad.position[0].x = 0;
	quad.position[0].y = 0;
	quad.position[1].x = x;
	quad.position[1].y = y;

}