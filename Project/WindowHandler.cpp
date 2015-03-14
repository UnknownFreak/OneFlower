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
void RunMain();
int test();
EngineWindow Engine::Window;
Gfx Engine::Graphic;
GameView Engine::View;
sf::Event Engine::event;
Game Engine::game;
Time Engine::time;
PhysicsEngine Engine::Physics;
Mouse Engine::mouse;
GraphicalUserInterface Engine::GUI;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPSTR lpCmnLine,int nShowCmd)
{
	Engine::Window.hInstance = hInstance;
	false ? test() : windowMessage();
	return 0;
}

int windowMessage()
{
	WorldManagement world;
	world.loadZone(1);
	GameObject* go = new GameObject("player");
	go->AddComponent<RenderComponent>("testTarget.png");
	Engine::game.player = go;
	Engine::game.addGameObject(go);
	Time time;
	MSG message;
	ZeroMemory(&message,sizeof(MSG));
	Engine::View.render.setFramerateLimit(200);

	#ifdef _DEBUG
	while(message.message != WM_QUIT)
	{
		while(PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{
			/*
			for(auto i = Engine::Window.focus.componentFieldGroup.begin(); i != Engine::Window.focus.componentFieldGroup.end(); ++i)
			{
				if(IsDialogMessage(i->second.hWnd,&message))
				{
					break;
				}
			}
			//*/

			if(message.message == WM_KEYDOWN)
			{
				if(message.wParam == VK_ESCAPE)
				{
					SetFocus(Engine::Window.hWnd);
				}
			}
			// If a message was waiting in the message queue, process it
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		{
			while(Engine::View.render.pollEvent(Engine::event))
			{
				if(Engine::View.render.hasFocus())
				{
					#pragma region Mouse
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
								if(hitbox || rig || rc)
								{
									sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::View.render);
									sf::Vector2f worldPos = Engine::View.render.mapPixelToCoords(pixelPos);

									rc = Engine::game.allGameObjectPointers.at(i)->GetComponent<RenderComponent>();
									ab = Engine::game.allGameObjectPointers.at(i);
									dialog = Engine::game.allGameObjectPointers.at(i)->GetComponent<DialogComponent>();
									if(dialog)
										dialog->show();

									int localStartX = (transform->position.x + (rc->sprite.getTextureRect().width / 2) * 1);
									int localStartY = (transform->position.y + (rc->sprite.getTextureRect().height / 2) * 1);
									int localEndX = (transform->position.x - (rc->sprite.getTextureRect().width / 2) * 1);
									int localEndY = (transform->position.y - (rc->sprite.getTextureRect().height / 2) * 1);

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
						#pragma endregion
						#pragma region Right
						else if(Engine::event.mouseButton.button == sf::Mouse::Button::Right)
						{
							sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::View.render);
							sf::Vector2f worldPos = Engine::View.render.mapPixelToCoords(pixelPos);
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

							HWND wnd = GetDlgItem(Engine::Window.hWnd,90562);
							HWND awnd = GetDlgItem(Engine::Window.hWnd,90572);

							SetWindowTextA(wnd,std::to_string((int)worldPos.x).c_str());
							SetWindowTextA(awnd,std::to_string((int)worldPos.y).c_str());
						}
#pragma endregion
					}
					#pragma endregion
				}
				if(Engine::event.type == sf::Event::Closed)
				{
					Engine::View.render.close();
				}
			}
			Engine::View.render.clear();
			Engine::game.Update();
			Engine::Physics.Update();
			Engine::Graphic.Draw();
			Engine::mouse.update();
			Engine::GUI.Draw();
			Engine::View.render.display();
			//Fix this, By moving it somewhere else? and have it return a constant variable
			Engine::time.delta.restart();
			time.FPS();
		}
	}
	return message.wParam;
#endif
}

int test()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800,600),"SFML window");
	// Load a sprite to display
	sf::Texture texture;
	if(!texture.loadFromFile("test.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	// Create a graphical text to display
	sf::Font font;
	if(!font.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;
	sf::Text text("Hello SFML",font,50);
	sf::Text text2("HellNoFucs",font,50);
	// Start the game loop
	while(window.isOpen())
	{
		// Process events
		sf::Event event;
		while(window.pollEvent(event))
		{
			// Close window: exit
			if(event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(sprite);
		// Draw the string
		window.hasFocus() ? window.draw(text) : window.draw(text2);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}