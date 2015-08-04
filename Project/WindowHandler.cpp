#include <Windows.h>
#include <string>
#include "Engine.hpp"
#include "Component\GameObject.h"
#include "Component\HitboxComponent.hpp"
#include "Component\RenderComponent.h"
#include "Component\TransformComponent.hpp"
#include "Component\DialogComponent.hpp"
#include "Component\ProjectilePatternComponent.hpp"
#include "Component\EquipmentComponent.hpp"	
#include "Component\PlayerComponent.hpp"
#include "Time.hpp"
#include "WorldManagement.hpp"
#include "Component\RigidComponent.hpp"
int windowMessage();
void RunMain();
int test();
EngineWindow Engine::Window;
Gfx Engine::Graphic;
sf::Event Engine::event;
Game Engine::game;
Time Engine::time;
PhysicsEngine Engine::Physics;
InputHandler Engine::Input;
GraphicalUserInterface Engine::GUI;
WorldManagement Engine::World;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPSTR lpCmnLine,int nShowCmd)
{
	Engine::Window.hInstance = hInstance;
	!_DEBUG ? test() : windowMessage();
	return 0;
}

int windowMessage()
{
	Engine::World.loadZone(1);
	GameObject* go = new GameObject("player");
	//go->AddComponent<ProjectilePatternComponent>();
	go->AddComponent<RenderComponent>("testTarget.png");
	go->GetComponent<RenderComponent>()->setAnimation("anime2.png",32,32);
	go->AddComponent<RigidComponent>();
	go->GetComponent<TransformComponent>()->position.x = 300;
	go->AddComponent<PlayerComponent>();
	//go->AddComponent<EquipmentComponent>();
	sf::Color c(1,0,0,1);
	sf::Sprite sp = go->GetComponent<RenderComponent>()->sprite;
	//else
	//Engine::Graphic.insertShader(shader,"test.glsl");
	Engine::GUI.showHideGUI();
	Engine::game.addGameObject(go);
	Time time;
	MSG message;
	ZeroMemory(&message,sizeof(MSG));
	Engine::Graphic.view.render.setFramerateLimit(200);
	Engine::Graphic.rex.create(800,600);

	CreateWindowEx(
		0,"Button","Start/Pause",
		BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		EditorUI::GetLocalCoordinates(Engine::Window.hWnd).right - 128 - 16,EditorUI::GetLocalCoordinates(Engine::Window.hWnd).bottom - 256,
		128,64,
		Engine::Window.hWnd,
		(HMENU)27457,
		Engine::Window.hInstance,
		NULL
		);
	//Engine::Window.debug.print("Test",__LINE__,__FILE__);
	while(message.message != WM_QUIT)
	{
		while(PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{
			if(message.message == WM_KEYDOWN)
			{
				if(message.wParam == VK_ESCAPE)
					SetFocus(Engine::Window.hWnd);
				if (message.wParam == VK_DELETE)
				{
					Engine::World.RemoveGameObjectFromZone(Engine::Window.focus.gameObject);
					Engine::game.requestRemoveal(Engine::Window.focus.gameObject);
				}
				if(message.wParam == VK_OEM_PLUS)
					Engine::Input.mouse.deltaScrolls += 5;
				if(message.wParam == VK_OEM_MINUS)
					Engine::Input.mouse.deltaScrolls -= 5;
			}
			// If a message was waiting in the message queue, process it
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		while(Engine::Graphic.view.render.pollEvent(Engine::event))
		{
			if(Engine::event.type == sf::Event::Closed)
				Engine::Graphic.view.render.close();
			if(Engine::event.type == Engine::event.MouseWheelMoved)
				Engine::Input.mouse.deltaScrolls += Engine::event.mouseWheel.delta;
			/*
			std::cout << "alt:" << event.key.alt << std::endl;
			std::cout << "shift:" << event.key.shift << std::endl;
			std::cout << "system:" << event.key.system << std::endl;
			//*/				
		}

		Engine::Input.update();

		Engine::game.update();

		Engine::Physics.update();

		Engine::Graphic.Draw();

		Engine::GUI.Draw();

		Engine::Graphic.view.render.display();
		
		Engine::Window.update();

		//Fix this, By moving it somewhere else? and have it return a constant variable
		Engine::time.restartDelta();
		time.FPS();
	}
	return message.wParam;
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
	//	window.hasFocus() ? window.draw(text) : window.draw(text2);
		// update the window
		window.display();
	}
	return EXIT_SUCCESS;
}