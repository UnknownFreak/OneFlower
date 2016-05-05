#include "Game.h"
#include <SFML\Window\Mouse.hpp>
#include <vector>
#include "Component/GameObject.h"
#include "Component/IBaseComponent.hpp"
#include "Component/HitboxComponent.hpp"
#include "Component/RigidComponent.hpp"
#include "Component/TransformComponent.hpp"
#include "Component/RenderComponent.h"
#include "Gfx.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "../Engine.hpp"
#include <math.h>

void Game::update()
{
	#pragma region oldcode
	/*
	for(size_t i = 0; i < motionPointers.size(); i++)
	{
		Physics::Movement movement = motionPointers[i];
		//->GetComponent<MovementComponent>();
		//HIGH: Learn the math, Been to long to remember
		if(movement)
		{
			//The combined force movement condensed into one vector
			Vector2 resultant;
			Vector2 position = movement->attachedOn->GetComponent<TransformComponent>()->position;
				//motionObjectPointers[i]->GetComponent<TransformComponent>()->position;
			
			Physics::BoundingBox box(0,0,0,0);
			Physics::Collider collided;

			//Combine all movement force
			for(size_t i = 0; i < movement->movementsQueue.size(); ++i)
				resultant += movement->movementsQueue[i].first;

			if(resultant.x || resultant.y)
			{
				if(HitboxComponent* hitbox = movement->attachedOn->GetComponent<HitboxComponent>())
					box = hitbox->bounding;
				else if(RigidComponent* rigid = movement->attachedOn->GetComponent<RigidComponent>())
					box = rigid->bounding;

				box.position += position;
				collided = Engine::Physics.collision(movement->attachedOn,box,resultant);

				if(collided.newton)
				{
					Engine::Window.debug.print(std::to_string(collided.newton),__LINE__,__FILE__);
				}
			}

			////Start Position of Object
			//Vector2 position = movement->attachedOn->GetComponent<TransformComponent>()->position;
			//
			////The movement direction 
			//Vector2 direction = movement->direction;
			////Currently velocity speed
			//double speed = movement->speed;
			/*
			//Stored force queue
			std::vector<std::pair<Vector2,double>> queue = movement->movementsQueue;
			
			if(queue.size() > 0)
			{

				Vector2 directionForce(direction.x*speed,direction.y*speed);
				Vector2 newForce;

				//HIGH: Remove this no need to save the different forces, only need one iteration
				std::vector<Vector2> forces;
				for(size_t i = 0; i < queue.size(); ++i)
					forces.push_back(Vector2(queue[i].first.x*queue[i].second,queue[i].first.y*queue[i].second));
				for(size_t i = 0; i < forces.size(); ++i)
					newForce += forces[i];

				double angle = atan2(newForce.x,newForce.y);
				Vector2 newDir(cos(angle),sin(angle));

				double newSpeed = newDir.x / newForce.x;

				position.x += newForce.x*Engine::time.deltaTime();
				position.y += newForce.y*Engine::time.deltaTime();
				movement->movementsQueue.clear();
			}
			else
			{
				position.x += direction.x*speed*Engine::time.deltaTime();
				position.y += direction.y*speed*Engine::time.deltaTime();

			}
			movement->attachedOn->GetComponent<TransformComponent>()->position = position;
			//*/
			/*
			if(movement->inMotion())
			{
				finalDirection = movement->direction;
					
				for(size_t i = 0; i < forces.size(); ++i)
				{
					finalDirection += forces[i].first;
					finalDirection.normalize();
				}
				position.x += finalDirection.x*movementSpeed*Engine::time.deltaTime();
				position.y += finalDirection.y*movementSpeed*Engine::time.deltaTime();
			}
			//*/
	//	}
	//}
	//*/
	#pragma endregion

		}
	}
	for (size_t i = 0; i < timedObjectPointers.size(); i++)
	{
		Component::Timer* timed = timedObjectPointers[i]->GetComponent<Component::Timer>();
		{
			timed->update();
			if (timed->canRemove())
				erase.push_back(timedObjectPointers[i]);
		}
	}
	for( size_t i = 0; i < erase.size(); i++)
	{
		erase[i]->destroy();
	}
	erase.clear();
	if (player)
	{
		Component::Combat* combat = player->GetComponent<Component::Combat>();
		if (combat->executingSkill)
		{
			combat->update();
		}
	}
	//LOW: Make my own Custom Focus
	if(Engine::Graphic.view.render.hasFocus())//Engine::Window.focus)
	{
		#pragma region Camera Temp
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			Engine::Graphic.view.camera.move(0,-10);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			Engine::Graphic.view.camera.move(-10,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Engine::Graphic.view.camera.move(0,10);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			Engine::Graphic.view.camera.move(10,0);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Engine::Graphic.view.camera.setCenter(0,0);
			Engine::Graphic.view.camera.setSize(800,600);
		}
		#pragma endregion

		Engine::Graphic.view.render.setView(Engine::Graphic.view.camera);
		Engine::GUI.updateMouseIcon();
		movementUpdate();
	}
	else
		while(ShowCursor(true) < 0);
}

