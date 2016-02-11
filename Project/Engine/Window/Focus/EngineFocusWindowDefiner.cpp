#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include "EngineFocusWindow.hpp"
#include "../../../Engine.hpp"
#include "../../Editor/UIAddon.hpp"
#include "../../../Game/Component/TransformComponent.hpp"
#include "../../../Game/Component/HitboxComponent.hpp"
#include "../../Editor/EditorField.hpp"
#include "../../Editor/EditorFieldGroup.hpp"
#include "../../../Game/Component/GameObject.h"
#include "../../../Game/Component/RenderComponent.h"
#include "../../../Engine.hpp"
#include "../../Resource.h"
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


WNDPROC prevWndEditor;
WNDPROC prevWndText;
WNDPROC prevWndComponentGroup;
WNDPROC prevWndTextMulti;

LRESULT CALLBACK WndProcEditorFocus(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK WndProcNameField(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK WndProcComponentGroup(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);


bool isDouble(char a);
std::string isLetter(std::string line);




EngineFocus::EngineFocus():size(256,500)
{
	windowDefinedName = "EngineFocus";
	titleBarDisplay = "EngineFocus";
	wc = {0};
	//The First Windows structure
	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = WndProcEditorFocus;						// This function is called by windows
	wc.style = CS_HREDRAW | CS_VREDRAW;;							// Catch double-clicks
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	wc.hIconSm = 0;//LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszMenuName = NULL;//MAKEINTRESOURCE(MENU_ID);;							// No menu
	wc.cbClsExtra = 0;														// No extra bytes after the window class
	wc.cbWndExtra = 0;														// structure or the window instance
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);;

	//wc.hInstance = hInst;
	//wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);;
	if(!RegisterClassEx(&wc))
		MessageBox(NULL,"Error Registering The Window Class","Error",MB_OK | MB_ICONERROR);

	wc.lpszClassName = "EngineComponentGroup";
	wc.lpfnWndProc = WndProcComponentGroup;						// This function is called by windows
	wc.style = CS_HREDRAW | CS_VREDRAW;;							// Catch double-clicks
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	wc.hIconSm = 0;//LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszMenuName = NULL;//MAKEINTRESOURCE(MENU_ID);;							// No menu
	wc.cbClsExtra = 0;														// No extra bytes after the window class
	wc.cbWndExtra = 0;														// structure or the window instance
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);;
	if(!RegisterClassEx(&wc))
		MessageBox(NULL,"Error Registering The Window Class","Error",MB_OK | MB_ICONERROR);
}
void EngineFocus::start()
{
	HWND apa = Engine::Window.hWnd;
	//TheEngine Window
	RECT window = EditorUI::GetLocalCoordinates(apa);
	//Monitor Screens
	RECT screen = EditorUI::GetClientCoordinates(apa);
	//TheEngine Window border thickness. The thing that you use to resize
	int border_thickness = ((screen.right - screen.left) - (window.right - window.left)) / 2;

	//The focused window of the selectd game object
	hWnd = addEditor(apa,"",window.right - window.left - 256 - 16,0,size.x,size.y,0);
	hWndField = Engine::Window.focus.addTextbox(hWnd,"startEmpty",std::string("Name: ").size() * 8,0,8 * 12,16,0);
	nameField = new EditorField<std::string>(0,std::string("Empty"));
	nameField->hWnd = hWndField;
	nameField->name = "GameObject FieldName";
	nameField->label = addLabel(hWnd,"Name: ",0,0,std::string("Name: ").size() * 8,16,0);

	extraFields.insert(std::make_pair(hWndField,nameField));
	SetWindowLong(hWndField,GWL_WNDPROC,(LONG_PTR)WndProcNameField);
	EnableWindow(hWndField,false);
}
void EngineFocus::cleanse()
{
#pragma region ResetScrolling
	SCROLLINFO sia = {sizeof(SCROLLINFO),SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS,0,0,0,0,0};
	GetScrollInfo(hWnd,SB_VERT,&sia);
	if(sia.nPos > 0)
	{
		ScrollWindowEx(hWnd,0,sia.nPos,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
	}
	sia.nPos = 0;
	SetScrollInfo(hWnd,SB_VERT,&sia,false);

#pragma endregion

#pragma region CleanseChildhWnd
	for(auto it = componentFieldGroup.begin(); it != componentFieldGroup.end(); it++)
	{
		for(auto jt = it->second.field.begin(); jt != it->second.field.end(); jt++)
		{
			DestroyWindow(jt->second->label);
			DestroyWindow(jt->second->hWnd);
		}
		DestroyWindow(it->second.hWnd);
	}
	componentFieldGroup.clear();
	EnableWindow(hWndField,false);
#pragma endregion
}

RECT EditorUI::GetLocalCoordinates(HWND hWnd)
{
	RECT Rect;
	GetWindowRect(hWnd,&Rect);
	MapWindowPoints(HWND_DESKTOP,GetParent(hWnd),(LPPOINT)&Rect,2);
	//Rect.right -= Rect.left;
	return Rect;
}
RECT EditorUI::GetClientCoordinates(HWND hWnd)
{
	RECT Rect;
	GetWindowRect(hWnd,&Rect);
	return Rect;
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
std::string isLetter(std::string line)
{
	std::string newValue;
	char c;
	for(int i = 0; i < line.length(); i++)
	{
		c = line.at(i);
		if(
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '.' ||
			c == '!' ||
			c == '\n' ||
			c == '\\'
			)
		{
			newValue.push_back(c);
		}
	}
	return newValue;
}

#pragma region WndProc

LRESULT CALLBACK WndProcComponentGroup(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_COMMAND:
		{
			int a = HIWORD(wParam);
			int b = BN_CLICKED;
			switch(HIWORD(wParam))
			{
				#pragma region BN_CLICKED
				case BN_CLICKED:
				{
					for(auto it = Engine::Window.focus.componentFieldGroup.begin(); it != Engine::Window.focus.componentFieldGroup.end(); ++it)
					{
						auto jit = it->second.field.find((HWND)lParam);
						if(jit != it->second.field.end())
						{
							EditorField<bool>* field = static_cast<EditorField<bool>*>(jit->second);
							if(*field->variable)
								Engine::Window.setValue(field,"false");
							else
								Engine::Window.setValue(field,"true");

							break;
						}
					}
					//*/
					break;
				}
				#pragma endregion
			}
		}
		default:
			break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}

//The Callback for the: Text field for Game Object names inside Focus Window when selecting a GameObject
LRESULT CALLBACK WndProcNameField(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CHAR:
		{
			switch(wParam)
			{
				default:
					//case(VK_RETURN) :
#pragma region Enter WndProcNameField
				{
					TCHAR txt[1024];
					DWORD start = 0;
					DWORD end = 0;
					GetWindowText(hWnd,txt,1024);
					std::string value(txt);
					std::string newValue = "";
					SendMessage(hWnd,EM_GETSEL,reinterpret_cast<WPARAM>(&start),reinterpret_cast<WPARAM>(&end));

					//TODO: Move this out towards a seperate WndProc
					//Field Object
#pragma region SearchFields
					std::map<HWND,BaseField*>::iterator it = Engine::Window.focus.extraFields.find(hWnd);
#pragma endregion
					//try .end one day
					if(it != Engine::Window.focus.extraFields.end())
					{
						if(value.empty())
							newValue = '0';
						else
							newValue = value;
						SetWindowTextA(hWnd,newValue.c_str());
						SendMessage(hWnd,EM_SETSEL,start,end);
						Engine::Window.setValue(it->second,newValue);
						Engine::Window.ListViewer.update();
					}
					else
						MessageBoxA(0,"Unknown HWND Inside ExtraFields, Please Modify SearchArea Region","CTRL + F: No FocusWindow/field",0);
					break;
				}

#pragma endregion
				//*/
			}
		}
		default:
			break;
	}
	return CallWindowProc(prevWndText,hWnd,msg,wParam,lParam);
}
LRESULT CALLBACK WndProcText(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//LOW: Set a limit of char to TextBox
	switch(msg)
	{
		#pragma region WM_Char
				case WM_CHAR:
				{
					switch(wParam)
					{
						#pragma region Non-CharKey
						// Process a backspace.
						case VK_BACK:

						#pragma region Number
							//0-9
						case 0x30:
						case 0x31:
						case 0x32:
						case 0x33:
						case 0x34:
						case 0x35:
						case 0x36:
						case 0x37:
						case 0x38:
						case 0x39:
						case 0x60:

						#pragma endregion
						#pragma region Numpad
							/*
						//Numpad 0-9
						case 0x61:
						case 0x62:
						case 0x63:
						case 0x64:
						case 0x65:
						case 0x66:
						case 0x67:
						case 0x68:
						case 0x69:
							//*/
						#pragma endregion
						{
							TCHAR text[1024];
							CallWindowProc(prevWndText,hWnd,msg,wParam,lParam);
							GetWindowText(hWnd,text,1024);

							std::string value(text);
							std::map<HWND,BaseField*>::iterator it;// = Engine::Window.focus.extraFields.find(hWnd);

							for(std::map<std::string,EditorGroup>::iterator i = Engine::Window.focus.componentFieldGroup.begin(); i != Engine::Window.focus.componentFieldGroup.end(); i++)
							{
								it = i->second.field.find(hWnd);
								if(it != i->second.field.end())
									break;
							}
							
							Engine::Window.setValue(it->second,value);

							return 0;
						}




						#pragma endregion
						
						default:
							return 0;
							
					}
				#pragma region Enter
							/*
							{
							TCHAR txt[1024];
							DWORD start = 0;
							DWORD end = 0;
							char newTempInput = wParam;

							GetWindowText(hWnd,txt,1024);
							std::string value(txt);
							std::string newValue = "";

							SendMessage(hWnd,EM_GETSEL,reinterpret_cast<WPARAM>(&start),reinterpret_cast<WPARAM>(&end));
							//TODO: Move this out towards a seperate WndProc
							//Field Object
							#pragma region SearchFields
							bool found = false;
							std::map<HWND,BaseField*>::iterator it;// = Engine::Window.focus.extraFields.find(hWnd);
							for(std::map<std::string,EditorGroup>::iterator i = Engine::Window.focus.componentFieldGroup.begin(); i != Engine::Window.focus.componentFieldGroup.end(); i++)
							{
							it = i->second.field.find(hWnd);
							if(it != i->second.field.end())
							{
							found = true;
							break;
							}
							}
							#pragma endregion
							//try .end one day
							if(found)
							{
							if(!value.empty())
							{
							if(it->second->flags & FieldFlag::Decimal)
							{
							#pragma region Decimal
							for(size_t i = 0; i < value.size(); i++)
							if(isDouble(value.at(i)))
							newValue.push_back(value[i]);
							if(!newValue.empty())
							if(value[0] == '-')
							newValue.insert(newValue.begin(),value[0]);
							else
							newValue = "0";
							#pragma endregion
							}
							else
							newValue = isLetter(value);
							}
							else
							newValue = '0';

							if(wParam == VK_BACK)
							value.erase(value.begin() + //start,value.begin() +
							end);
							else
							newValue.insert(start,1,newTempInput);
							SendMessage(hWnd,EM_SETSEL,start,end);

							Engine::Window.setValue(it->second,newValue);
							}
							else
							MessageBoxA(0,"Unknown HWND, Please Modify SearchArea Region","CTRL + F: TextField_Variable WndProc_Text",0);
							break;
							//return 0;
							}
							//*/
				#pragma endregion
				}
		#pragma endregion
		#pragma region WM_Command
				case WM_COMMAND:
				{
		#pragma region EN_Change
				case EN_CHANGE:
				{
					break;
				}

				/*case EN_CHANGE:
				{
				TCHAR txt[1024],txt2[1024];
				DWORD start = 0;
				DWORD end = 0;
				GetWindowText(hWnd,txt,1024);
				SendMessage(hWnd,EM_GETLINE,(WPARAM)0,(LPARAM)txt2);

				std::string value(txt);
				std::string newValue = "";
				std::string newValue2(txt2);

				std::map<HWND,BaseField*>::iterator it;
				if(!value.empty())
				{
				for(size_t i = 0; i < value.size(); i++)
				if(isDouble(value.at(i)))
				newValue.push_back(value[i]);
				if(!newValue.empty())
				if(value[0] == '-')
				newValue.insert(newValue.begin(),value[0]);
				else
				newValue = "0";

				//SendMessage(hWnd,EM_SETSEL,start,end);
				//SendMessage(hWnd,EM_REPLACESEL,0,(LPARAM)((LPSTR)newValue.c_str()));
				SetWindowTextA(hWnd,newValue.c_str());
				Engine::Window.setValue(it->second,newValue);
				}
				break;
				}
				//*/

		#pragma endregion
				}
		#pragma endregion

		default:
			break;
	}
	return 	CallWindowProc(prevWndText,hWnd,msg,wParam,lParam);

}
LRESULT CALLBACK WndProcEditorFocus(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		// User clicked the scroll bar shaft left of the scroll box.
		case WM_VSCROLL:
		{
			SCROLLINFO si = {sizeof(SCROLLINFO),SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS,0,0,0,0,0};
			GetScrollInfo(hWnd,SB_VERT,&si);
			int scrollSpeed = 16;
			#pragma region wParam
			switch(wParam)
			{
				#pragma region SB_PAGEUP
				case SB_PAGEUP:
				{
					scrollSpeed = -64;
					//Negative + Negative = Positive
					if(si.nPos + scrollSpeed >= 0)
					{
						ScrollWindowEx(hWnd,0,-scrollSpeed,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos += scrollSpeed;
					}
					else
					{
						ScrollWindowEx(hWnd,0,si.nPos,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos -= si.nPos;
					}
					SetScrollInfo(hWnd,SB_VERT,&si,false);
					break;
				}
				#pragma endregion
				#pragma region SB_PAGEDOWN
				case SB_PAGEDOWN:
				{
					scrollSpeed = 64;
					if(si.nPos + scrollSpeed <= si.nMax)
					{
						ScrollWindowEx(hWnd,0,-scrollSpeed,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos += scrollSpeed;
					}
					else
					{
						ScrollWindowEx(hWnd,0,-(si.nMax - si.nPos),NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos += (si.nMax - si.nPos);
					}
					SetScrollInfo(hWnd,SB_VERT,&si,false);
					break;
				}
				#pragma endregion
				#pragma region SB_LINEUP
				case SB_LINEUP:
				{
					scrollSpeed = -16;
					//Negative + Negative = Positive
					if(si.nPos + scrollSpeed >= 0)
					{
						ScrollWindowEx(hWnd,0,-scrollSpeed,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos += scrollSpeed;
					}
					else
					{
						ScrollWindowEx(hWnd,0,si.nPos,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos -= si.nPos;
					}
					SetScrollInfo(hWnd,SB_VERT,&si,false);

					break;
				}
				#pragma endregion
				#pragma region SB_LINEDOWN
				case SB_LINEDOWN:
				{
					//LOW: Figure out why -scrollSpeed -> scrollSpeed and si.nPos - scrollSpeed <- si.nPos + scrollSpeed doesnt work?
					scrollSpeed = 16;
					if(si.nPos + scrollSpeed <= si.nMax)
					{
						ScrollWindowEx(hWnd,0,-scrollSpeed,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos += scrollSpeed;
					}
					else
					{
						ScrollWindowEx(hWnd,0,-(si.nMax - si.nPos),NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
						si.nPos += (si.nMax - si.nPos);
					}
					SetScrollInfo(hWnd,SB_VERT,&si,false);
					break;
				}
				#pragma endregion

				/*
				case SB_THUMBPOSITION:
				{
				int move = HIWORD(wParam);
				si.nPos = move;
				SetScrollInfo(hWnd,SB_VERT,&si,false);

				break;
				}
				//*/
				default:
					break;
			}
			#pragma endregion
		}
		case WM_MOUSEACTIVATE:
		{
			SetFocus(hWnd);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			SCROLLINFO si = {sizeof(SCROLLINFO),SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS,0,0,0,0,0};
			GetScrollInfo(hWnd,SB_VERT,&si);

			int wheelTicks = GET_WHEEL_DELTA_WPARAM(wParam);// / WHEEL_DELTA;
			int scrollSpeed = wheelTicks;
			if(wheelTicks > 0)
			{
				//Wheel UP,Content Go DOWN
				#pragma region SB_LINEUP
				scrollSpeed = -16;
				//Negative + Negative = Positive
				if(si.nPos + scrollSpeed >= 0)
				{
					ScrollWindowEx(hWnd,0,-scrollSpeed,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
					si.nPos += scrollSpeed;
				}
				else
				{
					ScrollWindowEx(hWnd,0,si.nPos,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
					si.nPos -= si.nPos;
				}
				#pragma endregion
			}
			else
			{
				//Wheel Down, Content go UP
				#pragma region SB_LINEDOWN
				scrollSpeed = 16;
				if(si.nPos + scrollSpeed <= si.nMax)
				{
					ScrollWindowEx(hWnd,0,-scrollSpeed,NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
					si.nPos += scrollSpeed;
				}
				else
				{
					ScrollWindowEx(hWnd,0,-(si.nMax - si.nPos),NULL,NULL,NULL,0,SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
					si.nPos += (si.nMax - si.nPos);
				}
				#pragma endregion
			}

			SetScrollInfo(hWnd,SB_VERT,&si,false);

			break;
		}
		default:
		{
			break;
		}
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}

/*
LRESULT CALLBACK WndProcTextMulti(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
switch(msg)
{
case WM_CHAR:
{
switch(wParam)
{
#pragma region VK_RETURN
case(VK_RETURN) :
{
TCHAR txt[1024];
DWORD start = 0;
DWORD end = 0;
int id = GetWindowLong(hWnd,GWL_ID);
SendMessage(hWnd,EM_GETSEL,reinterpret_cast<WPARAM>(&start),reinterpret_cast<WPARAM>(&end));
GetWindowText(hWnd,txt,1024);
std::string value(txt);
std::string newValue = "";

std::map<int,BaseField*>::iterator it;
for(auto i = Engine::Window.focus.componentFieldGroup.begin(); i != Engine::Window.focus.componentFieldGroup.end(); i++)
{
it = i->second.field.find(id);
if(it != i->second.field.end())
break;
}
if(!value.empty())
{
newValue = isLetter(value);
}
else
newValue = "";
SetWindowTextA(hWnd,newValue.c_str());
SendMessage(hWnd,EM_SETSEL,start,end);
Engine::Window.setValue(it->second,newValue);
break;
}
#pragma endregion
default:
break;
}
}
default:
break;
}
return CallWindowProc(prevWndTextMulti,hWnd,msg,wParam,lParam);
}
//*/
#pragma endregion
#pragma region Add HWND
HWND EngineFocus::addEditor(HWND phWnd,std::string name,int x,int y,int width,int height,int groupID)
{
	HWND hWnd = CreateWindowEx
		(
		WS_EX_CONTROLPARENT,		// Extended possibilites for variation
		windowDefinedName,			// Classname
		titleBarDisplay,			// Title Text
		LBS_DISABLENOSCROLL | WS_VISIBLE | WS_THICKFRAME | WS_VSCROLL,	// default window
		x,							// Windows decides the position
		y,							// where the window ends up on the screen
		width,						// The programs width
		height,						// and height in pixels
		phWnd,						// The window is a child-window to desktop
		NULL,						// No menu
		Engine::Window.hInstance,	// Program Instance handler
		NULL						// No Window Creation data
		//this
		);

	//ShowWindow(hWnd,1);

	/*
	if(!prevWndEditor)
	prevWndEditor = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);

	SetWindowLong(hWnd,GWL_WNDPROC,(LONG_PTR)WndProcEditorFocus);
	//*/
	return hWnd;
}

/*
HWND EngineFocus::addComponentGroup(HWND phWnd,std::string name,int x,int y,int width,int height,int groupID)
{
HWND hWnd =
CreateWindowEx
(
0,
"EngineFocus",
name.c_str(),
WS_VISIBLE | WS_BORDER | WS_TABSTOP,
x,y,
width,height,
phWnd,
(HMENU)groupID,
Engine::Window.hInstance,
NULL
);

return hWnd;
}

//*/
HWND EngineFocus::addButton(HWND phWnd,std::string buttonDisplayName,int x,int y,int width,int height,int buttonID)
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
	return hWnd;
}
HWND EngineFocus::addTextbox(HWND phWnd,std::string text,int x,int y,int width,int height,int textboxID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"Edit",
		text.c_str(),
		WS_VISIBLE | WS_CHILD | WS_TABSTOP,
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
HWND EngineFocus::addTextboxInt(HWND phWnd,std::string text,int x,int y,int width,int height,int textboxID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"Edit",
		text.c_str(),
		WS_VISIBLE | WS_CHILD | ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP,
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
HWND EngineFocus::addTextboxMulti(HWND phWnd,std::string text,int x,int y,int width,int height,int textboxID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"Edit",
		text.c_str(),
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		x,y,
		width,height,
		phWnd,
		(HMENU)textboxID,
		Engine::Window.hInstance,
		NULL
		);
	if(!prevWndTextMulti)
		prevWndTextMulti = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
	//SetWindowLong(hWnd,GWL_WNDPROC,(LONG_PTR)WndProcTextMulti);
	return hWnd;
}
HWND EngineFocus::addLabel(HWND phWnd,std::string labelDisplay,int x,int y,int width,int height,int labelID)
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

/*void EngineFocus::addExtraField(HWND phWnd,std::string text,BaseField* theVariable,int x,int y,intwidth,int height)
{
	addLabel(hWnd,text,0,0,text.size() * 8,16,0);
	hWndField = CreateWindowExA(0,"edit",text.c_str(),WS_VISIBLE | WS_CHILD | WS_TABSTOP,x,y,width,height,phWnd,0,Engine::Window.hInstance,0);
	extraFields.insert(std::make_pair(hWndField,theVariable));
	SetWindowLong(hWndField,GWL_WNDPROC,(LONG_PTR)WndProcNameField);
}
//*/

// maximum mumber of lines the output console should have
//static const WORD MAX_CONSOLE_LINES = 500;
/*
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
//*/