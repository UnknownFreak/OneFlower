#ifndef IEditorField_HPP
#define IEditorField_HPP
#include <Windows.h>
#include <string>
#include <map>
#include "BaseField.hpp"
//#ifdef BaseComponentTest_HPP
#define REGISTER_EDITOR_TYPE(x)	std::string EditorField<x>::type = #x; //std::string EditorField<x>::getType(){return #x;}
#define REGISTER_EDITOR_VARIABLE(type,var,DisplayName)\
EditorField<type>* DisplayName = new EditorField<type>(&var,#DisplayName);\
editorFields.insert(std::make_pair(#var,DisplayName));\
DisplayName->holder = this;
//#endif
template<class T>
class EditorField : public BaseField
{
public:
	//LOW fix the compilation unit for method type
	//TODO get and set for the variable
	//TODO Make a Copy constructor? (Because of holder)
	//TODO Make it so that EditorField also take in a holder?
	EditorField(T* vPt,std::string vName)
	{
		variable = vPt;
		name = vName;
	}
	~EditorField()	
	{
		DestroyWindow(label);
		DestroyWindow(hwnd);
		
//		DestroyWindow(second);
	}

	//The variable
	T* variable;
	std::string getType()
	{
		return type;//	 static_assert(false,"You are missing a REGISTER_EDITOR_TYPE");;
	}

	//Name of type
	static std::string type;

};

class EditorGroup
{
public:
	//The Group Window
	HWND hwnd;
	
	//The Component name
	std::string name;

	//The Name Label
	HWND label;

	//All the variable field
	std::map<int,BaseField*> field;

	int variableCount = 0;


	
};

#endif
