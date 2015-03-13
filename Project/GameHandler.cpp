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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			Engine::View.camera.move(0,10);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			Engine::View.camera.move(-10,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			Engine::View.camera.move(0,-10);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			Engine::View.camera.move(10,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			Engine::View.camera.setCenter(0,0);
		Engine::View.render.setView(Engine::View.camera);
	}
}

void synchronizeComponents()
{

}
void mouseClick()
{
	
}