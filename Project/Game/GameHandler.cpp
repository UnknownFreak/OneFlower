#include "Game.h"
#include <SFML\Window\Mouse.hpp>
#include <vector>
#include "Component\GameObject.h"
#include "Component\IBaseComponent.hpp"
#include "Component\HitboxComponent.hpp"
#include "Component\TransformComponent.hpp"
#include "Component\RenderComponent.h"
#include "Gfx.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include "../Engine.hpp"
#include "Component\MovementComponent.hpp"
void Game::update()
{

	for(size_t i = 0; i < motionObjectPointers.size(); i++)
	{
		MovementComponent* movement = motionObjectPointers[i]->GetComponent<MovementComponent>();
		//HIGH: Learn the math, Been to long to remember
		if(movement)
		{
			Vector2 position = motionObjectPointers[i]->GetComponent<TransformComponent>()->position;
			Vector2 finalDirection(0,0);
			std::vector<std::pair<Vector2,double>> forces = movement->forces;
			double movementSpeed = 0;

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
			pos.x = 0;
			pos.y = 0;
		}
		Engine::Graphic.view.render.setView(Engine::Graphic.view.camera);
		Engine::GUI.updateMouseIcon();
	}
	else
		while(ShowCursor(true) < 0);
}
