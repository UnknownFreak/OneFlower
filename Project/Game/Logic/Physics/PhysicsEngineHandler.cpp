#include <SFML\Graphics\Rect.hpp>
#include "Physics.hpp"
#include "../../Component/RigidComponent.hpp"
#include "../../Component/GameObject.h"
#include "../../Component/TransformComponent.hpp"
#include "../../Component/HitboxComponent.hpp"
#include "../../../Engine.hpp"
//#include "ColliderBasic.hpp"
#include "Movement.hpp"
void PhysicsEngine::update()
{
	//gravity();
	//simulation();
}
void PhysicsEngine::gravity()
{
	/*
	for(size_t i = 0; i < rigids.size(); i++)
	{
		if(rigid[i]->gravity)
		{
			TransformComponent* tc = rigid[i]->attachedOn->GetComponent<TransformComponent>();
			Vector2 past = tc->position;

			Vector2 direction(0,1);
			double velocity = (Gravity*PixelInOneMeter);
			//rigid[i]->movement.addTranslation(direction,velocity);
			//->GetComponent<>()->addForce(Vector2(0,1),velocity);
		}
	}
	//*/
}

void PhysicsEngine::simulation()
{
	/*
	for(size_t i = 0; i < rigid.size(); i++)
	{
		TransformComponent* tc = rigid[i]->attachedOn->GetComponent<TransformComponent>();
		{
			if(rigid[i]->inMotion())
			{
				double force = rigid[i]->force;
				Vector2 direction = rigid[i]->direction;
				std::pair<GameObject*,double> collider = collision(rigid[i],Vector2(direction.x*force,direction.y*force));
				//HIGH: Checking how force move object on google.PS check collision and pass throug hitbox but still tirgger
				if(collider.second >= 1)
					tc->move(direction,force);
				else
					tc->move(direction,force*collider.second);
			}
		}
		//rigid[i]->forceQueue.clear();
	}
	//*/
}

//LOW: Change owner 
Physics::Collider PhysicsEngine::collision(TransformComponent* motion,Physics::BoundingBox bbox,Vector2 speed)
{
	//When two object travel in the same direction, The one who "Update" first will decide the outcome. If its the chaser than it catches, if its the runner than it flee. Thats the simpliest way todo it 
	Physics::Collider collider;

	/*
	for(size_t i = 0; i < hitboxes.size(); ++i)
	{
		HitboxComponent* hitbox = hitboxes[i];
		Physics::BoundingBox boxMoving(motion->position+speed,bbox.size);
		Physics::BoundingBox boxStatic
			(
				hitbox->attachedOn->GetComponent<TransformComponent>()->position,hitbox->bounding.size
			);

		//if(X1 + W1<X2 or X2 + W2<X1 or
		//Y1 + H1<Y2 or Y2 + H2<Y1) :

		#pragma region BroadPhase
		if(boxMoving.position.y +boxMoving.size.y < boxStatic.position.y)
			continue;
		else if(boxStatic.position.y + boxStatic.size.y < boxMoving.position.y)
			continue;
		else if(boxMoving.position.x + boxMoving.size.x < boxStatic.position.x)
			continue;
		else if(boxStatic.position.x + boxStatic.size.x < boxMoving.position.x)
			continue;
		#pragma endregion 
		else
		{
			float timeCx = 9000;
			float timeCy = 9000;
			float distanceCx = 9000;
			float distanceCy = 9000;

			if(speed.x > 0)
				distanceCx = boxStatic.position.x - (boxMoving.position.x + boxMoving.size.x);
			else if(speed.x < 0)
				distanceCx = (boxStatic.position.x + boxStatic.size.x) - boxMoving.position.x;
			if(speed.y > 0)
				distanceCy = boxStatic.position.y - (boxMoving.position.y + boxMoving.size.y);
			else if(speed.y < 0)
				distanceCy = (boxStatic.position.y + boxStatic.size.y) - boxMoving.position.y;
			//HIGH: Remove this and make it just return the collision time and let the game decide what happends with multi collision, put this intersection inside boundingbox? 

			//HIGH: this is somehow wrongs dont know any fixes yet
			float shortDist = distanceCx < distanceCy ? distanceCx : distanceCy;
			
			if(shortDist < collider.time)
			{
				collider.time = shortDist;
				collider.contact = hitbox->attachedOn;
			}
		}
	}
	//*/
	return collider;
}
