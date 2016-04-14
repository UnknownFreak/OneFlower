//#include "EffectEnchantDialog.hpp"
//
//unsigned int EngineItemCreatorEnchantEffectDialog::registered = 0;
//EngineItemCreatorEnchantEffectDialog::
//~EngineItemCreatorEnchantEffectDialog()
//{
//	DestroyWindow(hWnd);
//	registered--;
//	if (registered == 0)
//	{
//		UnregisterClass("EffectView", hInstance);
//	}
//}
//EngineItemCreatorEnchantEffectDialog::
//EngineItemCreatorEnchantEffectDialog()
//{
//	windowDefinedName = "EffectView";
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
//void EngineItemCreatorEnchantEffectDialog::clearEffect()
//{
//	//Clear the effect
//}
//void EngineItemCreatorEnchantEffectDialog::show(HWND hWndParent, HINSTANCE hInst)
//{
//
//	if (hWnd == NULL)
//	{
//		hInstance = hInst;
//		hWnd = CreateWindowEx(0, "EffectView", "Effects and enchantments <TODO>",
//			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUPWINDOW,					// default window
//			CW_USEDEFAULT,				// Windows decides the position
//			CW_USEDEFAULT,				// where the window ends up on the screen
//			300,						// The programs width
//			200,						// and height in pixels
//			hWndParent,					// The window is a child-window to hWndParent
//			NULL,						// No menu
//			hInst,						// Program Instance handler
//			NULL						// No Window Creation data
//			//this
//			);
//	}
//	ShowWindow(hWnd, true);
//}
//LRESULT CALLBACK EngineItemCreatorEnchantEffectDialog::WndProcAttachment(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_COMMAND:
//	{
//		switch (LOWORD(wParam))
//		{
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