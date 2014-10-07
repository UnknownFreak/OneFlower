#include <SFML/Graphics.hpp>
#include "Gfx.h"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include "Game.h"
#include "LoadAndSave.hpp"
#include "Component\BaseComponent.hpp"
#include "Component\IBaseComponent.hpp"
#include "Component\HitboxComponent.hpp"
#include "Component\TransformComponent.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "Time.hpp"
#include "Engine.hpp"
 
int main()
{


	sf::Texture ab;
	GameObject a("TestiingObject");
	a.AddComponent(new HitboxComponent());
	a.AddComponent(new RenderComponent());


	sf::Sprite* sprite = &a.GetComponent<RenderComponent>()->sprite;

	float x = sprite->getTextureRect().width;
	float y = sprite->getTextureRect().height;
	sprite->setOrigin(x/2,y/2);
	a.GetComponent<TransformComponent>()->position.x = 10;

	Engine::game.addGameObject(&a);

	Time time;
	while(Engine::Window.isOpen())
	{
		while(Engine::Window.pollEvent(Engine::event))
		{
			if(Engine::event.type == sf::Event::Closed)
			{
				Engine::Window.close();
			}
			#pragma region Mouse
			if(true)
			{
				if(Engine::event.type == Engine::event.MouseButtonReleased)
				{
					if(Engine::event.mouseButton.button == sf::Mouse::Button::Left)
					{
						int top = 0;

						for(int i = 0; i < Engine::game.allGameObjectPointers.size(); i++)
						{
							RenderComponent* rc = 0;
							GameObject* ab = 0;
							HitboxComponent* hitbox = 0;
							TransformComponent* transform = 0;
							hitbox = Engine::game.allGameObjectPointers.at(i)->GetComponent<HitboxComponent>();
							transform = Engine::game.allGameObjectPointers.at(i)->GetComponent<TransformComponent>();
							if(hitbox)
							{
								sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::Window);
								sf::Vector2f worldPos = Engine::Window.mapPixelToCoords(pixelPos);

								rc = Engine::game.allGameObjectPointers.at(i)->GetComponent<RenderComponent>();
								ab = Engine::game.allGameObjectPointers.at(i);

								int localStartX = (transform->position.x + (rc->sprite.getTextureRect().width / 2) * hitbox->size.x);
								int localStartY = (transform->position.y + (rc->sprite.getTextureRect().height / 2) * hitbox->size.y);
								int localEndX = (transform->position.x - (rc->sprite.getTextureRect().width / 2) * hitbox->size.x);
								int localEndY = (transform->position.y - (rc->sprite.getTextureRect().height / 2) * hitbox->size.y);

								if(worldPos.x <= localStartX && worldPos.x >= localEndX)
								if(worldPos.y <= localStartY && worldPos.y >= localEndY)
									SetGfx()->selectedDrawList.push_back(ab);
							}
						}

						if(SetGfx()->selectedDrawList.size() > 0)
						{
							for(size_t i = 0; i < SetGfx()->selectedDrawList.size(); i++)
							if(SetGfx()->selectedDrawList[i]->ReadComponent<RenderComponent>()->renderlayer > SetGfx()->selectedDrawList[top]->ReadComponent<RenderComponent>()->renderlayer)
								top = i;
							std::cout << "\nSelected Object: " << SetGfx()->selectedDrawList[top]->name << std::endl << "Game Object Position: " << SetGfx()->selectedDrawList[top]->GetComponent<TransformComponent>()->position.x << " " << SetGfx()->selectedDrawList[top]->GetComponent<TransformComponent>()->position.y;
							SetGfx()->selectedDrawList.clear();
						}
					}
				}
			}
			#pragma endregion 
		}
		Engine::Window.clear();
		Engine::game.Update();
		SetGfx()->Draw();//Change this to const verseion aka Request
		Engine::Window.display();
		time.FPS();
	}
	return 0;
}
