#ifndef InputDialog_HPP
#define InputDialog_HPP
#include "Resource.h"
#include <windows.h>
class InputDialog
{
public:
	static INT_PTR InputBox(LPCSTR szTitle, LPTSTR szResult, LPTSTR nResultID, DWORD nResultSize, HWND Parent);
	
private:
	static INT_PTR CALLBACK dlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};



#endif