#include <SFML\Graphics\Rect.hpp>
#include "Physics.hpp"
#include "../../Component/RigidComponent.hpp"
#include "../../Component\GameObject.h"
#include "../../Component\TransformComponent.hpp"
#include "../../Component\RenderComponent.h"
#include "../../Component\HitboxComponent.hpp"
#include "../../../Engine.hpp"
//#include "ColliderBasic.hpp"
void PhysicsEngine::update()
{
	gravity();
	simulation();
}
void PhysicsEngine::gravity()
{
	for(size_t i = 0; i < rigid.size(); i++)
	{
		if(rigid[i]->gravity)
		{
			TransformComponent* tc = rigid[i]->attachedOn->GetComponent<TransformComponent>();

			Vector2 past = tc->position;

			Vector2 direction(0,1);
			double velocity = (Gravity*PixelInOneMeter);

			std::pair<GameObject*,double> collisiontime = collision(rigid[i],Vector2(0,direction.y*velocity*Engine::time.deltaTime()));
			
			//HIGH: Checking how force move object on google.PS check collision and pass throug hitbox but still tirgger
			if(collisiontime.second >= 1)
				//tc->move(direction,velocity*Engine::time.deltaTime());
				//tc->position.x += direction.x*velocity;
				tc->position.y += direction.y*(velocity*Engine::time.deltaTime());
			else
				//tc->move(direction,(velocity*Engine::time.deltaTime())*collisiontime);
				//tc->position.x += direction.x*velocity*collisiontime;
				tc->position.y += direction.y*collisiontime.second*(velocity*Engine::time.deltaTime());
			//*/	
			//rigid[i]->replaceForce(Vector2(0,1),velocity*Engifne::time.deltaTime());
		}
	}
}

void PhysicsEngine::simulation()
{
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
}
std::pair<GameObject*,double> PhysicsEngine::collision(RigidComponent* inMotion,Vector2 speed)
{
	TransformComponent* tc = inMotion->attachedOn->GetComponent<TransformComponent>();
	Vector2 topLeft = tc->position + inMotion->position;
	std::vector<std::pair<HitboxComponent*,double>> collisionList;

	for(size_t i = 0; i < hitboxes.size(); i++)
	{
		TransformComponent* tcH = hitboxes[i]->attachedOn->GetComponent<TransformComponent>();
		Vector2 topLeftH = tcH->position + hitboxes[i]->position;
		double timeUntillCollision = 0;

		Vector2 distanceEntry;
		//= topLeft - topLeftH;

		if(speed.x > 0)			//Get the right side of rigid, LeftSide of hitbox
			distanceEntry.x = (topLeft.x + inMotion->size.x) - topLeftH.x;
		else
			distanceEntry.x = (topLeftH.x + hitboxes[i]->size.x) - topLeft.x;
		if(speed.y > 0)			//If the speed is positive it mean the object is going DOWN, and thus topleft.y+height
			distanceEntry.y = topLeftH.y - (topLeft.y + inMotion->size.y);
		else
			distanceEntry.y = topLeft.y - (topLeftH.y + topLeftH.y);

		Vector2 entryTime;
		if(speed.x)
			entryTime.x = distanceEntry.x / speed.x;
		else
			entryTime.x = std::numeric_limits<double>::infinity();
		if(speed.y)
			entryTime.y = distanceEntry.y / speed.y;
		else
			entryTime.y = std::numeric_limits<double>::infinity();

		double collisionTime = 1;
		//Check which entry time is the shortest, than do a broad check, A check to see if object is a aligned to each other
		if(entryTime.y < entryTime.x)
			if(topLeft.x > topLeftH.x + hitboxes[i]->size.x)//If rigid left side is to right side of hitbox right side its a miss
				continue;
			else if(topLeft.x + inMotion->size.x < topLeftH.x)
				continue;
			else
				collisionTime = entryTime.y;
		else
			if(topLeft.y + inMotion->size.y < topLeftH.y)
				continue;
			else if(topLeft.y > topLeftH.y + hitboxes[i]->size.y)
				continue;
			else
				collisionTime = entryTime.x;
			//= (((entryTime.x) < (entryTime.y)) ? (entryTime.x) : (entryTime.y));

			if(collisionTime >= 1 || collisionTime < 0)
				continue;
			else
				collisionList.push_back(std::make_pair(hitboxes[i],collisionTime));
	}

	std::pair<HitboxComponent*,double> fastestCollision(0,1);
	for(size_t i = 0; i < collisionList.size(); i++)
		if(fastestCollision.second > collisionList[i].second)
			fastestCollision = collisionList[i];
	if(fastestCollision.first)
		return std::pair<GameObject*,double>(fastestCollision.first->attachedOn,fastestCollision.second);
	else
		return std::pair<GameObject*,double>(0,1);
}

