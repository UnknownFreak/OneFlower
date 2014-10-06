#include <SFML/Graphics.hpp>
#include "CustomWindow.h"
#include "Gfx.h"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include "Game.h"
#include "LoadAndSave.hpp"
#include "Component\BaseComponent.hpp"
#include "Component\IBaseComponent.hpp"
#include <Windows.h>
#include "Component\HitboxComponent.hpp"
#include "Component\TransformComponent.hpp"
#include "Component\InputComponent.h"
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "Time.hpp"
void RedirectIOToConsole();
 
sf::RenderWindow* mainWindow;

EditorWindow editorWindow;
int windowMessage();
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPSTR lpCmnLine,int nShowCmd)
{
	RedirectIOToConsole();
	editorWindow.hInstance = hInstance;
	windowMessage();
	return 0;
}
sf::Event event;
int windowMessage()
{

	sf::RenderWindow window(sf::VideoMode(800,600),"SFML works!");
	//Do not remove
	//sf::RenderWindow eWindow(,);	//(sf::VideoMode(800, 600), "Editor!");
	mainWindow = &window;
	window.setVerticalSyncEnabled(false);


	sf::Texture ab;
	GameObject a("TestiingObject");
	a.AddComponent(new HitboxComponent());
	a.AddComponent(new RenderComponent());
	a.AddComponent(new InputComponent());
	SetGame()->addGameObject(&a);
	
	sf::Sprite* sprite = &a.GetComponent<RenderComponent>()->sprite;
	sprite->setOrigin(0,1);
	a.GetComponent<TransformComponent>()->position.x = 100;
	
	Time time;
	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));
	while(window.isOpen())
	{
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
			a.GetComponent<InputComponent>()->moveSprite(1,1,1);
			SetGame()->Update();
			SetGfx()->Draw();//Change this to const verseion aka Request
			window.display();
			time.FPS();
		
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
sf::Event* RequestEvent()
{
	return &event;
};



































// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

void RedirectIOToConsole()
{
	using namespace std;

	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

	fp = _fdopen(hConHandle,"w");

	*stdout = *fp;

	setvbuf(stdout,NULL,_IONBF,0);

	// redirect unbuffered STDIN to the console

	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

	fp = _fdopen(hConHandle,"r");
	*stdin = *fp;
	setvbuf(stdin,NULL,_IONBF,0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

	fp = _fdopen(hConHandle,"w");

	*stderr = *fp;

	setvbuf(stderr,NULL,_IONBF,0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	ios::sync_with_stdio();
}
//*/
