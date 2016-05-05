#include <Windows.h>
#include <string>
#include "Engine.hpp"
#include "Game\Component\GameObject.h"
#include "Game\Component\HitboxComponent.hpp"
#include "Game\Component\RenderComponent.h"
#include "Game\Component\TransformComponent.hpp"
#include "Game\Component\DialogComponent.hpp"
#include "Game\Component\ProjectilePatternComponent.hpp"
#include "Game\Component\EquipmentComponent.hpp"
#include "Game\Component\PlayerComponent.hpp"
#include "Game\Component\RigidComponent.hpp"
#include "Game\Logic\Time\Time.hpp"
#include "Game\World\WorldManagement.hpp"
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
void update();
int windowMessage()
{
#ifdef _DEBUG
	Engine::World.loadZone(1);
	Engine::game.player = new GameObject();
	GameObject* go = Engine::game.player;
	//go->AddComponent<ProjectilePatternComponent>();
	go->AddComponent<RenderComponent>("testTarget.png");
	go->GetComponent<RenderComponent>()->setAnimation("anime2.png",32,32);
	go->AddComponent<RigidComponent>();
	go->GetComponent<TransformComponent>()->position.x = 300;
	go->AddComponent<PlayerComponent>();
	go->AddComponent<EquipmentComponent>();
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

	while(message.message != WM_QUIT)
	{
		while(PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{
			if(message.message == WM_KEYDOWN)
			{
				if(message.wParam == VK_ESCAPE)
					SetFocus(Engine::Window.hWnd);
				if(message.wParam == VK_DELETE)
				{
					Engine::World.RemoveGameObjectFromZone(Engine::Window.focus.gameObject);
					Engine::game.requestRemoveal(Engine::Window.focus.gameObject);
				}
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
			
		}
		update();
		//*/
	}
	return message.wParam;
#endif
}



void update()
{
	Engine::time.elapsed += Engine::time.clock.restart();

	while(Engine::time.elapsed >= Engine::time.update_ms)
	{
		Engine::Input.update();
		//Engine::Physics.update();
		Engine::game.update();

		Engine::time.elapsed -= Engine::time.update_ms;
	}

	Engine::Graphic.draw();
	Engine::GUI.draw();
	Engine::Graphic.view.render.display();



	Engine::Window.update();

}






int test()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800,600),"SFML window");
	// Load a sprite to display
	sf::Texture texture;
	if(!texture.loadFromFile("Texture/test.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	// Create a graphical text to display
	sf::Font font;
	if(!font.loadFromFile("Font/arial.ttf"))
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
		// draw the sprite
		window.draw(sprite);
		// draw the string
		window.hasFocus() ? window.draw(text) : window.draw(text2);
		// update the window
		window.display();
	}
	return EXIT_SUCCESS;
}