#ifdef _DEBUG
#include "QuestObjectiveSetTargetWindow.hpp"
#include "../../../Engine.hpp"
#include "../../../Game/Item/Item.hpp"
unsigned int SetTargetWindow::registered = 0;
std::vector<ListViewItemStruct>* g_items;
SetTargetWindow::~SetTargetWindow()
{
	DestroyWindow(hWnd);
	registered--;
	if (registered == 0)
	{
		UnregisterClass(windowDefinedName, hInstance);
	}
}

SetTargetWindow::SetTargetWindow()
{
	windowDefinedName = "SetTargetWindow";

	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = WndProc;												// This function is called by windows
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;													// No menu
	wc.cbClsExtra = 0;														// No extra bytes after the window class
	wc.cbWndExtra = 0;														// structure or the window instance
	wc.hbrBackground = HBRUSH(COLOR_BTNFACE + 1);

	if (registered == 0)
		if (RegisterClassEx(&wc))
			registered = 1;
		else;
	else
		registered++;
}

void SetTargetWindow::show(HWND parent, HINSTANCE hInst, std::string type)
{
	if (!hWnd)
	{
		hInstance = hInst;
		hWnd = CreateWindowEx(0, windowDefinedName, "Set Target",
			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUPWINDOW,					// default window
			CW_USEDEFAULT,				// Windows decides the position
			CW_USEDEFAULT,				// where the window ends up on the screen
			318,						// The programs width
			320,						// and height in pixels
			parent,		// The window is a child-window to desktop
			NULL,						// No menu
			hInst,					// Program Instance handler
			NULL						// No Window Creation data
			//this
			);

		listBox = CreateWindowEx(0, "LISTBOX", "", WS_VISIBLE | WS_CHILD | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_STANDARD, 
			0, 0, 300, 250, hWnd, (HMENU)0, hInstance, NULL);
		set = CreateWindowEx(0,"BUTTON","Set",WS_VISIBLE | WS_CHILD| BS_PUSHBUTTON,200,251,80,20,hWnd,(HMENU)1,hInst,NULL);
	}

	items.clear();
	SendMessage(listBox, LB_RESETCONTENT, NULL, NULL);

	if (type == "Fetch/Collect")
	{
		int index = 0;
		for each (std::pair<Item*, HTREEITEM> pair in Engine::Window.prefabList.allItemsInGame())
		{
			int pos = (int)SendMessage(listBox, LB_ADDSTRING, NULL, (LPARAM)pair.first->getName().c_str());
			SendMessage(listBox, LB_SETITEMDATA, pos, (LPARAM)index);
			items.push_back(ListViewItemStruct(pair.first->getID(), pair.first->getName(), ListViewItemStruct::Item));
			index++;
		}
	}
	else if (type == "Kill" || type == "Escort")
	{
		int index = 0;
		for each (std::pair<Prefab*, HTREEITEM> pair in Engine::Window.prefabList.allPrefabsInGame())
		{
			if (pair.first->tag == "NPC")
			{
				int pos = (int)SendMessage(listBox, LB_ADDSTRING, NULL, (LPARAM)pair.first->name.c_str());
				SendMessage(listBox, LB_SETITEMDATA, pos, (LPARAM)index);
				items.push_back(ListViewItemStruct(pair.first->ID, pair.first->name, ListViewItemStruct::GameObject));
			}
			index++;
		}
	}
	else if(type == "Explore")
	{
		/*
		int index = 0;
		for each (std::pair<unsigned int, DBZone> pair in Engine::World.EditorAllZones)
		{
			int pos = (int)SendMessage(listBox, LB_ADDSTRING, NULL, (LPARAM)pair.second.name.c_str());
			SendMessage(listBox, LB_SETITEMDATA, pos, (LPARAM)index);
			items.push_back(ListViewItemStruct(pair.second.ID, pair.second.name, ListViewItemStruct::Zone));
			index++;
		}
		//*/
	}
	g_items = &items;
	ShowWindow(hWnd, TRUE);
}


LRESULT CALLBACK SetTargetWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1:
		{
			int pos = (int)SendMessage(GetDlgItem(hWnd, 0), LB_GETCURSEL, NULL, NULL);
			if (pos != -1)
			{
				int rv = (int)SendMessage(GetDlgItem(hWnd, 0), LB_GETITEMDATA, pos, NULL);
				ListViewItemStruct& selected = *(g_items->begin()+rv);
				std::string lP = std::to_string(selected.ID) + ":" + selected.name;
				std::string wP = "";
				if (selected.type == ListViewItemStruct::Item)
					wP = "Item - ";
				else if (selected.type == ListViewItemStruct::GameObject)
					wP = "GameObject - ";
				else if (selected.type == ListViewItemStruct::Zone)
					wP = "Zone - ";
				SendMessage(GetParent(hWnd), SET_TARGET_OBJECTIVE, (WPARAM)wP.c_str(), (LPARAM)lP.c_str());
			}
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			return 0;
		}
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
#endif