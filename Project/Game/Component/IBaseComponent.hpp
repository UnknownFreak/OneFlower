#ifndef IBaseComponent_HPP
#define IBaseComponent_HPP
#include "BaseComponent.hpp"
#include <string>
#ifdef _DEBUG
	#include "../../Engine/Editor/BaseField.hpp"
	#include "../../Engine/Editor/EditorField.hpp"
#endif
template<typename>
class IBaseComponent:public BaseComponent
{
public:

	const unsigned int getType()
	{
		return typeID;
	}
	std::string getTypeName()
	{
		return componentName;
	}

	static std::string componentName;
	static const unsigned int typeID;



protected:


#ifdef _DEBUG	
	std::map<std::string,BaseField*> getFields()
	{
		return editorFields;
	}

	//HIGH: Friendclass stuffz so you can put this into private
	std::map<std::string,BaseField*> editorFields;
#endif
};
#endif