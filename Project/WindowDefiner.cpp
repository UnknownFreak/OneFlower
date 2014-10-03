#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include "Vector.h"
#include"CustomWindow.h"
#define SaveButtonID 1001
#define TransformTextBoxID 2001
#define TransformLabelID 3001
#pragma region Prototypes
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void addButton(HWND phWnd,std::string buttonDisplayName,Vector2<int> position,Vector2<int> size,int buttonID);
void addTextbox(HWND phWnd,std::string textBoxName,Vector2<int> position,Vector2<int> size,int textboxID);
void addLabel(HWND phWnd,std::string labelDisplay,std::string labelName,Vector2<int> position,Vector2<int> size,int labelID);
void addTextboxInt(HWND phWnd,std::string number,Vector2<int> position,Vector2<int> size,int textboxID);
#pragma endregion

EditorWindow::EditorWindow():size(800,600)
{
	/*
	size.x = 800;
	size.y = 600;
	//*/
	windowDefinedName= "EditorWindow";
	titleBarDisplay = "Editor Window";
	
    //The First Windows structure 
	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = WndProc;						// This function is called by windows 
    wc.style = CS_DBLCLKS;							// Catch double-clicks 
    wc.cbSize = sizeof (WNDCLASSEX);
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;							// No menu 
    wc.cbClsExtra = 0;								// No extra bytes after the window class 
    wc.cbWndExtra = 0;								// structure or the window instance 
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);;
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL,"Error Registering The Window Class","Error",MB_OK | MB_ICONERROR);
	}
	hWnd =  CreateWindowEx
						(
							0,						// Extended possibilites for variation 
							windowDefinedName,		// Classname 
							titleBarDisplay,			// Title Text
							WS_OVERLAPPEDWINDOW,		// default window 
							CW_USEDEFAULT,			// Windows decides the position 
							CW_USEDEFAULT,			// where the window ends up on the screen 
							size.x,					// The programs width 
							size.y,					// and height in pixels 
							NULL,					// The window is a child-window to desktop 
							NULL,					// No menu
							hInstance,				// Program Instance handler
							NULL						// No Window Creation data 
							//this							
						);
	if (!hWnd)
	{
		MessageBox(NULL, "Error creating window","Error", MB_OK | MB_ICONERROR);
	}	
	else
	{
		ShowWindow(hWnd,1);
		UpdateWindow(hWnd);
	}
}


HWND EditorWindow::getAddon(int ID)
{
	std::map<int,HWND>::iterator it;
	it = this->controls.find(ID);
	if(it != controls.end())
	{
		return it->second;
	}
	return NULL;
}
HWND EditorWindow::getAddon(std::string ID)
{
	std::map<std::string,int>::iterator it;
	it = this->controlsID.find(ID);
	if(it != controlsID.end())
	{
		return getAddon(it->second);
	}
	return NULL;
}













LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)	
	{	
		case WM_CREATE:
		{
	
			Vector2<int> size;
			Vector2<int> position;
			#pragma region Save Prefab
			size.x = 128;
			size.y = 32;
			position.x = 800 - size.x - 6;
			position.y = 0 + size.y;
			addButton(hWnd,"Save Prefab",position,size,SaveButtonID);
			#pragma endregion
			#pragma region Transform Label
			position.x = 0;
			size.y = 16;
			size.x = 128;
			addLabel(hWnd,"Transform:","TransformLabel",position,size,TransformLabelID);
			
			size.x = 16;
			position.y += 16+8;
			addLabel(hWnd,"x:","TransformLabelX",position,size,TransformLabelID + 1);

			position.y += 16+8;
			addLabel(hWnd,"y:","TransformLabelY",position,size,TransformLabelID + 2);

			position.y += 16+8;
			addLabel(hWnd,"z:","TransformLabelZ",position,size,TransformLabelID + 2);
			#pragma endregion

			size.x = 64;
			size.y = 16;
			position.x = 12;
			position.y -= 3 * (16 + 8);
			position.y += 16 + 8;
			addTextboxInt(hWnd,"TransformBoxX",position,size,TransformTextBoxID + 1);
			position.y += 16 + 8;
			addTextboxInt(hWnd,"TransformBoxY",position,size,TransformTextBoxID + 2);
			position.y += 16 + 8;
			addTextboxInt(hWnd,"TransformBoxZ",position,size,TransformTextBoxID + 3);
		
		//*/
		}
		case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				DestroyWindow(hWnd);	
			}
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
					
		}
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}











#pragma region Add
void addButton(HWND phWnd,std::string buttonDisplayName,Vector2<int> position,Vector2<int> size,int buttonID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
			0,
			"Button",
			buttonDisplayName.c_str(),
			BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
			position.x,
			position.y,
			size.x,
			size.y,
			phWnd,
			(HMENU)buttonID,
			NULL,
			NULL
		);
	SetEditorWindow()->controls.insert(SetEditorWindow()->controls.end(),std::pair<int,HWND>(buttonID,hWnd));
	SetEditorWindow()->controlsID.insert(SetEditorWindow()->controlsID.end(),std::pair<std::string,int>(buttonDisplayName,buttonID));;
}
void addTextbox(HWND phWnd,std::string textBoxName,Vector2<int> position,Vector2<int> size,int textboxID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
			0,
			"Edit",
			"",
			WS_VISIBLE | WS_CHILD,
			position.x,
			position.y,
			size.x,
			size.y,
			phWnd,
			(HMENU)textboxID,
			NULL,
			NULL
		);
	SetEditorWindow()->controls.insert(SetEditorWindow()->controls.end(),std::pair<int,HWND>(textboxID,hWnd));
	SetEditorWindow()->controlsID.insert(SetEditorWindow()->controlsID.end(),std::pair<std::string,int>(textBoxName,textboxID));;
}
void addLabel(HWND phWnd,std::string labelDisplay,std::string labelName,Vector2<int> position,Vector2<int> size,int labelID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
			0,
			"static",
			labelDisplay.c_str(),
			WS_VISIBLE | WS_CHILD,
			position.x,
			position.y,
			size.x,
			size.y,	
			phWnd,
			(HMENU)labelID,
			NULL,
			NULL
		);
		SetEditorWindow()->controls.insert(SetEditorWindow()->controls.end(),std::pair<int,HWND>(labelID,hWnd));
		SetEditorWindow()->controlsID.insert(SetEditorWindow()->controlsID.end(),std::pair<std::string,int>(labelName,labelID));;
}
void addTextboxInt(HWND phWnd,std::string number,Vector2<int> position,Vector2<int> size,int textboxID)
{
	HWND hWnd;
	hWnd = CreateWindowEx
		(
		0,
		"Edit",
		"",
		WS_VISIBLE | WS_CHILD | ES_NUMBER,
		position.x,
		position.y,
		size.x,
		size.y,
		phWnd,
		(HMENU)textboxID,
		NULL,
		NULL
		);
	SetEditorWindow()->controls.insert(SetEditorWindow()->controls.end(),std::pair<int,HWND>(textboxID,hWnd));


}
#pragma endregion