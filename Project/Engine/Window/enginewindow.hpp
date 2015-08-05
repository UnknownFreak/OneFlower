#ifdef _DEBUG
#ifndef EngineWindow_HPP
#define EngineWindow_HPP
#include <Windows.h>
#include <map>
#include "../../Vector.h"
#include <string>
#include <SFML\Graphics\RenderWindow.hpp>
#include <vector>
#include "../Editor/EditorIDAssigner.hpp"
#include "Focus/EngineFocusWindow.hpp"
#include "../../Game/GameView.hpp"
#include "ListViewer/EngineObjectListViewer.hpp"
#include "Focus/EngineFocusWindow.hpp"
#include "Debug/EngineDebugWindow.hpp"
class GameObject;
class EngineWindow
{
public:
	EngineWindow();
	~EngineWindow();

	void setGameObject(GameObject* gameobject);
	void update();

	void setValue(BaseField* id,std::string value);

	void print(std::string);

	HINSTANCE hInstance;

	HWND hWnd;
	EngineObjectListViewer ListViewer;
	
	EngineFocus focus;

	EngineDebugWindow debug;

	EditorID editorID;


private:
	Vector2 size;

	std::vector<std::string> printList;
	LPCTSTR windowDefinedName;
	LPCTSTR titleBarDisplay;
	WNDCLASSEX wc;
	//HWND focus;
};
#endif
#endif