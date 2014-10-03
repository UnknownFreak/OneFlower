#include <SFML/Graphics.hpp>
#include "CustomWindow.h"
#include "RenderHandler.h"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include "Game.h"
#include "LoadAndSave.hpp"
#include "Component\BaseComponent.hpp"
#include "Component\IBaseComponent.hpp"
#include <Windows.h>
#include "Component\HitboxComponent.hpp"
#include "Component\TransformComponent.hpp"
sf::RenderWindow* mainWindow;

EditorWindow editorWindow;
int windowMessage();
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPSTR lpCmnLine,int nShowCmd)
{
	editorWindow.hInstance = hInstance;
	windowMessage();
	return 0;
}
int windowMessage()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	//sf::RenderWindow eWindow(,);	//(sf::VideoMode(800, 600), "Editor!");
	mainWindow = &window;
	sf::Texture ab;
	GameObject a("Testiing Object Simon does not listen");
	a.AddComponent(new HitboxComponent());

	a.AddComponent(new RenderComponent());
	SetGame()->addGameObject(&a);


	sf::Sprite* sprite = &a.GetComponent<RenderComponent>()->sprite;
	sprite->setOrigin(0,1);
	a.GetComponent<TransformComponent>()->position.x = 100;
	MSG msg;
		ZeroMemory(&msg,sizeof(MSG));
		sf::Sprite bat;
		bat.setTexture(*SetGfx()->requestTexture("test.png"));
		bat.setOrigin(bat.getTextureRect().width / 2,bat.getTextureRect().height/2);
	while(window.isOpen())
	{
		sf::Event event;

		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				window.close();
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			while(window.pollEvent(event))
				if(event.type == sf::Event::Closed)
					window.close();

			window.clear();
			SetGame()->Update();
		//	SetGfx()->Draw();//Change this to const verseion aka Request
			window.draw(bat);
			window.display();
		}

	}
	return (int)msg.wParam;
}
	
EditorWindow* SetEditorWindow()
{
	return &editorWindow;
}

//Read Only
const sf::RenderWindow* RequestWindow()
{
	return mainWindow;
}

sf::RenderWindow* SetWindow()
{
	return mainWindow;
}	