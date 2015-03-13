#include "GameView.hpp"
#include <Windows.h>
#include "Vector.h"
#include "Engine.hpp"
LRESULT CALLBACK WndProcGameView(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
GameView::GameView():size(800,600)
{
	#ifdef _DEBUG
	Vector2 size;
	LPCTSTR windowDefinedName;
	LPCTSTR titleBarDisplay;
	WNDCLASSEX wc;


	windowDefinedName = "GameViewWindow";
	titleBarDisplay = "Game View";


	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = DefWindowProc;						// This function is called by windows 
	wc.style = CS_HREDRAW | CS_VREDRAW;;							// Catch double-clicks 
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	wc.hIconSm = 0;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszMenuName = NULL;					// No menu 
	wc.cbClsExtra = 0;						// No extra bytes after the window class 
	wc.cbWndExtra = 0;						// structure or the window instance 
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	if(!RegisterClassEx(&wc))
		MessageBox(NULL,"Error Registering The GameViewWindow Class","Error",MB_OK | MB_ICONERROR);
	
	
	hWnd = CreateWindowEx(
		0,windowDefinedName,"Game View",WS_OVERLAPPEDWINDOW,
		GetSystemMetrics(SM_CXBORDER) + (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2),
		GetSystemMetrics(SM_CYCAPTION) + (GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYEDGE) * 2) + GetSystemMetrics(SM_CYMENU),
		800,600,
		Engine::Window.hWnd,NULL,Engine::Window.hInstance,NULL);
	if(hWnd)
		render.create(hWnd);
	else
		MessageBox(0,"Critical Error: Cannot create hWnd","GameViewDefiner.cpp",0);
	camera.reset(sf::FloatRect(0,0,800,600));

	#endif
}

#ifdef _DEBUG
GameView::~GameView()
{
	UnregisterClass("GameViewWindow",Engine::Window.hInstance);
}
#endif

LRESULT CALLBACK WndProcGameView(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_MOVE:
		{
			break;
		}
		default:
			break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
