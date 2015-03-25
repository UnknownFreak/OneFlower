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
	!_DEBUG ? test() : windowMessage();
	return 0;
}

int windowMessage()
{
	WorldManagement world;
	world.loadZone(1);
	GameObject* go = new GameObject("player");
	go->AddComponent<RenderComponent>("testTarget.png");

	Engine::game.addGameObject(go);
	Time time;
	MSG message;
	ZeroMemory(&message,sizeof(MSG));
	Engine::View.render.setFramerateLimit(200);
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
				if(message.wParam ==VK_DELETE)
					Engine::game.requestRemoveal(Engine::Window.focus.gameObject);
			}
			// If a message was waiting in the message queue, process it
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		while(Engine::View.render.pollEvent(Engine::event))
		{
			if(Engine::event.type == sf::Event::Closed)
			{
				Engine::View.render.close();
			}
			if(Engine::event.type == Engine::event.MouseWheelMoved)
			{
				Engine::mouse.deltaScrolls += Engine::event.mouseWheel.delta;
			}
		}
		Engine::View.render.clear();
		Engine::game.Update();
		Engine::Physics.Update();
		Engine::Graphic.Draw();
		Engine::mouse.update();
		Engine::GUI.Draw();
		Engine::View.render.display();
		if(Engine::View.render.hasFocus())
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
		window.hasFocus() ? window.draw(text) : window.draw(text2);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}