void Game::movementUpdate()
{
	movementGrid();
	movementRigid();
	for(size_t i = 0; i < rigids.size(); i++)
		rigids.at(i)->movement.reset();

}

void Game::movementGrid()
{

	{

	}
}
void Game::movementRigid()
{
	for(size_t i = 0; i < rigids.size(); i++)
	{
		RigidComponent* rigid = rigids.at(i);
		Physics::Movement movement = rigid->movement;
		if(movement.speed)
		{
			movement.direction.normalize();
			Vector2 speed
				(
				movement.direction.x*movement.speed*Engine::time.deltaTime(),
				movement.direction.y*movement.speed*Engine::time.deltaTime()
				);

			TransformComponent* transform = rigid->attachedOn->GetComponent<TransformComponent>();
			std::vector<Physics::Collider> colliders;
			//Physics::Collider collider;
			Physics::BoundingBox boxMoving(transform->position,rigid->bounding.size + speed);
			Physics::BoundingBox boxDestination(transform->position,rigid->bounding.size + speed);

			for(size_t i = 0; i < hitboxes.size(); i++)
			{
				HitboxComponent* hitbox = hitboxes[i];
				Physics::Collider collider;
				Physics::BoundingBox boxStatic
					(hitbox->attachedOn->GetComponent<TransformComponent>()->position,hitbox->bounding.size);
				#pragma region Intersect
				if(boxDestination.intersect(boxStatic))
				{
					float xInvEntry,yInvEntry;
					float xInvExit,yInvExit;
					float xEntry,yEntry;
					float xExit,yExit;
#pragma region Distance
					if(speed.x > 0)
					{
						xInvEntry = boxStatic.position.x - (boxMoving.position.x + boxMoving.size.x);
						xInvExit = (boxStatic.position.x + boxStatic.size.x) - boxMoving.position.x;
					}
					else
					{
						xInvEntry = (boxStatic.position.x + boxStatic.size.x) - boxMoving.position.x;
						xInvExit = boxStatic.position.x - (boxMoving.position.x + boxMoving.size.x);
					}


					if(speed.y > 0.0f)
					{
						yInvEntry = boxStatic.position.y - (boxMoving.position.y + boxMoving.size.y);
						yInvExit = (boxStatic.position.y + boxStatic.size.y) - boxMoving.position.y;
					}
					else
					{
						yInvEntry = (boxStatic.position.y + boxStatic.size.y) - boxMoving.position.y;
						yInvExit = boxStatic.position.y - (boxMoving.position.y + boxMoving.size.y);
					}
#pragma endregion
#pragma region Time
					if(!speed.x)
					{
						xEntry = -std::numeric_limits<float>::infinity();
						xExit = std::numeric_limits<float>::infinity();
					}
					else
					{
						xEntry = xInvEntry / speed.x;
						xExit = xInvExit / speed.x;
					}

					if(!speed.y)
					{
						yEntry = -std::numeric_limits<float>::infinity();
						yExit = std::numeric_limits<float>::infinity();
					}
					else
					{
						yEntry = yInvEntry / speed.y;
						yExit = yInvExit / speed.y;
					}
					// find the earliest/latest times of collision
					float entryTime = std::max(xEntry,yEntry);
					float exitTime = std::min(xExit,yExit);


					//if(entryTime < collider.timeEnter)
					{
						collider.timeExit = exitTime;
						collider.timeEnter = entryTime;
						collider.contact = hitbox->attachedOn;
					}
					//else
					//	continue;


#pragma endregion
#pragma region Direction
					// calculate normal of collided surface
					if(xEntry > yEntry)
					{
						if(xInvEntry < 0.0f)
							collider.direction.x = 1;	//Physics::Collider::Hit::Right;
						else
							collider.direction.x = -1;	//Physics::Collider::Hit::Left;
					}
					else
					{
						if(yInvEntry < 0.0f)
							collider.direction.y = -1;		// = Physics::Collider::Hit::Bottom;
						else
							collider.direction.y = 1;		// = Physics::Collider::Hit::Top;
					}
#pragma endregion

				}
#pragma endregion
			}
			if(colliders.size())
			rigid->attachedOn->collision(colliders);
		}
	}
}