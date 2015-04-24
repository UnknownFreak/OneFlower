#ifndef IBaseComponent_HPP
#define IBaseComponent_HPP
#include "BaseComponent.hpp"
#include <string>
#include "../EditorUI/EditorField.hpp"

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
	std::map<std::string,BaseField*> getFields()
	{
		return editorFields;
	}

	//Name of the componentn
	static std::string componentName;
	static const unsigned int typeID;

	//HIGH: Friendclass stuffz so you can put this into private
	std::map<std::string,BaseField*> editorFields;
};
#endif