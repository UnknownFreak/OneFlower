#ifndef EngineWindow_HPP
#define EngineWindow_HPP
#include <Windows.h>	
#include <map>
#include "Vector.h"
#include <string>
#include <SFML\Graphics\RenderWindow.hpp>
#include "EditorUI\EditorField.hpp"	
#include <vector>
class GameObject;
class EngineWindow
{
public:
	EngineWindow();
	~EngineWindow();

	void setGameObject(GameObject* gameobject);
	void cleanse();

	void update();


//	void setValue(BaseField* var,std::string value);
	void setValue(BaseField* id,std::string value);

	void print(std::string);
	
	HINSTANCE hInstance;
	sf::RenderWindow View;

	//All component group, not to be confused with the control fields inside EditorGroup
	std::map<std::string,EditorGroup> fieldGroup;
	HWND hWnd;

	bool focus = true;

	GameObject* focusedGameObject = NULL;

	//std::map<std::string,HWND> Fields;
private:
	std::vector<std::string> printList;
	Vector2 size;
	Vector2 viewPosition;
	HWND viewport;
	LPCTSTR windowDefinedName;
	LPCTSTR titleBarDisplay;
	WNDCLASSEX wc;
	HWND focusWindow;

};
#endif