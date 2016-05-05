//#ifdef _DEBUG
//#include "QuestObjectiveCreator.hpp"
//#include "../../Resource.h"
//
//bool QuestObjectiveCreator::isEdit = false;
//unsigned int QuestObjectiveCreator::registered = 0;
//EngineItemCreatorTypeField* g_QuestTypes;
//std::string g_mySelected = "Fetch/Collect";
//SetTargetWindow* g_TargetWindow;
//QuestObjectiveCreator::
//~QuestObjectiveCreator()
//{
//	DestroyWindow(hWnd);
//	registered--;
//	if (registered == 0)
//	{
//		UnregisterClass(windowDefinedName, hInstance);
//	}
//}
//
//QuestObjectiveCreator::
//QuestObjectiveCreator()
//{
//	windowDefinedName = "ObjectiveView";
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
//void QuestObjectiveCreator::show(HWND parent, HINSTANCE hInst, bool edit)
//{
//	isEdit = edit;
//	if (!hWnd)
//	{
//		hInstance = hInst;
//		hWnd = CreateWindowEx(0, windowDefinedName, "Add Objective",
//			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUPWINDOW,					// default window
//			CW_USEDEFAULT,				// Windows decides the position
//			CW_USEDEFAULT,				// where the window ends up on the screen
//			360,						// The programs width
//			400,						// and height in pixels
//			parent,		// The window is a child-window to desktop
//			NULL,						// No menu
//			hInst,					// Program Instance handler
//			NULL						// No Window Creation data
//			//this
//			);
//		objectiveNameLabel = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Objective Name:", WS_CHILD | WS_VISIBLE, 0, 0, 110, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
//		objectiveNameHWnd = CreateWindowEx(0, "EDIT", "...", WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 0, 100, 20, hWnd, (HMENU)1, hInstance, NULL);
//
//		objectiveNameLabel = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Description", WS_CHILD | WS_VISIBLE, 0, 20, 110, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
//		objectiveNameHWnd = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 0, 40, 210, 80, hWnd, (HMENU)2, hInstance, NULL);
//		QuestTypes.start(hWnd, hInstance, Vector2(220, 0), Vector2(120, 120), 10, { "Escort", "Explore", "Work", "Kill", "Fetch/Collect" });
//
//		countLabel = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Count:", WS_CHILD | WS_VISIBLE, 0, 160, 50, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);
//		countHWnd = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 55, 160, 155, 20, hWnd, (HMENU)3, hInstance, NULL);
//
//		targetLabelHWnd = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Target:", WS_CHILD | WS_VISIBLE, 0, 140, 50, 20, hWnd, (HMENU)ID_CREATOR_LABELS, hInstance, NULL);;
//		targetHWnd = CreateWindowEx(0, "EDIT", "NULL", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_READONLY, 55, 140, 155, 20, hWnd, (HMENU)4, hInstance, NULL);
//		setTargetHWnd = CreateWindowEx(0, "BUTTON", "Set", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 215, 140, 40, 20, hWnd, (HMENU)5, hInstance, NULL);
//		
//		isBonusObjective = CreateWindowEx(0,"BUTTON","Is Bonus Objective",BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE ,55,180,200,20,hWnd,(HMENU)6,hInstance,NULL);
//	
//	}
//	if (isEdit)
//	{
//		SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)"Edit Objective");
//	}
//	else
//	{
//		SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)"Add Objective");
//	}
//	QuestTypes.setText(" Objective Type");
//	g_QuestTypes = &QuestTypes;
//	g_TargetWindow = &target;
//	ShowWindow(hWnd, TRUE);
//}
//
//LRESULT CALLBACK QuestObjectiveCreator::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	if (g_QuestTypes)
//	{
//		if (g_mySelected != g_QuestTypes->getCheckedType())
//		{
//			g_mySelected = g_QuestTypes->getCheckedType();
//			SendMessage(GetDlgItem(hWnd, 4), WM_SETTEXT, NULL, (LPARAM)"NULL");
//			if (g_mySelected == "Escort" || g_mySelected == "Explore")
//				EnableWindow(GetDlgItem(hWnd,3),FALSE);
//			else
//				EnableWindow(GetDlgItem(hWnd, 3), TRUE);
//		}
//	}
//	switch (msg)
//	{
//	case SET_TARGET_OBJECTIVE:
//	{
//		std::string myText = std::string((char*)wParam);
//		myText.append(std::string((char*)lParam));
//
//		SendMessage(GetDlgItem(hWnd, 4), WM_SETTEXT, NULL, (LPARAM)myText.c_str());
//	}
//	
//	case WM_COMMAND:
//	{
//		
//		switch (LOWORD(wParam))
//		{
//		case 5:
//		{
//			g_TargetWindow->show(hWnd, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),g_QuestTypes->getCheckedType());
//			return 0;
//		}
//		case 99999999:
//		{
//			if (!isEdit)
//				SendMessage(GetParent(hWnd), WM_COMMAND, COMMAND_ADD_OBJECTIVE, NULL);
//			else
//				SendMessage(GetParent(hWnd), WM_COMMAND, COMMAND_EDIT_OBJECTIVE, NULL);
//			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
//			return 0;
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
//#endif