#include "Physics.hpp"
#include "Component\RigidComponent.hpp"
#include "Component\GameObject.h"
#include "Component\TransformComponent.hpp"
#include "Component\RenderComponent.h"
#include "Component\HitboxComponent.hpp"
bool AABB(RigidComponent* a,HitboxComponent* b);
#include "Engine.hpp"

void PhysicsEngine::Update()
{
	for(size_t i = 0; i < rigid.size(); i++)
	{
		//TODO swap for quad
		for(size_t j = 0; j < hitboxes.size(); j++)
		{
			//TODO: Swap for a Swept AABB someday
			if(AABB(rigid.at(i),hitboxes.at(j)))
			{
				//TODO: QuadTree: Atleast divide the Static hitbox into 4 list 
				//LOW: Perhaps move this to inside gameobject? or something similar
				//LOW: Alternative store what hit what and loop all at the same time: May get better timing?
				for(std::map<int,BaseComponent*>::iterator kt = rigid[i]->attachedOn->GetComponents()->begin(); kt != rigid[i]->attachedOn->GetComponents()->end(); kt++)
				{
	 				kt->second->onCollision(hitboxes[j]->attachedOn);	
				}
			}
		}
		/*
		for(size_t j = i; j < rigid.size(); j++)
		{
			if(AABB(rigid.at(i),rigid.at(j)))
			{
				std::cout<< "Object " + rigid[i]->attachedOn->name + ": Hit : Object " + rigid[j]->attachedOn->name;
			}
		}
		//*/	
	}
}
bool AABB(RigidComponent* a,HitboxComponent* b)
{
	//LOW: Remove this one day due to updating AABB code
	if(a->attachedOn->GetComponent<RenderComponent>() && b->attachedOn->GetComponent<RenderComponent>())
	{
		Vector2 posA = a->attachedOn->GetComponent<TransformComponent>()->position;
		Vector2 posB = b->attachedOn->GetComponent<TransformComponent>()->position;
		


		int OB1top = posA.y - (a->size.y / 2);
		int OB1bot = posA.y + (a->size.y / 2);

		int OB1right = posA.x + (a->size.x / 2);
		int OB1left = posA.x - (a->size.x / 2);

		int OB2top = posB.y - (a->size.y / 2);
		int OB2bot = posB.y + (a->size.y / 2);

		int OB2right = posB.x + (a->size.x / 2);
		int OB2left = posB.x - (a->size.x / 2);



		// Check the collision Horizontally

		// > Because the higher the more right, 0,0 top left 
		// this means that OB1 is to the right of OB2 
		if(OB1left > OB2right)
			return false;


		// > Because the higher the more right, 0,0 top left 
		// this means that OB2 is to the right of OB1 
		if(OB2left > OB1right)
			return false;


		//< Because the lower the higher, 0,0 top left 
		//this means that OB1 is above OB2,	far enough to guarantee not to be touching
		if(OB1bot < OB2top)
			return false;


		//< Because the lower the higher, 0,0 top left 
		//this means that OB2 is above OB1 
		if(OB2bot < OB1top)
			return false;
		if(Engine::time.time("Collision",5))
			Engine::Window.print("Collision: " + a->attachedOn->name + "-> " + b->attachedOn->name + "\n");

		return true;
	}
}

float SweptAABB(HitboxComponent b1,HitboxComponent b2,float& normalx,float& normaly)
{
	float xInvEntry = 0;
	float yInvEntry = 0;
	float xInvExit = 0;
	float yInvExit = 0;

	/*

	// find the distance between the objects on the near and far sides for both x and y
	if(b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if(b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}
	// We have an overlap
	
	//*/
	return 0.5f;
};