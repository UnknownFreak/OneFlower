#ifndef _EDITOR_
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
#include "Game\Component\CombatComponenet.hpp"
#include "Game\Component\RigidComponent.hpp"
#include "Game\Logic\Time\Time.hpp"
#include "Game\World\WorldManagement.hpp"
#include "Game\LoadAndSave\LoadAndSave.hpp"
int windowMessage();
void RunMain();
int test();
Gfx Engine::Graphic;
sf::Event Engine::event;
Game Engine::game;
Time Engine::time;
PhysicsEngine Engine::Physics;
InputHandler Engine::Input;
GUI::GraphicalUserInterface Engine::GUI;
WorldManagement Engine::World;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPSTR lpCmnLine,int nShowCmd)
{
	//Engine::Window.hInstance = hInstance;
	!_DEBUG ? test() : windowMessage();
	return 0;
}

int windowMessage()
{
	//testSave();
	//Loads the mods required for the "editor", not required for release mode.
	Engine::World.loadMod("OneFlower.main");
	Engine::World.loadZone("OneFlower.main",1);
	GameObject* go = new GameObject("player");
	//go->AddComponent<ProjectilePatternComponent>();
	go->AddComponent<RenderComponent>("testTarget.png");
	go->GetComponent<RenderComponent>()->setAnimation("anime2.png",32,32);
	go->AddComponent<RigidComponent>();
	go->GetComponent<TransformComponent>()->position.x = 300;
	go->AddComponent<PlayerComponent>();
	go->AddComponent<EquipmentComponent>();
	go->AddComponent<Component::Combat>();
	sf::Color c(1,0,0,1);
	sf::Sprite sp = go->GetComponent<RenderComponent>()->sprite;
	Engine::game.player = go;
	//else
	//Engine::Graphic.insertShader(shader,"test.glsl");
	Engine::GUI.showHideGUI();
	Engine::game.addGameObject(go);
	Time time;
	Engine::Graphic.view.render.setFramerateLimit(200);
	Engine::Graphic.rex.create(800,600);
	bool running = true;
	//Engine::Window.debug.print("Test",__LINE__,__FILE__);
	while(running)
	{
		while(Engine::Graphic.view.render.pollEvent(Engine::event))
		{
			if (Engine::event.type == sf::Event::Closed)
			{
				Engine::Graphic.view.render.close();
				running = false;
			}
			if(Engine::event.type == Engine::event.MouseWheelMoved)
				Engine::Input.mouse.deltaScrolls += Engine::event.mouseWheel.delta;
			/*
			std::cout << "alt:" << event.key.alt << std::endl;
			std::cout << "shift:" << event.key.shift << std::endl;
			std::cout << "system:" << event.key.system << std::endl;
			//*/
		}
		if (Engine::World.getIsLoading())
		{
			Engine::World.loadSome();
			Engine::World.drawLoadingScreen();
		}
		else
		{
		Engine::Input.update();

		Engine::game.update();

		Engine::Physics.update();

		Engine::Graphic.Draw();

		Engine::GUI.Draw();

		Engine::Graphic.view.render.display();
		//LOW: Fix this, By moving it somewhere else? and have it return a constant variable
		Engine::time.restartDelta();
		time.FPS();
		}
	}
	return 1;
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
#endif