#if defined _DEBUG
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
#include "EditorUI\EditorFieldGroup.hpp"
#include <Windows.h>

#include "InputDialog.hpp"

#include "Component\GameObject.h"
#include "Component\DialogComponent.hpp"
#include "Component\RenderComponent.h"
#include "Component\TransformComponent.hpp"
#include "Component\RigidComponent.hpp"
#include "Component\DialogComponent.hpp"
#include "Component\HitboxComponent.hpp"
#include "Component\StatsComponent.hpp"
#include "Component\HealthComponent.hpp"

#include "Component\ReputationComponent.hpp"
#include "Component\ProjectilePatternComponent.hpp"
#include "Component\LevelComponent.h"

#include "Component\InventoryComponent.hpp"

#include "Zone.hpp"

#define SHOW_COMMAND_ID 501
#define SET_NULL_FOCUS_ID 503

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
EngineWindow::EngineWindow():size(1366,768)
{
	windowDefinedName = "EditorWindow";
	titleBarDisplay = "Editor Window";

	//The First Windows structure
	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = WndProc;						// This function is called by windows
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// Catch double-clicks
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(MENU_ICON));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(MENU_ICON),IMAGE_ICON,16,16,0);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszMenuName = MAKEINTRESOURCE(MENU_ID);;							// No menu
	wc.cbClsExtra = 0;														// No extra bytes after the window class
	wc.cbWndExtra = 0;														// structure or the window instance
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
		size.x,						// The programs width
		size.y,						// and height in pixels
		NULL,						// The window is a child-window to desktop
		NULL,						// No menu
		hInstance,					// Program Instance handler
		NULL						// No Window Creation data
		//this
		);

	//Move this
	if(!hWnd)
	{
		MessageBox(NULL,"Error creating window","Error",MB_OK | MB_ICONERROR);
	}
	else
	{
		ShowWindow(hWnd,1);
		UpdateWindow(hWnd);
		ListViewer.start();
		focus.start();
	}
}
EngineWindow::~EngineWindow()
{
	focus.cleanse();
	DestroyWindow(focus.hWnd);
	UnregisterClass(windowDefinedName,Engine::Window.hInstance);
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
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
#pragma region ADD_MENU

				case ADD_GameObject:
				{
					GameObject* a = new GameObject();
					Engine::game.addGameObject(a);
					Engine::Window.setGameObject(a);
					Engine::World.getCurrentZone()->objects.push_back(a);
					break;
				}
				case ADD_DialogComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<DialogComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}
				case ADD_HitboxComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<HitboxComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}
				case ADD_OverHeadComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<OverheadComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}
				case ADD_RenderComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<RenderComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}

				case ADD_RigidComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<RigidComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}
				case ADD_TransformComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<TransformComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}
				case ADD_StatsComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<StatsComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}
				case ADD_HealthComponent:
				{
					if(Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<HealthComponent>();
					else
						MessageBoxA(0,"No focused Object, Select a GameObject first","Error 500",0);
					break;
				}
				case ADD_ReputationComponent:
				{
					if (Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<ReputationComponent>();
					break;
				}
				case ADD_ProjectilePatternComponent:
				{
					if (Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<ProjectilePatternComponent>();
					break;
				}
				case ADD_LevelComponent:
				{
					if (Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<LevelComponent>();
					break;
				}
				case ADD_InventoryComponent:
				{
					if (Engine::Window.focus.gameObject)
						Engine::Window.focus.gameObject->AddComponent<InventoryComponent>();
					break;
				}
#pragma endregion
#pragma region GUI_MENU
				case ID_SHOW_HIDE_GUI:
				{
					Engine::GUI.showHideGUI();
					break;
				}
				case ID_SHOW_HIDE_MOUSE:
				{
					Engine::GUI.showHideMouse();
					break;
				}
				case ID_SHOW_HIDE_OVERHEAD:
				{
					Engine::GUI.showHideOverhead();
					break;
				}
				case ID_SHOW_HIDE_DIALOGS:
				{
					Engine::GUI.showHideDialogs();
					break;
				}
#pragma endregion
#pragma region FILE_MENU
				
				case ID_FILE_EXIT:
				{
					DestroyWindow(hWnd);
					break;
				}
#pragma endregion
#pragma region ZONE_MENU
				case ID_ADD_ZONE:
				{
					char name[100] = { 0 };
					char value[100] = { 0 };
					InputDialog::InputBox("Add Zone",name,value,100,hWnd);
					unsigned int i = std::atoi(value);
					if (!InputDialog::getIfCancelled())
						Engine::World.EditorAddNewZone(name,i);
					break;
				}
				case ID_LOAD_ZONE:
				{
					char name[100] = { 0 };
					char value[100] = { 0 };
					InputDialog::InputBox("Load Zone", name, value, 100, hWnd);
					unsigned int i = std::atoi(value);
					if (!InputDialog::getIfCancelled())
						Engine::World.EditorLoadZone(name, i);
					break;
				}
				case ID_SAVE_ZONE:
				{
					Engine::World.EditorSaveZone();
					break;
				}
				case ID_REMOVE_ZONE:
				{
					Engine::World.EditorRemoveZone();
					break;
				}
				case ID_SETBACKGROUND:
				{
					char buffer[100] = {0};
					//Probably redo this with editorfield instead
					InputDialog::InputBox("SetBackground",buffer,NULL,100,hWnd,ID_DIALOG_RENAME);
					if(!InputDialog::getIfCancelled())
						Engine::World.EditorSetBackground(buffer);
					else
						MessageBox(Engine::Window.hWnd,"TODO","INFO",NULL);
					break;
				}

				case ID_SETBACKGROUND_SIZE:
				{
					char cX[7] = { 0 };
					char cY[7] = { 0 };
					InputDialog::InputBox("Set Background Size", cX, cY, 7, hWnd, ID_DIALOG_RESIZE);
					int x = std::atoi(cX);
					int y = std::atoi(cY);
					if (!InputDialog::getIfCancelled())
						Engine::World.EditorSetBackgroundSize(x, y);
					break;
				}
#pragma endregion
#pragma region Remove_Menu
				case REMOVE_GameObject:
				{
					if(Engine::Window.focus.gameObject)
					{
						Engine::World.RemoveGameObjectFromZone(Engine::Window.focus.gameObject);
						Engine::game.requestRemoveal(Engine::Window.focus.gameObject);
					}
					else
						MessageBoxA(0,"No focused object","CTRL + F FocusedObjectRemoveal",0);
				}
#pragma endregion
				default:
					break;
			}
			switch(HIWORD(wParam))
			{
				case LBN_SELCHANGE:
				{
					Engine::Window.ListViewer.getSelection();
					break;
				}
				default:
					break;
			}
		}
		case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		case WM_WINDOWPOSCHANGED:
		{
#pragma region WM_WINDOWPOSCHANGED
			RECT a = EditorUI::GetLocalCoordinates(hWnd);
			RECT b = EditorUI::GetLocalCoordinates(Engine::View.hWnd);
#pragma region Focus Window
			SetWindowPos
				(
				Engine::Window.focus.hWnd,hWnd,
				a.right - (Engine::Window.focus.size.x + GetSystemMetrics(SM_CXBORDER) + (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2)),
				//LOW: Replace with GetThemeSysSize inside UxTheme.h
				a.top + GetSystemMetrics(SM_CYCAPTION) + (GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYEDGE) * 2) + GetSystemMetrics(SM_CYMENU),
				b.right - b.left,
				b.bottom - b.top,
				SWP_NOSIZE
				);
#pragma endregion
#pragma region ListView Window
			SetWindowPos
				(
				Engine::Window.ListViewer.hWnd,hWnd,
				a.right - (Engine::Window.ListViewer.size.x + Engine::Window.focus.size.x + GetSystemMetrics(SM_CXBORDER) + (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2)),
				//LOW: Replace with GetThemeSysSize inside UxTheme.h
				a.top + GetSystemMetrics(SM_CYCAPTION) + (GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYEDGE) * 2) + GetSystemMetrics(SM_CYMENU),
				b.right - b.left,
				b.bottom - b.top,
				SWP_NOSIZE
				);
#pragma endregion

#pragma region Game View
			SetWindowPos
				(
				Engine::View.hWnd,hWnd,
				a.left + GetSystemMetrics(SM_CXBORDER) + (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2),
				//LOW: Replace with GetThemeSysSize inside UxTheme.h
				a.top + GetSystemMetrics(SM_CYCAPTION) + (GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYEDGE) * 2) + GetSystemMetrics(SM_CYMENU),
				b.right - b.left,
				b.bottom - b.top,
				SWP_NOSIZE
				);
#pragma endregion

#pragma endregion
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
#endif