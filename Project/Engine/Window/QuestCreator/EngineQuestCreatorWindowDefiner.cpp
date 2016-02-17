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
	size = Vector2(700, 700);
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

	NameHWnd = CreateWindowEx(0, "EDIT", "...", WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 10, 170, 20, hWnd, (HMENU)ID_ITEMNAME, hInstance, NULL);
	NameLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Name", WS_CHILD | WS_VISIBLE, 50, 10, 90, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);


	IDHWnd = CreateWindowEx(0, "EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 100, 30, 70, 20, hWnd, (HMENU)ID_ITEMID, hInstance, NULL);
	IDLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "ID", WS_CHILD | WS_VISIBLE, 75, 30, 14, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	IDButtonHWnd = CreateWindowEx(0, "BUTTON", "Suggest", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 176, 30, 94, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);


	DescriptionLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Description", WS_CHILD | WS_VISIBLE, 15, 60, 90, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
	DescriptionHWnd = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL | WS_VSCROLL, 10, 82, 460, 258, hWnd, (HMENU)ID_ITEMTOOLTIP, hInstance, NULL);

	iconField.start(hWnd, hInstance, Vector2(276, 10), Vector2(32, 32), (HMENU)ID_ITEMICON_BUTTON, "Quest Icon");

	ObjectiveListHWnd = CreateWindowEx(0, "LISTBOX", "", WS_VISIBLE | WS_CHILD | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_STANDARD,
		10, 360, 300, 250, hWnd, HMENU(6), hInstance, NULL);
	ObjectiveListLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Objectives", WS_CHILD | WS_VISIBLE, 10, 340, 90, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);

	RewardListHWnd = CreateWindowEx(0, "LISTBOX", "", WS_VISIBLE | WS_CHILD | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_STANDARD,
		320, 360, 300, 250, hWnd, HMENU(6), hInstance, NULL);
	RewardListLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Rewards", WS_CHILD | WS_VISIBLE, 320, 340, 90, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);


	AddObjectiveButton = CreateWindowEx(0, "BUTTON", "Add", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 10, 600, 100, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);
	RemoveObjectiveButton = CreateWindowEx(0, "BUTTON", "Remove", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 110, 600, 100, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);
	EditObjectiveButton = CreateWindowEx(0, "BUTTON", "Edit", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 210, 600, 100, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);

	AddRewardButton = CreateWindowEx(0, "BUTTON", "Add", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 320, 600, 100, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);
	RemoveRewardButton = CreateWindowEx(0, "BUTTON", "Remove", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 420, 600, 100, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);
	EditRewardButton = CreateWindowEx(0, "BUTTON", "Edit", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 520, 600, 100, 20, hWnd, (HMENU)ID_ITEMID_NEXT_VALID_ID, hInstance, NULL);

}

void EngineQuestCreator::setNextValidID()
{
	if (ID == 0)
		ID++;
	while (Engine::World.EditorAllItems.find(ID) != Engine::World.EditorAllItems.end())
	{
		ID++;
	}
	SendMessage(IDHWnd, WM_SETTEXT, NULL, (LPARAM)std::to_string(ID).c_str());
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