#ifdef _DEBUG
#include "EngineObjectListViewer.hpp"
#include "../../../Engine.hpp"
#include "../../../Game/Component/GameObject.h"
#include <Windows.h>
#include <vector>
EngineObjectListViewer::~EngineObjectListViewer()
{
	DestroyWindow(hWnd);
}
void EngineObjectListViewer::start()
{
	size.x = 256;
	size.y = 512;

	RECT window = EditorUI::GetLocalCoordinates(Engine::Window.hWnd);
	RECT screen = EditorUI::GetClientCoordinates(Engine::Window.hWnd);
	hWnd =
		CreateWindowEx(0,"LISTBOX","Object Viewer",
		WS_VISIBLE | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY | LBS_STANDARD,
		window.right - window.left - Engine::Window.focus.size.x - size.x - (GetSystemMetrics(SM_CXBORDER) + (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2)),0,
		size.x,size.y,
		Engine::Window.hWnd,NULL,Engine::Window.hInstance,NULL);
}
void EngineObjectListViewer::update()
{
	int index = SendMessage(hWnd,LB_GETCURSEL,0,0);
	if(index > -1)
	{
		GameObject* temp = (GameObject*)SendMessageA(hWnd,LB_GETITEMDATA,index,0);
		if(temp)
		{
			SendMessage(hWnd,LB_DELETESTRING,index,0);
			SendMessage(hWnd,LB_INSERTSTRING,index,(LPARAM)temp->name.c_str());
			SendMessage(hWnd,LB_SETITEMDATA,index,(LPARAM)temp);
			SendMessage(hWnd,LB_SETCURSEL,index,0);
		}
		else
			MessageBox(0,"NULL GameObject, From ListBox","CTRL+F 4328974",0);
	}
}
void EngineObjectListViewer::getSelection()
{
	int index = SendMessage(hWnd,LB_GETCURSEL,0,0);
	if(index > -1)
	{
		GameObject* temp = (GameObject*)SendMessageA(hWnd,LB_GETITEMDATA,index,0);
		if(temp)
			Engine::Window.setGameObject(temp);
		else
			MessageBox(0,"NULL GameObject, From ListBox","CTRL+F 4328974",0);
	}
	else
		MessageBox(0,"No Index, From ListBox","CTRL+F 4328974",0);
}
void EngineObjectListViewer::set(GameObject* t)
{
	std::vector<int> position;
	int count = SendMessage(hWnd,LB_GETCOUNT,0,0);
	for(size_t i = 0; i < count; ++i)
	{
		LRESULT l = SendMessage(hWnd,LB_GETTEXTLEN,(WPARAM)i,0);
		TCHAR* text = new char[l + 1];
		SendMessage(hWnd,LB_GETTEXT,(WPARAM)i,(LPARAM)text);
		if(t->name == text)
		{
			GameObject* temp = (GameObject*)SendMessageA(hWnd,LB_GETITEMDATA,i,0);
			if(temp == t)
			{
				SendMessage(hWnd,LB_SETCURSEL,i,0);
				delete text;
				break;
			}
		}
		delete text;
	}
}
void EngineObjectListViewer::add(GameObject* entity)
{
	if(entity)
	{
		int pos = -1;
		pos = SendMessage(hWnd,LB_ADDSTRING,-1,(LPARAM)entity->name.c_str());
		if(pos > -1)
		{
			order.push_back(entity);

			SendMessage(hWnd,LB_SETITEMDATA,(WPARAM)pos,(LPARAM)entity);
			SendMessage(hWnd,LB_SETCURSEL,pos,0);
		}
		else
			MessageBox(0,"Error adding strig","Ctrl+F 16455",0);
	}
}
void EngineObjectListViewer::remove(GameObject* t)
{
	std::vector<int> position;
	int count = SendMessage(hWnd,LB_GETCOUNT,0,0);
	for(size_t i = 0; i < count; ++i)
	{
		LRESULT l = SendMessage(hWnd,LB_GETTEXTLEN,(WPARAM)i,0);
		TCHAR* text = new char[l + 1];
		SendMessage(hWnd,LB_GETTEXT,(WPARAM)i,(LPARAM)text);
		if(t->name == text)
		{
			GameObject* temp = (GameObject*)SendMessageA(hWnd,LB_GETITEMDATA,i,0);
			if(temp == t)
			{
				SendMessage(hWnd,LB_DELETESTRING,i,0);
				delete text;
				break;
			}
		}
		delete text;
	}
}
#endif