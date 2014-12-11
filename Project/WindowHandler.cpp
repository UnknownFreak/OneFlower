#include <Windows.h>
#include <string>
#include "Engine.hpp"
#include "Component\GameObject.h"
#include "Component\HitboxComponent.hpp"
#include "Component\RenderComponent.h"
#include "Component\TransformComponent.hpp"
#include "Time.hpp"
#include "WorldManagement.hpp"
//#include "LoadAndSave.hpp"

#include <SFML\Audio.hpp>
//#include "vld.h"
int windowMessage();

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPSTR lpCmnLine,int nShowCmd)
{
	
	Engine::Window.hInstance = hInstance;
	windowMessage();
	return 0;
}
int windowMessage()
{
	//sf::SoundBuffer buf;
	//buf.loadFromFile("test.wav");
	//testSave();
	WorldManagement world;
	world.loadZone(1);
	sf::Texture ab;
		
	/*
	GameObject* a = new GameObject("TestiingObject");
	a->AddComponent(new HitboxComponent());
	a->AddComponent(new RenderComponent());
	sf::Sprite* sprite = &a->GetComponent<RenderComponent>()->sprite;

	float x = sprite->getTextureRect().width;
	float y = sprite->getTextureRect().height;
	sprite->setOrigin(x / 2,y / 2);
	a->GetComponent<TransformComponent>()->position.x = 10;
	
	Engine::game.addGameObject(a);
	//*/
	Time time;
	MSG Message;
	ZeroMemory(&Message,sizeof(MSG));
	while(Message.message != WM_QUIT)
	{
		while(PeekMessage(&Message,NULL,0,0,PM_REMOVE))
		{
			if(Message.message == WM_KEYDOWN)
			{
				if(Message.wParam == VK_ESCAPE)
				{
					SetFocus(Engine::Window.hWnd);
				}
			}
			// If a message was waiting in the message queue, process it
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		//else
		{
			while(Engine::Window.View.pollEvent(Engine::event))
			{
				if(Engine::event.type == sf::Event::Closed)
				{
					Engine::Window.View.close();
				}
				#pragma region Mouse
				else if(true)
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
									sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::Window.View);
									sf::Vector2f worldPos = Engine::Window.View.mapPixelToCoords(pixelPos);

									rc = Engine::game.allGameObjectPointers.at(i)->GetComponent<RenderComponent>();
									ab = Engine::game.allGameObjectPointers.at(i);

									int localStartX = (transform->position.x + (rc->sprite.getTextureRect().width / 2) * hitbox->size.x);
									int localStartY = (transform->position.y + (rc->sprite.getTextureRect().height / 2) * hitbox->size.y);
									int localEndX = (transform->position.x - (rc->sprite.getTextureRect().width / 2) * hitbox->size.x);
									int localEndY = (transform->position.y - (rc->sprite.getTextureRect().height / 2) * hitbox->size.y);

									if(worldPos.x <= localStartX && worldPos.x >= localEndX)
									if(worldPos.y <= localStartY && worldPos.y >= localEndY)
										Engine::Graphic.selectedDrawList.push_back(ab);
								}
							}

							if(Engine::Graphic.selectedDrawList.size() > 0)
							{
								for(size_t i = 0; i < Engine::Graphic.selectedDrawList.size(); i++)
								{
									if(Engine::Graphic.selectedDrawList[i]->ReadComponent<RenderComponent>()->renderlayer > Engine::Graphic.selectedDrawList[top]->ReadComponent<RenderComponent>()->renderlayer)
									{
										top = i;
									}
								}
								GameObject* theChoosenOne = Engine::Graphic.selectedDrawList[top];
								std::cout << "\nSelected Object: " << theChoosenOne->name << std::endl << "Game Object Position: " << Engine::Graphic.selectedDrawList[top]->GetComponent<TransformComponent>()->position.x << " " << Engine::Graphic.selectedDrawList[top]->GetComponent<TransformComponent>()->position.y;
								Engine::Window.setGameObject(theChoosenOne);
								Engine::Graphic.selectedDrawList.clear();
							}
						}
					}
				}
				#pragma endregion 
			}
			Engine::Window.View.clear();
			Engine::game.Update();
			Engine::Graphic.Draw();
			Engine::Window.View.display();
			time.FPS();
		}
	}
	/*
	if(!true)
	{
		MSG msg;
		ZeroMemory(&msg,sizeof(MSG));
		while(GetMessage(&msg,NULL,0,0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if(msg.message == WM_QUIT)
				{
					Engine::Window.View.close();
					break;
				}
			}
			else
			{
			
			}
		}
	}
	//*/
	return Message.wParam;
}