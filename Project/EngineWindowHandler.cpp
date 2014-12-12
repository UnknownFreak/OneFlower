#include "EngineWindow.hpp"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include "Component\TransformComponent.hpp"
#include "EditorUI\EditorField.hpp"
#include "Engine.hpp"
#include "EditorUI\UIAddon.hpp"
#include <Windows.h>
void EngineWindow::setGameObject(GameObject* t)
{
	int size = 256;
	DestroyWindow(focusWindow);
	cleanse();
	if(t)
	{
		//The focused window of the selectd game object
		focusWindow = EditorUI::addEditor(Engine::Window.hWnd,"",EditorUI::GetLocalCoordinates(hWnd).right - EditorUI::GetLocalCoordinates(hWnd).left - size,0,size,600,EditorUI::RequestID());
		std::string lastName = "";

		//All components from the gameObject, gameComponent_it = BaseComponent*
		for(std::map<int,BaseComponent*>::iterator gameComponent_it = t->GetComponents()->begin(); gameComponent_it != t->GetComponents()->end(); gameComponent_it++)
		{
			//For spacing
			int x = 0;
			int y = 0;
			//To avoid Out of range
			if(lastName != "")
			{
				x = EditorUI::GetLocalCoordinates(fieldGroup.at(lastName).hwnd).left;
				y = EditorUI::GetLocalCoordinates(fieldGroup.at(lastName).hwnd).bottom + 8;
			}
			EditorGroup a;
			//Add a Component Group HWND that hold all the variable HWND
			a.hwnd = EditorUI::addComponentGroup(focusWindow,"",x,y,EditorUI::GetLocalCoordinates(focusWindow).right / 2,(gameComponent_it->second->getFields().size() * 32) + 32,EditorUI::RequestID());
			
			//Get the name of component
			a.name = gameComponent_it->second->getTypeName();
			
			//Add a Label with said Component name
			a.label = EditorUI::addLabel(a.hwnd,a.name,0,0,a.name.size() * 8,16,EditorUI::RequestID());
			
			//Insert the Name of the component
			fieldGroup.insert(std::pair<std::string,EditorGroup>(gameComponent_it->second->getTypeName(),a));
			
			
			lastName = gameComponent_it->second->getTypeName();


			//Copy of Registered editor variables from Component
			std::map<std::string,BaseField*> test = gameComponent_it->second->getFields();

			//All Field inside each component
			for(std::map<std::string,BaseField*>::iterator componentField_it = test.begin(); componentField_it != test.end(); componentField_it++)
				EditorUI::Field::addField(componentField_it->second,&fieldGroup.at(gameComponent_it->second->getTypeName()));
		}
	}
}
void EngineWindow::setValue(int id,std::string value)
{
	BaseField* variable = NULL;
	std::map<int,BaseField*>::iterator it;
	for(auto i = Engine::Window.fieldGroup.begin(); i != Engine::Window.fieldGroup.end(); i++)
	{
		it = i->second.field.find(id);
		if(it != i->second.field.end())
		{
			variable = it->second;
			break;
		}
	}
	if(variable)
	{
		if(variable->getType() == EditorField<int>::type)
		{
			EditorField<int>* a = static_cast<EditorField<int>*>(variable);
			int b = std::atoi(value.c_str());
			*a->variable = b;
		}
		else if(variable->getType() == EditorField<double>::type)
		{
			EditorField<double>* a = static_cast<EditorField<double>*>(variable);
			int b = std::atoi(value.c_str());
			*a->variable = b;
		}
		else if(variable->getType() == EditorField<std::string>::type)
		{
			EditorField<std::string>* a = static_cast<EditorField<std::string>*>(variable);
			int b = std::atoi(value.c_str());
			*a->variable = b;
		}
		if(variable->holder)
			variable->holder->UpdateFromEditor();
		else
			MessageBox(Engine::Window.hWnd,"Empty variable Holder","Error:5870",NULL);
	}
}
