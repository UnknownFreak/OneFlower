#include "InputDialog.hpp"
#include "Engine.hpp"
#include <Windows.h>

static LPTSTR buffer;
static int nMax;
static LPCSTR title;
static LPTSTR ID;
static int type;
INT_PTR InputDialog::InputBox(LPCSTR szTitle,LPTSTR szResult,LPTSTR nResultID,DWORD nResultSize,HWND Parent, int diagType)
{
	nMax = nResultSize;
	buffer = szResult;
	title = szTitle;
	ID = nResultID;
	type = diagType;
	DialogBox(Engine::Window.hInstance,MAKEINTRESOURCE(DIALOG_ID),Parent,dlgProc);

	//GetDlgItemText(Engine::Window.hWnd, ID_DIALOG_TEXT, szResult, nResultSize);
	szResult = buffer;
	nResultID = ID;
	return TRUE;
}

INT_PTR CALLBACK InputDialog::dlgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			return (INT_PTR)TRUE;
		case WM_INITDIALOG:
			switch (type)
			{
				case 1:
					HWND dlg = GetDlgItem(hWnd, ID_DIALOG_LABEL_ID);
					ShowWindow(dlg, FALSE);
					dlg = GetDlgItem(hWnd, ID_DIALOG_TEXT_ID);
					ShowWindow(dlg, FALSE);
					break;
			}
			SetWindowText(hWnd,title);
			return (INT_PTR)TRUE;
		case WM_CLOSE:
			EndDialog(hWnd,LOWORD(ID_DIALOG_CANCEL));
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			if(LOWORD(wParam) == ID_DIALOG_OK || LOWORD(wParam) == ID_DIALOG_CANCEL)
			{
				GetDlgItemText(hWnd,ID_DIALOG_TEXT,buffer,nMax);
				GetDlgItemText(hWnd,ID_DIALOG_TEXT_ID,ID,nMax);
				EndDialog(hWnd,LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}