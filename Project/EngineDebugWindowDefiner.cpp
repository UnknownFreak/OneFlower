#ifdef _DEBUG
#include "EngineDebugWindow.hpp"
#include "Engine.hpp"
#include <Windows.h>
EngineDebugMessage::EngineDebugMessage(std::string str):msg(str)
{
}
void EngineDebugWindow::init(HWND phWnd)
{


	LPCTSTR windowDefinedName;
	LPCTSTR titleBarDisplay;
	WNDCLASSEX wc;

	windowDefinedName = "DebugWindow";
	titleBarDisplay = "Debug View";

	wc.lpszClassName = windowDefinedName;
	wc.lpfnWndProc = DefWindowProc;						// This function is called by windows
	wc.style = CS_HREDRAW | CS_VREDRAW;;							// Catch double-clicks
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	wc.hIconSm = 0;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszMenuName = NULL;					// No menu
	wc.cbClsExtra = 0;						// No extra bytes after the window class
	wc.cbWndExtra = 0;						// structure or the window instance
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	if(!RegisterClassEx(&wc))
		MessageBox(NULL,"Error Registering The DebugWindow Class","Error",MB_OK | MB_ICONERROR);





	hWnd = CreateWindowEx
		(
		0,		// Extended possibilites for variation
		"DebugWindow",				// Classname
		"Debug Window ",			// Title Text
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,	// default window
		0,
		0,							// Windows decides the position
		width,						// The programs width
		height,						// and height in pixels
		phWnd,						// The window is a child-window to desktop
		0,							// No menu
		Engine::Window.hInstance,	// Program Instance handler
		NULL						// No Window Creation data
		//this
		);



}
void EngineDebugWindow::print(std::string msg,int codeline,std::string filePath)
{
	EngineDebugMessage windowMsg(msg);
	size_t reversePos = filePath.rfind("\\");

	std::string nameOfFile(filePath.begin() + reversePos + 1,filePath.end());

	if(reversePos != std::wstring::npos)
	{
		std::string newMsg = msg + "\nCodeLine: " + std::to_string(codeline) + '\n' + nameOfFile;
		windowMsg.hWnd = CreateWindowEx
			(
			0,"STATIC",newMsg.c_str(),WS_CHILD | WS_VISIBLE | WS_BORDER,
			0,list.size()*messageSize,width - (GetSystemMetrics(SM_CXBORDER) + (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2)),(list.size() + 1)*messageSize,
			hWnd,(HMENU)123456789,Engine::Window.hInstance,NULL
			);
		if(windowMsg.hWnd)
			list.push_back(windowMsg);
		else
			MessageBox(0,std::string("Unable to add: " + msg).c_str(),"Unable to add Message to Debug Window",0);
	}
}

#endif