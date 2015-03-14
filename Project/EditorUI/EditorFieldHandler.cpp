#ifdef _DEBUG
#include "EditorField.hpp"
#include "UIAddon.hpp"
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include "../Component/TransformComponent.hpp"
#include "../Component/HitboxComponent.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "EditorField.hpp"
#include "../Component/GameObject.h"
#include "../Component/RenderComponent.h"
#include "../Engine.hpp"
#include "EditorFieldGroup.hpp"
#include "SFML\Main.hpp"
void EditorUI::Field::addGroup(EditorGroup* name)
{

}
void EditorUI::Field::addField(BaseField* variable,EditorGroup* group,int _x,int _y)
{
	std::string value = "";
	int height = 16;
	const int space = 16;
	const int start = 32;
	int size = group->variableCount;

	int x = variable->name.size() * 8;
	int y = start + (space + 16) * size;

	 
	//Acts as a tab space
	if(x < 64)
		x = 64;

	//Extra padding
	x += 8;

	//variable->name[0] = variable->name[0] + ('A' - 'a');
	//0 = RequestID();

	//LOW: Keep adding diffrent types
	if(variable->getType() == EditorField<std::string>::type)
		#pragma region std::string
	{
		EditorField<std::string>* a = static_cast<EditorField<std::string>*>(variable);
		value = a->variable->c_str();
		size_t multi = value.find("\n");
		size_t multiNigo = value.find("\\n");
		if(multi == std::string::npos && multiNigo == std::string::npos)
			variable->hWnd = Engine::Window.focus.addTextbox(group->hWnd,value,x,y,128,height,0);
		else
		{
			if(multi != std::string::npos)
			{
				value.replace(multi,std::string("\n").length(),"\\n");
			}
			variable->hWnd = Engine::Window.focus.addTextboxMulti(group->hWnd,value,x,y,128,height + 16,0);

		}
		group->field.insert(std::make_pair(variable->hWnd,a));
	}
#pragma endregion
	else if(variable->getType() == EditorField<int>::type)
		#pragma region int
	{
		EditorField<int>* a = static_cast<EditorField<int>*>(variable);
		value = std::to_string(*a->variable);
		variable->hWnd = Engine::Window.focus.addTextboxInt(group->hWnd,value,x,y,64,height,0);
		variable->flags = FieldFlag::Numbers_Only;
		group->field.insert(std::make_pair(variable->hWnd,a));
	}
#pragma endregion
	else if(variable->getType() == EditorField<Vector2>::type)
		#pragma region Vector2
	{
		//y = start + (space + 16) * size / 2;
		EditorField<Vector2>* a = static_cast<EditorField<Vector2>*>(variable);
		EditorField<double>* varX = new EditorField<double>(&a->variable->x,a->name + ".x");
		EditorField<double>* varY = new EditorField<double>(&a->variable->y,a->name + ".y");
		std::string valueNigo = "";

		value = std::to_string(a->variable->x);
		valueNigo = std::to_string(a->variable->y);


		//variable->hWnd = addComponentGroup(group->hWnd,"",0,y,width,height +4,0);
		//variable->label = addLabel(group->hWnd,variable->name,0,0,width,16,RequestID());

		////Variable name 
		//varX->ID = RequestID();
		//varY->ID = RequestID();

		varX->hWnd = Engine::Window.focus.addTextbox(group->hWnd,value,x,y,64,height,0);
		varY->hWnd = Engine::Window.focus.addTextbox(group->hWnd,valueNigo,x + 64 + 8,y,64,height,0);


		varX->flags = FieldFlag::Decimal | FieldFlag::Left;
		varY->flags = FieldFlag::Decimal | FieldFlag::Right;


		varX->variable = &a->variable->x;
		varY->variable = &a->variable->y;

		varX->holder = a->holder;
		varY->holder = a->holder;

		group->field.insert(std::make_pair(varX->hWnd,varX));
		group->field.insert(std::make_pair(varX->hWnd,varY));
		//group->variableCount++;

	}
	#pragma endregion
	else if(variable->getType() == EditorField<bool>::type)
	{
		#pragma region bool
	{
		EditorField<bool>* a = static_cast<EditorField<bool>*>(variable);
		variable->hWnd = CreateWindowEx(0,"BUTTON",a->name.c_str(),WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX ,x,y,64,height,group->hWnd,0,Engine::Window.hInstance,0);
		if(a->variable)
			SendMessageA(variable->hWnd,BM_SETCHECK,BST_CHECKED,0);
		
		value = "Bool";
		group->field.insert(std::make_pair(variable->hWnd,a));
	}
		#pragma endregion

	}
	if(!value.empty())
	{
		group->variableCount++;
		variable->label = Engine::Window.focus.addLabel(group->hWnd,variable->name,0,y,variable->name.size() * 8,height,0);
	}
	#pragma endregion
}



#endif