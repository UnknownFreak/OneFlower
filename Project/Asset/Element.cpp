#include "Element.hpp"

#include <Core/EngineModule/EngineModuleManager.hpp>
#include <Core/Logger.hpp>

Element::Element() : Element("")
{
}

Element::Element(Core::String elementName) : IObject(elementName), IRequestable()
{
}

Element::Element(const Element & copy) : IObject(copy), IRequestable(copy)
{
}

double Element::getElementModifier()
{
	return 0.0;
}

double Element::getElementModifier(Core::String name, size_t ID)
{
	if(elementAttributes.find({ name, ID }) != elementAttributes.end())
		return elementAttributes[{name, ID}];
	else
	{
		Engine::GetModule<OneLogger>().Info("UnknownElementType["+name +","+ std::to_string(ID).c_str()+"] called [<TODO>] defaulting"
			"to internal damageToUnknownType("+std::to_string(damageToUnknownType).c_str()+")");
		return damageToUnknownType;
	}
}
