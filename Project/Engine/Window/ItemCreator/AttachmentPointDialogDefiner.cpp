//#include "AttachmentPointDialog.hpp"
//#include "../../Resource.h"
//unsigned int EngineItemCreatorAttachmentPointDialog::registered = 0;
//std::map<std::string, Vector2>* EngineItemCreatorAttachmentPointDialog::ref = 0;
//EngineItemCreatorImageField* ImageRef;
//EngineItemCreatorAttachmentPointDialog::
//~EngineItemCreatorAttachmentPointDialog()
//{
//	DestroyWindow(hWnd);
//	registered--;
//	if (registered == 0)
//	{
//		UnregisterClass("AttachmentView", hInstance);
//	}
//}
//
//EngineItemCreatorAttachmentPointDialog::
//EngineItemCreatorAttachmentPointDialog()
//{
//	windowDefinedName = "AttachmentView";
//
//	wc.lpszClassName = windowDefinedName;
//	wc.lpfnWndProc = WndProcAttachment;						// This function is called by windows
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
//void EngineItemCreatorAttachmentPointDialog::show(EngineItemCreatorImageField* _parent, HWND hWndParent, HINSTANCE hInst)
//{
//	
//	if (hWnd == NULL)
//	{
//		hInstance = hInst;
//		parent = _parent;
//		hWnd = CreateWindowEx(0, "AttachmentView", "Attachment points",
//			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX| WS_POPUPWINDOW,					// default window
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
//		add = CreateWindowEx(0, "BUTTON", "Add Point", WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD, 150,0,100,20,hWnd,HMENU(1),hInstance,NULL);
//		remove = CreateWindowEx(0, "BUTTON", "Remove Point", WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD, 150, 20, 100, 20, hWnd, HMENU(2), hInstance, NULL);
//		CreateWindowEx(0, "STATIC", "x", WS_VISIBLE | WS_CHILD, 150, 80, 30, 20, hWnd, NULL, hInstance, NULL);
//		CreateWindowEx(0, "STATIC", "y", WS_VISIBLE | WS_CHILD, 150, 100, 30, 20, hWnd, NULL, hInstance, NULL);
//		CreateWindowEx(0, "STATIC", "Point name", WS_VISIBLE | WS_CHILD, 150, 40, 100, 20, hWnd, NULL, hInstance, NULL);
//		name = CreateWindowEx(0, "EDIT", "", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 60, 100, 20, hWnd, HMENU(3), hInstance, NULL);
//		x = CreateWindowEx(0, "EDIT", "0", WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER, 180, 80, 70, 20, hWnd, HMENU(4), hInstance, NULL);
//		y = CreateWindowEx(0, "EDIT", "0", WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER, 180, 100, 70, 20, hWnd, HMENU(5), hInstance, NULL);
//		pointList = CreateWindowEx(0, "LISTBOX", "", WS_VISIBLE| WS_CHILD | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_STANDARD,
//			0, 0, 150, 170, hWnd, HMENU(6), hInstance, NULL);
//	}
//	ref = &attachpoints;
//	ImageRef = _parent;
//	ShowWindow(hWnd, true);
//}
//LRESULT CALLBACK EngineItemCreatorAttachmentPointDialog::WndProcAttachment(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_COMMAND:
//	{
//		switch (LOWORD(wParam))
//		{
//		case 1:
//		{
//			char _name[64];
//			char _xPos[10];
//			char _yPos[10];
//			HWND dlgItem = GetDlgItem(hWnd, 3);
//			SendMessage(dlgItem, WM_GETTEXT, 64, LPARAM(_name)); 
//			dlgItem = GetDlgItem(hWnd, 4);
//			SendMessage(dlgItem, WM_GETTEXT, 10, LPARAM(_xPos));
//			dlgItem = GetDlgItem(hWnd, 5);
//			SendMessage(dlgItem, WM_GETTEXT, 10, LPARAM(_yPos));
//			std::string name = _name;
//			int xPos = std::stoi(_xPos);
//			int yPos = std::stoi(_yPos);
//
//			dlgItem = GetDlgItem(hWnd, 6);
//			if (ref->find(name) == ref->end())
//			{
//				ref->insert(std::pair<std::string, Vector2>(name, Vector2(xPos, yPos)));
//				int pos = (int)SendMessage(dlgItem, LB_ADDSTRING, NULL, (LPARAM)_name);
//				SendMessage(dlgItem, LB_SETITEMDATA, pos, (LPARAM)_name);
//
//				ImageRef->setAttachmentPoints(*ref);
//				ImageRef->redraw();
//			}
//			return 0;
//		}
//		case 2:
//		{
//			HWND dlgItem = GetDlgItem(hWnd, 6);
//			int index = (int)SendMessage(dlgItem, LB_GETCURSEL, 0, 0);
//			int i = 0;
//			for (std::map<std::string, Vector2>::iterator it = ref->begin(); it != ref->end(); it++)
//			{
//				if (i == index)
//				{
//					ref->erase(it);
//					SendMessage(dlgItem, LB_DELETESTRING, index, 0);
//					break;
//				}
//				i++;
//			}
//			ImageRef->setAttachmentPoints(*ref);
//			ImageRef->redraw();
//			return 0;
//		}
//		case 4:
//		{
//			HWND dlgItem = GetDlgItem(hWnd, 4);
//			if (SendMessage(dlgItem, EM_GETMODIFY, NULL, NULL))
//			{
//				HWND lst = GetDlgItem(hWnd, 6);
//				int index = (int)SendMessage(lst, LB_GETCURSEL, 0, 0);
//				int i = 0;
//				for (std::map<std::string, Vector2>::iterator it = ref->begin(); it != ref->end(); it++)
//				{
//					if (i == index)
//					{
//						char pos[10];
//						SendMessage(dlgItem, WM_GETTEXT, 10, LPARAM(pos));
//						if (std::string(pos) != "")
//							it->second.x = std::stod(pos);
//						break;
//					}
//					i++;
//				}
//				ImageRef->setAttachmentPoints(*ref);
//				ImageRef->redraw();
//			}
//			return 0;
//		}
//		case 5:
//		{
//			HWND dlgItem = GetDlgItem(hWnd, 5);
//			if (SendMessage(dlgItem, EM_GETMODIFY, NULL, NULL))
//			{
//				HWND lst = GetDlgItem(hWnd, 6);
//				int index = (int)SendMessage(lst, LB_GETCURSEL, 0, 0);
//				int i = 0;
//				for (std::map<std::string, Vector2>::iterator it = ref->begin(); it != ref->end(); it++)
//				{
//					if (i == index)
//					{
//						char pos[10];
//						SendMessage(dlgItem, WM_GETTEXT, 10, LPARAM(pos));
//						if (std::string(pos) != "")
//							it->second.y = std::stod(pos);
//						break;
//					}
//					i++;
//				}
//				ImageRef->setAttachmentPoints(*ref);
//				ImageRef->redraw();
//			}
//			return 0;
//		}
//		case 6:
//		{
//			switch (HIWORD(wParam))
//			{
//				case LBN_SELCHANGE:
//				{
//					HWND dlgItem = GetDlgItem(hWnd, 6);
//					int index = (int)SendMessage(dlgItem, LB_GETCURSEL, 0, 0);
//					int i = 0;
//					for (std::map<std::string, Vector2>::iterator it = ref->begin(); it != ref->end(); it++)
//					{
//						if (i == index)
//						{
//							dlgItem = GetDlgItem(hWnd, 4);
//							SendMessage(dlgItem, WM_SETTEXT, NULL, LPARAM(std::to_string(it->second.x).c_str()));
//							dlgItem = GetDlgItem(hWnd, 5);
//							SendMessage(dlgItem, WM_SETTEXT, NULL, LPARAM(std::to_string(it->second.y).c_str()));
//							return true;
//						}
//						i++;
//					}
//					return true;
//				}
//			}
//		}
//		default:
//			break;
//		}
//		break;
//	}
//	case WM_CLOSE:
//		ShowWindow(hWnd, FALSE);
//		return 0;
//	default:
//		break;
//	}
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}