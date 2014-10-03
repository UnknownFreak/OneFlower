#ifndef WindowClass_H
#define WindowClass_H
#include <Windows.h>
#include "Vector.h"

class BasicWindow
{
public:
	BasicWindow();
	Vector2 size;
	HINSTANCE hInstance;
	HWND hWnd;

private:
	LPCTSTR windowDefinedName;
	LPCTSTR titleBarDisplay;

	WNDCLASSEX wc;

	static LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	
};
const BasicWindow* RequestWindow();
BasicWindow* SetWindow();

/*
class MainWindow:public BasicWindow
{
public:
	MainWindow();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	

};

//*/


#endif