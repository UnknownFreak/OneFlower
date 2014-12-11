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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		Engine::Graphic.camera.move(0,1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		Engine::Graphic.camera.move(0, 1);
		Engine::Graphic.moveBackground(0, 1,1.5);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		Engine::Graphic.camera.move(-1,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		Engine::Graphic.camera.move(-1, 0);
		Engine::Graphic.moveBackground(-1, 0, 1.5);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		Engine::Graphic.camera.move(0,-1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		Engine::Graphic.camera.move(0, -1);
		Engine::Graphic.moveBackground(0, -1, 1.5);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		Engine::Graphic.camera.move(1,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		Engine::Graphic.camera.move(1, 0);
		Engine::Graphic.moveBackground(1, 0, 1.5);
	}
	Engine::Window.View.setView(Engine::Graphic.camera);
}

void synchronizeComponents()
{

}
void mouseClick()
{
	
}