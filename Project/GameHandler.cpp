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
#include "Engine.hpp"
void Game::Update()
{
	//LOW: Make my own Custom Focus
	if(Engine::View.render.hasFocus())//Engine::Window.focus)
	{
		TransformComponent* tcp = player->GetComponent<TransformComponent>();
		tcp->move(pos, 2);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			pos.y -= 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//Engine::Graphic.camera.move(-10, 0);
			pos.x -= 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//Engine::Graphic.camera.move(0, -10);
			pos.y += 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//Engine::Graphic.camera.move(10, 0);
			pos.x += 2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			Engine::View.camera.move(0, 10);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			Engine::View.camera.move(-10, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Engine::View.camera.move(0, -10);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			Engine::View.camera.move(10, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Engine::View.camera.setCenter(0, 0);
			pos.x = 0;
			pos.y = 0;
		}
		Engine::View.render.setView(Engine::View.camera);
		Engine::GUI.updateMouseIcon();
	}
}

void synchronizeComponents()
{
}
void mouseClick()
{
}