float PhysicsEngine::SweptAABB(RigidComponent* inMotion,HitboxComponent* b22,float& normalx,float& normaly,Vector2 speed)
{
	std::vector<std::pair<HitboxComponent*,double>> collided;

	TransformComponent* tc = inMotion->attachedOn->GetComponent<TransformComponent>();
	Vector2 topLeft = tc->position + inMotion->position;
	Vector2 bottomRight = topLeft + inMotion->size;

	struct Box
	{
		// position of top-left corner
		float x,y;

		// dimensions
		float w,h;

		// velocity
		float vx,vy;
	};
	Box b1;
	b1.x = topLeft.x;
	b1.y = topLeft.y;
	b1.w = inMotion->size.x;
	b1.h = inMotion->size.y;
	b1.vx = speed.x;
	b1.vy = speed.y;

	for(size_t i = 0; i < hitboxes.size(); i++)
	{
		TransformComponent* tcH = hitboxes[i]->attachedOn->GetComponent<TransformComponent>();
		Vector2 topLeftH = tcH->position + hitboxes[i]->position;
		Vector2 bottomRightH = topLeftH + hitboxes[i]->size;
		Box b2;

		b2.x = topLeft.x;
		b2.y = topLeft.y;
		b2.w = hitboxes[i]->size.x;
		b2.h = hitboxes[i]->size.y;
		b2.vx = 0;
		b2.vy = 0;
		float xInvEntry,yInvEntry;
		float xInvExit,yInvExit;

		// find the distance between the objects on the near and far sides for both x and y
		if(b1.vx > 0.0f)//If the hitbox have movement, but our hitbox will never have movement persay, unless its a rigidbody(cause we use force)
		{
			xInvEntry = b2.x - (b1.x + b1.w);
			xInvExit = (b2.x + b2.w) - b1.x;
		}
		else
		{
			//Hitbox position.x + its width - rigidbod position to get xInvEntry
			xInvEntry = (b2.x + b2.w) - b1.x;
			//Hitbox position - Rigidbody.x + width to get xInvExit
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

		// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
		float xEntry,yEntry;
		float xExit,yExit;

		if(b1.vx == 0.0f)
		{
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / b1.vx;
			xExit = xInvExit / b1.vx;
		}

		if(b1.vy == 0.0f)
		{
			yEntry = -std::numeric_limits<float>::infinity();
			yExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / b1.vy;
			yExit = yInvExit / b1.vy;
		}
		// find the earliest/latest times of collision
		float entryTime = std::max<double>(xEntry,yEntry);
		float exitTime = std::min<double>(xExit,yExit);
		/*
		// Check the collision Horizontally
		// > Because the higher the more right, 0,0 top left
		// this means that rigid left side is to the right of hitbox right side
		if(topLeft.x > bottomRightH.x)
		continue;
		// > Because the higher the more right, 0,0 top left
		// this means that rigid right side is to the left side of hitbox
		else if(bottomRight.x < topLeftH.x)
		continue;
		//< Because the lower the higher, 0,0 top left
		//this means that Rigid below hitbox, Top part of rigid is below hitbox bottom part
		else if(topLeft.y > bottomRightH.y)
		continue;
		//< Because the lower the higher, 0,0 top left
		//this means that rigid is above HitBox, Bottom part of rigid is higher than top part of Hitbox
		else if(bottomRight.y  < topLeftH.y)
		continue;
		else
		{
		collided.push_back(hitboxes[i]);
		}
		//*/
		// if there was no collision
		double normalx,normaly = 0;
		if(entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
		{
			continue;
			/*
			normaly = 0.0f;
			return 1.0f;
			//*/
		}
		else // if there was a collision
		{
			// calculate normal of collided surface
			if(xEntry > yEntry)
			{
				if(xInvEntry < 0.0f)
				{
					normalx = 1.0f;
					normaly = 0.0f;
				}
				else
				{
					normalx = -1.0f;
					normaly = 0.0f;
				}
			}
			else
			{
				if(yInvEntry < 0.0f)
				{
					normalx = 0.0f;
					normaly = 1.0f;
				}
				else
				{
					normalx = 0.0f;
					normaly = -1.0f;
				}
			}

			//TODO: Remake this as a bubble sort, aka Only save the nearest hitbox
			collided.push_back(std::make_pair(hitboxes[i],entryTime));
			// return the time of collision
		}
	}
	HitboxComponent* a;
	double horse = 1;
	int index = -1;
	for(size_t i = 0; i < collided.size(); i++)
	{
		horse = collided[i].second;
		index = i;
		a = collided[i].first;
	}

	return horse;
	/*
	//HIGH: Move this to a function call
	for(size_t i = 0; i < collided.size(); i++)
	{
	for(size_t j = 0; j < collided[i]->collisionCall.size(); j++)
	{
	collided[i]->collisionCall[j]->onCollision(inMotion->attachedOn);
	}
	}
	//*/

	//return Vector2();
};