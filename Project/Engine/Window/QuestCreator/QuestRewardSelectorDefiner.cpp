//#include "QuestRewardSelector.hpp"
//#include "../../../Engine.hpp"
//#include "../../../Game/Item/Item.hpp"
//
//
//bool QuestRewardSelectorWindow::isEdit = false;
//std::string QuestRewardSelectorWindow::ItemName = "";
//unsigned int QuestRewardSelectorWindow::registered = 0;
//QuestRewardSelectorWindow::
//~QuestRewardSelectorWindow()
//{
//	DestroyWindow(hWnd);
//	registered--;
//	if (registered == 0)
//	{
//		UnregisterClass(windowDefinedName, hInstance);
//	}
//}
//
//QuestRewardSelectorWindow::
//QuestRewardSelectorWindow()
//{
//	windowDefinedName = "RewardView";
//
//	wc.lpszClassName = windowDefinedName;
//	wc.lpfnWndProc = WndProc;												// This function is called by windows
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.hIcon = NULL;
//	wc.hIconSm = NULL;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.lpszMenuName = NULL;													// No menu
//	wc.cbClsExtra = 0;														// No extra bytes after the window class
//	wc.cbWndExtra = 0;														// structure or the window instance
//	wc.hbrBackground = HBRUSH(COLOR_BTNFACE + 1);
//
//	if (registered == 0)
//		if (RegisterClassEx(&wc))
//			registered = 1;
//		else;
//	else
//		registered++;
//}
//
//void QuestRewardSelectorWindow::show(HWND hWndParent, HINSTANCE hInst, bool edit)
//{
//	isEdit = edit;
//	if (!hWnd)
//	{
//		hInstance = hInst;
//		hWnd = CreateWindowEx(0, windowDefinedName, "Add a reward",
//			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUPWINDOW,					// default window
//			CW_USEDEFAULT,				// Windows decides the position
//			CW_USEDEFAULT,				// where the window ends up on the screen
//			300,						// The programs width
//			200,						// and height in pixels
//			hWndParent,		// The window is a child-window to desktop
//			NULL,						// No menu
//			hInst,					// Program Instance handler
//			NULL						// No Window Creation data
//			//this
//			);
//		
//		listView = CreateWindowEx(0, "LISTBOX", "", WS_VISIBLE | WS_CHILD | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_STANDARD,
//		0, 0, 150, 170, hWnd, HMENU(4), hInstance, NULL);
//		add = CreateWindowEx(0, "BUTTON", "Add", WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD, 150, 134, 100, 20, hWnd, HMENU(1), hInstance, NULL);
//		quantity = CreateWindowEx(0, "EDIT", "", WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER, 150, 20, 100, 20, hWnd, HMENU(2), hInstance, NULL);
//		quantityLabel = CreateWindowEx(0, "STATIC", "Quantity", WS_VISIBLE | WS_CHILD, 150, 0, 100, 20, hWnd, HMENU(3), hInstance, NULL);
//
//		
//	}
//
//	if (isEdit)
//	{
//		SendMessage(add, WM_SETTEXT, NULL, (LPARAM)"Edit");
//		SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)"Edit a reward");
//	}
//	else
//	{
//		SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)"Add a reward");
//		SendMessage(add, WM_SETTEXT, NULL, (LPARAM)"Add");
//	}
//
//
//	HWND dlgItem = GetDlgItem(hWnd, 4);
//
//	SendMessage(dlgItem, LB_RESETCONTENT, 0,0);
//
//	for (std::map<Items::Item*, HTREEITEM>::iterator it = Engine::Window.prefabList.allItemsInGame().begin();
//		it != Engine::Window.prefabList.allItemsInGame().end(); it++)
//	{
//		std::string myValue = std::to_string(it->first->getID())+ ':' + it->first->getName();
//		int pos = (int)SendMessage(dlgItem, LB_ADDSTRING, NULL, (LPARAM)myValue.c_str());
//		SendMessage(dlgItem, LB_SETITEMDATA, pos, (LPARAM)myValue.c_str());
//	}
//	ItemName = "0:NotSet:0";
//	ShowWindow(hWnd,TRUE);
//}
//
//LRESULT CALLBACK QuestRewardSelectorWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_COMMAND:
//	{
//		switch (LOWORD(wParam))
//		{
//		//Add
//		case 1: 
//		{
//			char _quantity[128] = { 0 };
//			char _selected[128] = { 0 };
//			HWND dlgItem = GetDlgItem(hWnd, 2);
//			SendMessage(dlgItem, WM_GETTEXT, 128, LPARAM(_quantity));
//			dlgItem = GetDlgItem(hWnd,4);
//			int index = SendMessage(dlgItem, LB_GETCURSEL, 0, 0);
//			SendMessage(dlgItem, LB_GETTEXT, index, LPARAM(_selected));
//
//			if (_selected[0] != '\0')
//			{
//				ItemName = _selected;
//				ItemName.append(":");
//				ItemName.append(_quantity);
//				Engine::Window.debug.print(ItemName, __LINE__, __FILE__);
//				if (!isEdit)
//					SendMessage(GetParent(hWnd), WM_COMMAND, COMMAND_ADD_REWARD, NULL);
//				else
//				{
//					SendMessage(GetParent(hWnd), WM_COMMAND, COMMAND_EDIT_REWARD, NULL);
//				}
//			}
//			
//			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
//			return 0;
//		}
//		default:
//			break;
//		}
//		break;
//	}
//	case WM_CLOSE:
//		ShowWindow(hWnd,FALSE);
//		return 0;
//	default:
//		break;
//	}
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}