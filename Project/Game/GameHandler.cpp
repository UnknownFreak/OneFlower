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
#include "Component/MovementComponent.hpp"
#include <math.h>
#define PI 3.14159265

void Game::update()
{
	for(size_t i = 0; i < motionObjectPointers.size(); i++)
	{
		MovementComponent* movement = motionObjectPointers[i]->GetComponent<MovementComponent>();
		//HIGH: Learn the math, Been to long to remember
#ifdef _DEBUG
		if(movement)
#endif
		{
			Vector2 position = motionObjectPointers[i]->GetComponent<TransformComponent>()->position;
			Vector2 resultant;

			if(RigidComponent* rigid = motionObjectPointers[i]->GetComponent<RigidComponent>())
			{
				for(size_t i = 0; i < movement->movementsQueue.size(); ++i)
					resultant += movement->movementsQueue[i].first;

					
			}
			else if(HitboxComponent* hitbox = motionObjectPointers[i]->GetComponent<HitboxComponent>())
			{

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
		}
	}
	//LOW: Make my own Custom Focus
	if(Engine::Graphic.view.render.hasFocus())//Engine::Window.focus)
	{
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
//			pos.x = 0;
//			pos.y = 0;
		}
		Engine::Graphic.view.render.setView(Engine::Graphic.view.camera);
		Engine::GUI.updateMouseIcon();
	}
	else
		while(ShowCursor(true) < 0);
}