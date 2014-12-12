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
std::map<std::string,std::map<std::string,std::string>> EditorUI:: compiledClass;

void EditorUI::CompileComponents()
{
	std::string word;
	bool isClass = 0;
	std::vector<std::string> keywords = 
	{
		"int",
		"float",
		"double",
		"std::string",

		"Vector2<int>",
		"Vector2<double>",
		"Vector2<float>",
		"Vector2<std::string>"
	};
	std::map<std::string,std::string> fields;

	std::ifstream file;
	std::string className;
	std::vector<std::string> files;
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	hFind = FindFirstFile("Project/Component/*.hpp",&FindData);
	std::cout << FindData.cFileName << std::endl;
	while(FindNextFile(hFind,&FindData))
	{
		std::cout << FindData.cFileName << std::endl;
		files.push_back(FindData.cFileName);
	}

	hFind = FindFirstFile("Project/Component/*.h",&FindData);
	std::cout << FindData.cFileName << std::endl;
	while(FindNextFile(hFind,&FindData))
	{
		std::cout << FindData.cFileName << std::endl;
		files.push_back(FindData.cFileName);
	}
	for(size_t i = 0; i < files.size(); i++)
	{
		#pragma region Read File
		file.open("Project/Component/"+files[i]);
		if(file.is_open())
		{
			while(file >> word)
			{
				//Check for the keyword: Class,
				if(word == "class")
				{
					//Get the class Name
					file >> className;
					if(className.at(className.size() - 1) == ':')
						className.erase(className.size()-1);
					isClass = true;
					break;
				}
			}
			if(isClass)
				while(file >> word)
					for(size_t i = 0; i < keywords.size(); i++)
						if(word == keywords[i])
						{
							std::string name;
							file >> name;
							if(name.find("()") == std::string::npos)
							{
								if(name.at(name.size() - 1) == ';')
									name.erase(name.size() - 1);
								fields.insert(fields.end(),std::make_pair(name,word));
							}
						}
		}
		
		file.close();
		#pragma endregion
		#ifdef _DEBUG
		std::cout << "Class: " << className << std::endl << "{" << std::endl << std::endl;
		for(auto it = fields.begin(); it != fields.end(); it++)
		{
			std::cout << "Name: " << it->first << std::endl;
			std::cout << "Type: " << it->second << std::endl << std::endl;
		}
		std::cout << "}" << std::endl;
		#endif
		compiledClass.insert(std::make_pair(files[i],fields));
	}


}
void EditorUI::Field::addGroup(EditorGroup* name)
{


}
void EditorUI::Field::addField(BaseField* variable,EditorGroup* group)	
{
	std::string value = "";
	int height = 16;
	//int width = GetLocalCoordinates(group->hwnd).right-GetLocalCoordinates(group->hwnd).left;
	const int space = 8;
	const int start = 32;
	int size = group->variableCount;

	int x = variable->name.size() * 8;
	int y = start + (space + 16) * size;
	
	if(x < 64)
		x = 64;

	//variable->name[0] = variable->name[0] + ('A' - 'a');
	variable->ID = RequestID();
	variable->label = addLabel(group->hwnd,variable->name,0,y,variable->name.size() * 8,height,RequestID());

	//LOW: Keep adding diffrent types
	if(variable->getType() == EditorField<std::string>::type)
		#pragma region std::string
	{
		EditorField<std::string>* a = static_cast<EditorField<std::string>*>(variable);
		value = a->variable->c_str();
		variable->hwnd = addTextbox(group->hwnd,value,x,y,64,height,variable->ID);
		group->field.insert(std::make_pair(variable->ID,a));

	}
		#pragma endregion
	else if(variable->getType() == EditorField<int>::type)
		#pragma region int
	{
		EditorField<int>* a = static_cast<EditorField<int>*>(variable);
		value = std::to_string(*a->variable);
		variable->hwnd = addTextboxInt(group->hwnd,value,x,y,64,height,variable->ID);
		variable->flags = FieldFlag::Numbers_Only;
		group->field.insert(std::make_pair(variable->ID,a));
	}
		#pragma endregion
	else
		#pragma region Vector2
	{
		if(variable->getType() == EditorField<Vector2<int>>::type)
			#pragma region Vector2<int>
		{
			EditorField<Vector2<int>>* a = static_cast<EditorField<Vector2<int>>*>(variable);
			EditorField<int>* varX = new EditorField<int>(&a->variable->x,a->name + ".x");
			EditorField<int>* varY = new EditorField<int>(&a->variable->y,a->name + ".y");
			std::string valueNigo = "";

			value = std::to_string(a->variable->x);
			valueNigo = std::to_string(a->variable->y);

			//variable->hwnd = addComponentGroup(group->hwnd,"",0,y,width,height +4,variable->ID);
			//variable->label = addLabel(group->hwnd,variable->name,0,0,width,16,RequestID());

			//Variable name	
			varX->ID = RequestID();
			varY->ID = RequestID();

			varX->hwnd = addTextboxInt(group->hwnd,value,x,y,64,height,varX->ID);
			varY->hwnd = addTextboxInt(group->hwnd,valueNigo,x + 64 + 8,y,64,height,varY->ID);


			varX->flags = FieldFlag::Left;
			varX->flags = FieldFlag::Right;

			varX->variable = &a->variable->x;
			varY->variable = &a->variable->y;

			varX->holder = a->holder;
			varY->holder = a->holder;


			group->field.insert(std::make_pair(varX->ID,varX));
			group->field.insert(std::make_pair(varY->ID,varY));

		}
			#pragma endregion
		if(variable->getType() == EditorField<Vector2<double>>::type)
			#pragma region Vector2<double>
		{
			EditorField<Vector2<double>>* a = static_cast<EditorField<Vector2<double>>*>(variable);
			EditorField<double>* varX = new EditorField<double>(&a->variable->x,a->name + ".x");
			EditorField<double>* varY = new EditorField<double>(&a->variable->y,a->name + ".y");
			std::string valueNigo = "";

			value = std::to_string(a->variable->x);
			valueNigo = std::to_string(a->variable->y);

			//variable->hwnd = addComponentGroup(group->hwnd,"",0,y,width,height +4,variable->ID);
			//variable->label = addLabel(group->hwnd,variable->name,0,0,width,16,RequestID());

			//Variable name	
			varX->ID = RequestID();
			varY->ID = RequestID();

			varX->hwnd = addTextbox(group->hwnd,value,x,y,64,height,varX->ID);
			varY->hwnd = addTextbox(group->hwnd,valueNigo,x + 64 + 8,y,64,height,varY->ID);


			varX->flags = FieldFlag::Decimal | FieldFlag::Left;
			varX->flags = FieldFlag::Decimal | FieldFlag::Right;

			varX->variable = &a->variable->x;
			varY->variable = &a->variable->y;

			varX->holder = a->holder;
			varY->holder = a->holder;

			group->field.insert(std::make_pair(varX->ID,varX));
			group->field.insert(std::make_pair(varY->ID,varY));

		}
			#pragma endregion
	}
		#pragma endregion
	if(!value.empty())
		group->variableCount++;
	#pragma endregion
}
