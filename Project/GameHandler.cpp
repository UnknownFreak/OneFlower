#include "Game.h"
#include <SFML\Window\Mouse.hpp>
#include <vector>
#include "Component\GameObject.h";
#include "Component\IBaseComponent.hpp"
#include "CustomWindow.h"
#include "Component\HitboxComponent.hpp"
#include "Component\TransformComponent.hpp"
#include "Component\RenderComponent.h"
#include "Gfx.h"
Game gameManager;
void Game::Update()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
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



				if((mouse.x <= (transform->position.x + (rc->sprite.getTextureRect().width / 2) * hitbox->size.x) &&
					mouse.x >= (transform->position.x - (rc->sprite.getTextureRect().width / 2) * hitbox->size.x)
					))
				{
					if((mouse.y <= (transform->position.y + (rc->sprite.getTextureRect().height / 2) * hitbox->size.y) &&
						mouse.y >= (transform->position.y - (rc->sprite.getTextureRect().height / 2) * hitbox->size.y)
						))
						{
						SetGfx()->selectedDrawList.clear();
						SetGfx()->selectedDrawList.push_back(ab); 

					}
				}
			}
		}
	}
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