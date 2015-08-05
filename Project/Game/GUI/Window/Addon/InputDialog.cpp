#include "InputDialog.hpp"
#include "../../../../Engine.hpp"
#include <Windows.h>

static LPTSTR buffer;
static int nMax;
static LPCSTR title;
static LPTSTR ID;
static int type;
static bool cancel;

//TODO fix all ugly hacks
INT_PTR InputDialog::InputBox(LPCSTR szTitle,LPTSTR szResult,LPTSTR nResultID,DWORD nResultSize,HWND Parent,int diagType)
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
			switch(type)
			{
				HWND dlg;
				case ID_DIALOG_RENAME:
					dlg = GetDlgItem(hWnd,ID_DIALOG_LABEL_ID);
					ShowWindow(dlg,FALSE);
					dlg = GetDlgItem(hWnd,ID_DIALOG_TEXT_ID);
					ShowWindow(dlg,FALSE);
					break;
				case ID_DIALOG_RESIZE:
					dlg = GetDlgItem(hWnd,ID_DIALOG_TEXT);
					SetWindowLong(dlg,GWL_STYLE,ES_AUTOHSCROLL | ES_NUMBER | WS_VISIBLE | WS_CHILD | WS_TABSTOP);
					dlg = GetDlgItem(hWnd,ID_DIALOG_LABEL);
					SetWindowText(dlg,"X");
					dlg = GetDlgItem(hWnd,ID_DIALOG_LABEL_ID);
					SetWindowText(dlg,"Y");
					break;
			}
			SetWindowText(hWnd,title);
			return (INT_PTR)TRUE;
		case WM_CLOSE:
			EndDialog(hWnd,LOWORD(ID_DIALOG_CANCEL));
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			if(LOWORD(wParam) == ID_DIALOG_OK)
			{
				GetDlgItemText(hWnd,ID_DIALOG_TEXT,buffer,nMax);
				GetDlgItemText(hWnd,ID_DIALOG_TEXT_ID,ID,nMax);
				cancel = false;
				EndDialog(hWnd,LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			else if(LOWORD(wParam) == ID_DIALOG_CANCEL)
			{
				cancel = true;
				EndDialog(hWnd,LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}

bool InputDialog::getIfCancelled()
{
	return cancel;
}