#include "UIAddon.hpp"
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include "../Component/TransformComponent.hpp"
#include "../Component/HitboxComponent.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "EditorField.hpp"
#include "../Component/GameObject.h"
#include "../Component/RenderComponent.h"
#include "../Engine.hpp"
// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;
int currentID = 0;
std::vector<int> recycleID;
WNDPROC prevWndProcGroup;
WNDPROC prevWndEditor;
WNDPROC prevWndText;
WNDPROC prevWndButton;
bool isDouble(char a);

#pragma region HWND handler Related
int EditorUI::RequestID()
{
	if(!recycleID.empty())
		return recycleID[0];
	else
		return 	currentID++;
}
void EditorUI::RecycleID(int i)
{
	recycleID.push_back(i);
}
bool isDouble(char a)
{
	if(!(a > 0 && a < 255))
		return false;
	else if(isdigit(a))
		return true;
	else if(a == '.')
		return true;
	else if(a == ',')
		return true;
	else
		return false;
}
RECT EditorUI::GetLocalCoordinates(HWND hWnd)
{
	RECT Rect;
	GetWindowRect(hWnd,&Rect);
	MapWindowPoints(HWND_DESKTOP,GetParent(hWnd),(LPPOINT)&Rect,2);
	//Rect.right -= Rect.left;
	return Rect;

}
#pragma endregion
//LOW: Set a limit of char to TextBox
LRESULT CALLBACK WndProcText(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CHAR:
		{
		switch(wParam)
		{
			#pragma region Enter
			case(VK_RETURN):
			{
				TCHAR txt[1024];
				GetWindowText(hwnd,txt,1024);
				std::string value(txt);
				std::string newValue = "";
				if(!value.empty())
				{
					for(size_t i = 0; i < value.size(); i++)
					{
						if(isDouble(value.at(i)))
							newValue.push_back(value[i]);
					}
					if(!newValue.empty())
					{
						if(value[0] == '-')
							newValue.insert(newValue.begin(),value[0]);
					}
					else
						newValue = "0";
				}
				else
					newValue = '0';
				SetWindowText(hwnd,newValue.c_str());
				SendMessage(hwnd,EM_SETSEL,newValue.size(),newValue.size());
				int id = GetWindowLong(hwnd,GWL_ID);
				Engine::Window.setValue(id,newValue);
			}
			#pragma endregion
			return 0;
			break;
		}
		default:
			break;
		}
	}
	return CallWindowProc(prevWndText,hwnd,msg,wParam,lParam);
}
LRESULT CALLBACK WndProcEditorFocus(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		default:
			break;
	}
	return CallWindowProc(prevWndEditor,hwnd,msg,wParam,lParam);
}
LRESULT CALLBACK WndProcComponent(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{

			}
			break;
		}

		/*
		case WM_COMMAND:
		{
		switch(HIWORD(wParam))
		{
		#pragma region EN_CHANGE
		case EN_CHANGE:
		{
		std::map<int,BaseField*>::iterator it;
		for(auto i = Engine::Window.fieldGroup.begin(); i != Engine::Window.fieldGroup.end(); i++)
		{
		it = i->second.field.find(LOWORD(wParam));
		if(it != i->second.field.end())
		{
		if(it->second->flags & FieldFlag::Decimal)
		{
		TCHAR txt[1024];
		GetWindowText(it->second->hwnd,txt,1024);
		std::string value(txt);
		if(!isDouble(value.at(value.size())))
		value.erase(value.end());
		break;
		}
		}
		}
		break;
		}
		#pragma endregion
		}
		break;
		}
		//*/
		default:
			break;
	}
	return CallWindowProc(prevWndProcGroup,hwnd,msg,wParam,lParam);
}
LRESULT CALLBACK WndProcButton(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam,int groupID)
{
	/*
	switch(msg)
	{
		default:
			break;
	}
	//*/
	return CallWindowProc(prevWndButton,hWnd,msg,wParam,lParam);
}
void EditorUI::RedirectIOToConsole()
{
	using namespace std;
	{
		int hConHandle;
		long lStdHandle;
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		FILE *fp;

		// allocate a console for this app
		AllocConsole();

		// set the screen buffer to be big enough to let us scroll text
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
		coninfo.dwSize.Y = MAX_CONSOLE_LINES;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);

		// redirect unbuffered STDOUT to the console
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

		fp = _fdopen(hConHandle,"w");

		*stdout = *fp;

		setvbuf(stdout,NULL,_IONBF,0);

		// redirect unbuffered STDIN to the console

		lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

		fp = _fdopen(hConHandle,"r");
		*stdin = *fp;
		setvbuf(stdin,NULL,_IONBF,0);

		// redirect unbuffered STDERR to the console
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

		fp = _fdopen(hConHandle,"w");

		*stderr = *fp;

		setvbuf(stderr,NULL,_IONBF,0);

		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
		// point to console as well
		ios::sync_with_stdio();
	}
}
#pragma region Add
HWND EditorUI::addEditor(HWND phWnd,std::string name,int x,int y,int width,int height,int groupID)
{
	HWND hWnd = CreateWindow(
		"STATIC",name.c_str(),
		WS_CHILD | WS_VISIBLE | WS_THICKFRAME,
		x,y,
		width,height,
		phWnd,
		(HMENU)groupID,
		Engine::Window.hInstance,
		NULL,
		);
	if(!prevWndEditor)
		prevWndEditor = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);

	SetWindowLong(hWnd,GWL_WNDPROC,(LONG_PTR)WndProcEditorFocus);
	return hWnd;
}
HWND EditorUI::addComponentGroup(HWND phWnd,std::string name,int x,int y,int width,int height,int groupID)
{
	HWND hWnd =
		CreateWindow
		(
		"STATIC",
		name.c_str(),
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		x,y,
		width,height,
		phWnd,
		(HMENU)groupID,
		Engine::Window.hInstance,
		NULL,
		);
	if(!prevWndProcGroup)
		prevWndProcGroup = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
	SetWindowLong(hWnd,GWL_WNDPROC,(LONG_PTR)WndProcComponent);
	return hWnd;
}
HWND EditorUI::addButton(HWND phWnd,std::string buttonDisplayName,int x,int y,int width,int height,int buttonID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"Button",
		buttonDisplayName.c_str(),
		BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		x,y,
		width,height,
		phWnd,
		(HMENU)buttonID,
		Engine::Window.hInstance,
		NULL
		);
	/*
	if(buttonID == 1337)
		prevWndButton = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);	
	if(buttonID == 1337)
		SetWindowLong(hWnd,GWL_WNDPROC,(LONG_PTR)WndProcButton);*/
	//*/
	return hWnd;
}
HWND EditorUI::addTextbox(HWND phWnd,std::string text,int x,int y,int width,int height,int textboxID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"Edit",
		text.c_str(),
		WS_VISIBLE | WS_CHILD|ES_AUTOHSCROLL,
		x,y,
		width,height,
		phWnd,
		(HMENU)textboxID,
		Engine::Window.hInstance,
		NULL
		);
	if(!prevWndText)
		prevWndText = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
	SetWindowLong(hWnd,GWL_WNDPROC,(LONG_PTR)WndProcText);
	return hWnd;
}
HWND EditorUI::addTextboxInt(HWND phWnd,std::string text,int x,int y,int width,int height,int textboxID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"Edit",
		text.c_str(),
		WS_VISIBLE | WS_CHILD | ES_NUMBER | ES_AUTOHSCROLL,
		x,y,
		width,height,
		phWnd,
		(HMENU)textboxID,
		Engine::Window.hInstance,
		NULL
		);
	if(!prevWndText)
		prevWndText = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
	SetWindowLong(hWnd,GWL_WNDPROC,(LONG_PTR)WndProcText);

	return hWnd;
}
HWND EditorUI::addLabel(HWND phWnd,std::string labelDisplay,int x,int y,int width,int height,int labelID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"static",
		labelDisplay.c_str(),
		WS_VISIBLE | WS_CHILD,
		x,y,
		width,height,
		phWnd,
		(HMENU)labelID,
		Engine::Window.hInstance,
		NULL
		);

	return hWnd;
}
#pragma endregion