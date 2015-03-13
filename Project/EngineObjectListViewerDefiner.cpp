#ifdef _DEBUG
#include "EngineObjectListViewer.hpp"
#include "Engine.hpp"
#include "Component\GameObject.h"
#include <Windows.h>
void EngineObjectListViewer::start()
{
	RECT window = EditorUI::GetLocalCoordinates(Engine::Window.hWnd);
	RECT screen = EditorUI::GetClientCoordinates(Engine::Window.hWnd); 
	hWnd =
		CreateWindowEx(0,"LISTBOX","Object Viewer",
		WS_VISIBLE|WS_CHILDWINDOW | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY | LBS_STANDARD,
		window.right - window.left - 256*2 - 16,0,
		256,500,
		Engine::Window.hWnd,NULL,Engine::Window.hInstance,NULL);
}
EngineObjectListViewer::~EngineObjectListViewer()
{
	DestroyWindow(hWnd);
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
#endif