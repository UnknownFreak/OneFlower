#include <Windows.h>
#include <string>
#include "Engine.hpp"
#include "Component\GameObject.h"
#include "Component\HitboxComponent.hpp"
#include "Component\RenderComponent.h"
#include "Component\TransformComponent.hpp"
#include "Component\DialogComponent.hpp"
#include "Time.hpp"
#include "WorldManagement.hpp"
#include "Component\RigidComponent.hpp"
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
	//HIGH: Make it do TRY AND CATCH EMIL!
//	world.loadZone(1);
	sf::Texture ab;
	
	GameObject* a = new GameObject("TestiingObject");
	a->AddComponent<RigidComponent>();
	a->AddComponent(new RenderComponent(/*"Debug.png"*/));
	a->AddComponent<RenderComponent>("Debug.png");
	sf::Sprite* sprite = &a->GetComponent<RenderComponent>()->sprite;
	a->tag = "Rigid";
	float x = sprite->getTextureRect().width;
	float y = sprite->getTextureRect().height;
	sprite->setOrigin(x / 2,y / 2);
	a->GetComponent<TransformComponent>()->position.x = 300;
	a->GetComponent<TransformComponent>()->position.y = 400;
	Engine::game.addGameObject(a);


	GameObject* b = new GameObject("TestiingObject");
	b->AddComponent<HitboxComponent>();
	b->AddComponent(new RenderComponent(/*"Debug.png"*/));
	b->AddComponent<RenderComponent>("Debug.png");
	sf::Sprite* spriteB = &b->GetComponent<RenderComponent>()->sprite;

	float x2 = spriteB->getTextureRect().width;
	float y2 = spriteB->getTextureRect().height;
	spriteB->setOrigin(x2 / 2,y2 / 2);
	b->GetComponent<TransformComponent>()->position.x = 100;
	b->GetComponent<TransformComponent>()->position.y = 200;
	Engine::game.addGameObject(b);
	//*/	
	sf::Vector2f vec(10,10);
	Time time;
	MSG Message;
	ZeroMemory(&Message,sizeof(MSG));
	Engine::Window.View.setFramerateLimit(200);
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
						#pragma region Left
						if(Engine::event.mouseButton.button == sf::Mouse::Button::Left)
						{
							int top = 0;
							for(int i = 0; i < Engine::game.allGameObjectPointers.size(); i++)
							{
								RenderComponent* rc = 0;
								GameObject* ab = 0;
								HitboxComponent* hitbox = 0;
								TransformComponent* transform = 0;
								DialogComponent* dialog = 0;
								RigidComponent* rig = 0;
								hitbox = Engine::game.allGameObjectPointers.at(i)->GetComponent<HitboxComponent>();
								transform = Engine::game.allGameObjectPointers.at(i)->GetComponent<TransformComponent>();
								rig = Engine::game.allGameObjectPointers.at(i)->GetComponent<RigidComponent>();
								if(hitbox || rig)
								{
									sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::Window.View);
									sf::Vector2f worldPos = Engine::Window.View.mapPixelToCoords(pixelPos);

									rc = Engine::game.allGameObjectPointers.at(i)->GetComponent<RenderComponent>();
									ab = Engine::game.allGameObjectPointers.at(i);
									dialog = Engine::game.allGameObjectPointers.at(i)->GetComponent<DialogComponent>();
									if (dialog)
										dialog->show();

									int localStartX = (transform->position.x + (rc->sprite.getTextureRect().width / 2) * 1);
									int localStartY = (transform->position.y + (rc->sprite.getTextureRect().height / 2) *1);
									int localEndX = (transform->position.x - (rc->sprite.getTextureRect().width / 2) *1);
									int localEndY = (transform->position.y - (rc->sprite.getTextureRect().height / 2) *1);

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
								std::cout<< "\nSelected Object: " << theChoosenOne->name << std::endl << "Game Object Position: " << Engine::Graphic.selectedDrawList[top]->GetComponent<TransformComponent>()->position.x << " " << Engine::Graphic.selectedDrawList[top]->GetComponent<TransformComponent>()->position.y;
								Engine::Window.setGameObject(theChoosenOne);
								Engine::Graphic.selectedDrawList.clear();
							}
						}
					#pragma endregion
						else if(Engine::event.mouseButton.button == sf::Mouse::Button::Right)
						{
							sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::Window.View);
							sf::Vector2f worldPos = Engine::Window.View.mapPixelToCoords(pixelPos);
							/*
							sf::Vector2f dir = testa.sprite.getPosition() - worldPos;
							dir = dir / sqrt(dir.x * dir.x + dir.y * dir.y) ;
							
							/*
							sf::Vector2f shit(a->GetComponent<TransformComponent>()->position.x,a->GetComponent<TransformComponent>()->position.y);

							vec = worldPos - shit;
							Vector2 asia(vec.x,vec.y);

							asia.normalize();
							sf::Vector2f shit2(asia.dx,asia.dy);

							vec.x = shit2.x;
							vec.y = shit2.y;
							//*/
							vec = worldPos;

							HWND wnd = GetDlgItem(Engine::Window.hWnd,90562);
							HWND awnd = GetDlgItem(Engine::Window.hWnd,90572);

							SetWindowText(wnd,std::to_string((int)worldPos.x).c_str());
							SetWindowText(awnd,std::to_string((int)worldPos.y).c_str());
						}
					}

				}
				#pragma endregion 
				else if(Engine::event.type == sf::Event::GainedFocus)
					Engine::Window.focus = true;
				else if(Engine::event.type == sf::Event::LostFocus)
					Engine::Window.focus = false;
			}
			Engine::Window.View.clear();
			Engine::game.Update();
			a->GetComponent<TransformComponent>()->move(vec.x,vec.y,5);
			Engine::Physics.Update();
			Engine::Graphic.Draw();		

			Engine::Window.View.display();

			Engine::time.delta.restart();
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