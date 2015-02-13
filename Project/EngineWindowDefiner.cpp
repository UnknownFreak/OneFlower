 #if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#include "Resource.h"
#include "EngineWindow.hpp"
#include "Engine.hpp"
#include "Vector.h"
#include "EditorUI\UIAddon.hpp"
#include <vector>
#define SHOW_COMMAND_ID 501 
#define SET_NULL_FOCUS_ID 503

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
EngineWindow::EngineWindow():size(1366,768), viewPosition(0,0)
{
	windowDefinedName = "EditorWindow";
	titleBarDisplay = "Editor Window";

	//The First Windows structure 
	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = WndProc;						// This function is called by windows 
	wc.style = CS_DBLCLKS;							// Catch double-clicks 
	wc.cbSize = sizeof (WNDCLASSEX);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(MENU_ICON));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(MENU_ICON),IMAGE_ICON,16,16,0);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszMenuName = MAKEINTRESOURCE(MENU_ID);;							// No menu 
	wc.cbClsExtra = 0;								// No extra bytes after the window class 
	wc.cbWndExtra = 0;								// structure or the window instance 
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);;
	
	
	if(!RegisterClassEx(&wc))
		MessageBox(NULL,"Error Registering The Window Class","Error",MB_OK | MB_ICONERROR);
	hWnd = CreateWindowEx
		(
		0,							// Extended possibilites for variation 
		windowDefinedName,			// Classname 
		titleBarDisplay,			// Title Text
		WS_OVERLAPPEDWINDOW,		// default window 
		CW_USEDEFAULT,				// Windows decides the position 
		CW_USEDEFAULT,				// where the window ends up on the screen 
		size.x,						// The programs width EditorUI::addTextbox
		size.y,						// and height in pixels 
		NULL,						// The window is a child-window to desktop 
		NULL,						// No menu
		hInstance,					// Program Instance handler
		NULL						// No Window Creation data 
		//this							
		);
	viewport = CreateWindow(windowDefinedName,NULL,WS_CHILD | WS_VISIBLE | WS_BORDER,viewPosition.x,viewPosition.y,800,600,hWnd,NULL,hInstance,NULL);
	View.create(viewport);
	HWND b = CreateWindowEx(0,"Button","Show CMD",BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,EditorUI::GetLocalCoordinates(viewport).right,EditorUI::GetLocalCoordinates(viewport).top,128,32,hWnd,(HMENU)SHOW_COMMAND_ID,Engine::Window.hInstance,NULL);
	HWND c = EditorUI::addLabel(hWnd,"FPS:",EditorUI::GetLocalCoordinates(b).left,EditorUI::GetLocalCoordinates(b).bottom,32,32,9002);
	HWND d = EditorUI::addLabel(hWnd,"0",EditorUI::GetLocalCoordinates(c).right,EditorUI::GetLocalCoordinates(c).top,128,32,9003);
	HWND resetFocus = CreateWindowEx(0,"Button","UnFocus",BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,EditorUI::GetLocalCoordinates(b).right,EditorUI::GetLocalCoordinates(b).top,128,32,hWnd,(HMENU)SET_NULL_FOCUS_ID,Engine::Window.hInstance,NULL);
		
	
	

	HWND a2 = EditorUI::addLabel(hWnd,"Mouse X:",EditorUI::GetLocalCoordinates(b).left,300,128,32,90502);
	HWND ab2 = EditorUI::addLabel(hWnd,"Mouse Y:",EditorUI::GetLocalCoordinates(b).left,332,128,32,90552);
	HWND ac2 = EditorUI::addLabel(hWnd,"0",EditorUI::GetLocalCoordinates(ab2).right,300,128,32,90562);
	HWND ad2 = EditorUI::addLabel(hWnd,"0",EditorUI::GetLocalCoordinates(a2).right,332,128,32,90572);
	
	
	
	HWND a = EditorUI::addLabel(hWnd,"Right:",EditorUI::GetLocalCoordinates(b).left,200,128,32,9050);
	HWND ab = EditorUI::addLabel(hWnd,"Left:",EditorUI::GetLocalCoordinates(b).left,232,128,32,9055);
	HWND ac = EditorUI::addLabel(hWnd,"0",EditorUI::GetLocalCoordinates(ab).right,200,128,32,9056);
	HWND ad = EditorUI::addLabel(hWnd,"0",EditorUI::GetLocalCoordinates(a).right,232,128,32,9057);

	if(!hWnd)
	{
		MessageBox(NULL,"Error creating window","Error",MB_OK | MB_ICONERROR);
	}
	else
	{
		ShowWindow(hWnd,1);
		UpdateWindow(hWnd);
	}
}
EngineWindow::~EngineWindow()
{
	for(std::map<std::string,EditorGroup>::iterator it = fieldGroup.begin(); it != fieldGroup.end(); it++)
	{
		for(auto controlField_it = it->second.field.begin(); controlField_it != it->second.field.end(); controlField_it++)
		{
			delete controlField_it->second;
			controlField_it->second = 0;
		}
		DestroyWindow(it->second.hwnd);
	}
	
	UnregisterClass(windowDefinedName,Engine::Window.hInstance);
}
void EngineWindow::cleanse()
{
	for(auto it = fieldGroup.begin(); it != fieldGroup.end(); it++)
	{
		for(auto jt = it->second.field.begin(); jt != it->second.field.end(); jt++)
		{
			DestroyWindow(jt->second->label);
			DestroyWindow(jt->second->hwnd);
		//	delete jt->second;
		//	jt->second = 0;
		}
		DestroyWindow(it->second.hwnd);
	}
	fieldGroup.clear();
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	
		case WM_CREATE:
		{  
			break;
		}
		case WM_COMMAND:
		{	
			switch(LOWORD(wParam))
			{
				#pragma region Buttons
				case SHOW_COMMAND_ID:
				{
					 EditorUI::RedirectIOToConsole();
					 break;
				} 
				case SET_NULL_FOCUS_ID:
				{
					Engine::Window.setGameObject(NULL);
					break;
				}
				#pragma endregion
				case ID_FILE_EXIT:
				{
					DestroyWindow(hWnd);
					break;
				}
			}
		}
		case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				DestroyWindow(hWnd);
			//	SetFocus(hWnd);
			}
			break;

		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
void EngineWindow::print(std::string str)
{
	
	std::cout << str;
}