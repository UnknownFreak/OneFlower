#ifndef MainEditorWindow_HPP
#define MainEditorWindow_HPP
#ifdef _EDITOR_
//#include "ParentWindowWrapper.hpp"
#include <Windows.h>
ref class MainEditorWindow
{
	EditorResources::Windows::EditorWindow^ window;

	System::IntPtr^ windowhandle;

public:

	HWND getEditorGameWindowView();
	
	void show();
	bool isClosed();
	MainEditorWindow();
	MainEditorWindow(const MainEditorWindow% window);
	~MainEditorWindow();

};


#endif
#endif