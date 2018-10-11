#include "Physics.hpp"
//#include "../../../Engine.hpp"
//LOW Is this really needed?
//#include "../../../Vector.h"
//#include "../../Component/RigidComponent.hpp"

#include "Component\HitboxComponent.hpp"
#include "Component\RigidComponent.hpp"


ResourceType IEngineResource<PhysicsEngine>::type = ResourceType::Physics;


void PhysicsEngine::addPhysics(Component::RigidComponent* obj)
{
	if (obj)
		quadTree.insert(obj);
}
void PhysicsEngine::addPhysics(Component::HitboxComponent* obj)
{
	if (obj)
		quadTree.insert(obj);
}

void PhysicsEngine::removePhysics(Component::RigidComponent* obj)
{
	if (obj)
		quadTree.remove(obj);
}
void PhysicsEngine::removePhysics(Component::HitboxComponent* obj)
{
	if (obj)
		quadTree.remove(obj);
}

/*
PhysicsEngine::Collider::Collider()
{
}
//*/

//LOW dont think this is needed, Only prototype
//#include "../../Component/GameObject.h"
/*
void PhysicsEngine::addPhysics(GameObject* obj)
{
	HitboxComponent* a = obj->GetComponent<HitboxComponent>();
	if(a)
		hitboxes.push_back(a);
}
//*/
PhysicsEngine::PhysicsEngine() :  quadTree(0.f, 0.f, 2048.f, 2048.f)
//:quad(0)
{
	//size_t x = Engine::Graphic.view.render.getSize().x;
	//size_t y = Engine::Graphic.view.render.getSize().y;

	////LOW: Use init list
	//quad.position[0].x = 0;
	//quad.position[0].y = 0;
	//quad.position[1].x = x;
	//quad.position[1].y = y;
}
