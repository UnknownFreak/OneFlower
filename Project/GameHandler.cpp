#include "Game.h"
#include <SFML\Window\Mouse.hpp>
#include <vector>
#include "Component\GameObject.h"
#include "Component\IBaseComponent.hpp"
#include "CustomWindow.h"
#include "Component\HitboxComponent.hpp"
#include "Component\TransformComponent.hpp"
#include "Component\RenderComponent.h"
#include "Gfx.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include "Window.h"
#include "Engine.hpp"
void Game::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		SetGfx()->camera.move(0, 1);
		SetGfx()->moveBackground(0, 1,1.5);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		SetGfx()->camera.move(-1, 0);
		SetGfx()->moveBackground(-1, 0, 1.5);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		SetGfx()->camera.move(0, -1);
		SetGfx()->moveBackground(0, -1, 1.5);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		SetGfx()->camera.move(1, 0);
		SetGfx()->moveBackground(1, 0, 1.5);
	}

	SetWindow()->setView(SetGfx()->camera);
}

void synchronizeComponents()
{

}
void mouseClick()
{
	
}

