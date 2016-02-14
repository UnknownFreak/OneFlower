#ifdef _DEBUG
#include "EngineQuestCreatorWindow.hpp"
#include "../../../Engine.hpp"
#include "../../Resource.h"
LRESULT CALLBACK WndProcQuestCreator(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


EngineQuestCreator::~EngineQuestCreator()
{
	DestroyWindow(hWnd);
	UnregisterClass(windowDefinedName, hInstance);
}

void EngineQuestCreator::start()
{
	hInstance = Engine::Window.hInstance;
	size = Vector2(500, 700);
	windowDefinedName = "Quest Creator";

	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = WndProcQuestCreator;						// This function is called by windows
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;													// No menu
	wc.cbClsExtra = 0;														// No extra bytes after the window class
	wc.cbWndExtra = 0;														// structure or the window instance
	wc.hbrBackground = HBRUSH(COLOR_BTNFACE + 1);

	if (!RegisterClassEx(&wc))
		MessageBox(NULL, "Error Registering The Window Class", "Error", MB_OK | MB_ICONERROR);

	hWnd = CreateWindowEx
		(
		0,							// Extended possibilites for variation
		windowDefinedName,			// Classname
		"Quest Creator",			// Title Text
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,					// default window
		CW_USEDEFAULT,				// Windows decides the position
		CW_USEDEFAULT,				// where the window ends up on the screen
		(int)size.x,						// The programs width
		(int)size.y,						// and height in pixels
		Engine::Window.hWnd,						// The window is a child-window to desktop
		NULL,						// No menu
		hInstance,					// Program Instance handler
		NULL						// No Window Creation data
		//this
		);
}



LRESULT CALLBACK WndProcQuestCreator(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOVE:
	{
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		switch (GetDlgCtrlID((HWND)lParam))
		{
		case ID_CREATOR_LABELS:
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (LRESULT)GetStockObject(NULL_BRUSH);
		default:
			break;
		}
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		default:
			break;
		}
		break;
	}
	case WM_CLOSE:
		ShowWindow(hWnd, FALSE);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void EngineQuestCreator::show()
{
	ShowWindow(hWnd, TRUE);
}


#endif