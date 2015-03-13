#ifndef EditorFieldGroup_HPP
#define EditorFieldGroup_HPP

#include <Windows.h>
#include <string>
#include <map>
#include "../Vector.h"
class BaseField;
class EditorGroup
{
public:
	//The Group Window
	HWND hWnd;

	//The Component name
	std::string name;	

	//The Name Label
	HWND label;

	//All the variable field
	std::map<int,BaseField*> field;

	Vector2 position;

	int scrollSize = 0;

	//Remove this and just use field.size
	int variableCount = 0;
};
#endif