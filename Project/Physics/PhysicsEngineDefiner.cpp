#include "Physics.hpp"
//#include "../../../Engine.hpp"
//LOW Is this really needed?
//#include "../../../Vector.h"
//#include "../../Component/RigidComponent.hpp"


void PhysicsEngine::addPhysics(Component::RigidComponent* obj)
{
	if (obj)
		rigids.push_back(obj);
}
void PhysicsEngine::addPhysics(Component::HitboxComponent* obj)
{
	if (obj)
		hitboxes.push_back(obj);
}

void PhysicsEngine::removePhysics(Component::RigidComponent* obj)
{
	if (obj)
		for (size_t i = 0; i < rigids.size(); ++i)
			if (rigids[i] == obj)
			{
				rigids.erase(rigids.begin() + i);
				break;
			}
}
void PhysicsEngine::removePhysics(Component::HitboxComponent* obj)
{
	if (obj)
		for (size_t i = 0; i < hitboxes.size(); ++i)
			if (obj == hitboxes[i])
			{
				hitboxes.erase(hitboxes.begin() + i);
				break;
			}
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
PhysicsEngine::PhysicsEngine()
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