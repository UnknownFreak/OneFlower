#ifdef _DEBUG
#ifndef ENGINEQUESTCREATORWINDOW_HPP
#define ENGINEQUESTCREATORWINDOW_HPP
#include <Windows.h>
#include "../../../Vector.h"
class EngineQuestCreator
{
public:

	HINSTANCE hInstance;
	HWND hWnd;

	~EngineQuestCreator();
	//EngineItemCreator() = default;
	void start();
	void show();

private:

	Vector2 size;
	WNDCLASSEX wc;
	LPCTSTR windowDefinedName;
};


#endif
#endif