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
Game gameManager;
void Game::Update()
{

	#pragma region Mouse
	if(true)
	{
		//if(
		for(int i = 0; i < allGameObjectPointers.size(); i++)
		if(RequestEvent()->MouseButtonReleased == sf::Mouse::Left)

		{
			for(int i = 0; i < allGameObjectPointers.size(); i++)
			{
				HitboxComponent* hitbox;
				TransformComponent* transform;
				hitbox = allGameObjectPointers.at(i)->GetComponent<HitboxComponent>();
				transform = allGameObjectPointers.at(i)->GetComponent<TransformComponent>();
				if(hitbox)
				{
					Vector2<int> mouse;
					mouse.x = sf::Mouse::getPosition(*RequestWindow()).x;
					mouse.y = sf::Mouse::getPosition(*RequestWindow()).y;
					RenderComponent* rc = allGameObjectPointers.at(i)->GetComponent<RenderComponent>();
					GameObject* ab = allGameObjectPointers.at(i);

					int localStartX = (transform->position.x + (rc->sprite.getTextureRect().width / 2) * hitbox->size.x);
					int localStartY = (transform->position.y + (rc->sprite.getTextureRect().height / 2) * hitbox->size.y);
					int localEndX = (transform->position.x - (rc->sprite.getTextureRect().width / 2) * hitbox->size.x);
					int localEndY = (transform->position.y - (rc->sprite.getTextureRect().height / 2) * hitbox->size.y);

					if(mouse.x <= localStartX && mouse.x >= localEndX)
					{
						SetGfx()->selectedDrawList.clear();
						SetGfx()->selectedDrawList.push_back(ab);
					//	std::cout << "\nMouse Click: " << ab->name;
						if(mouse.y <= localStartY && mouse.y >= localEndY)
						{
							SetGfx()->selectedDrawList.clear();
							SetGfx()->selectedDrawList.push_back(ab);
							std::cout << "\nMouse Click: " << ab->name;
						}
					}
				}
			}
		}
	}
	#pragma endregion 
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		SetGfx()->camera.move(0,10);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		SetGfx()->camera.move(-10,0);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		SetGfx()->camera.move(0,-10);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		SetGfx()->camera.move(10,0);

	SetWindow()->setView(SetGfx()->camera);
}

void synchronizeComponents()
{

}
void mouseClick()
{
	
}










const Game* RequestGame()
{
	return &gameManager;
}
Game* SetGame()
{
	return &gameManager;
}