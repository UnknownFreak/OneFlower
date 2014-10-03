#ifndef CustomWindow_H
#define CustomWindow_H
#include <SFML\Graphics\RenderWindow.hpp>
#include <Windows.h>	
#include <map>
#include "Vector.h"
#include <string>
//Read Only
const sf::RenderWindow* RequestWindow();

//Returns a modifiyable pointer towards the main window
sf::RenderWindow* SetWindow();


class EditorWindow
{
public:
	EditorWindow();
	Vector2<int> size;
	HINSTANCE hInstance;
	HWND hWnd;
	std::map<int,HWND> controls;
	std::map<std::string,int> controlsID;
	HWND getAddon(int ID);
	HWND getAddon(std::string name);
private:
	LPCTSTR windowDefinedName;
	LPCTSTR titleBarDisplay;
	WNDCLASSEX wc;
};
EditorWindow* SetEditorWindow();

#endif