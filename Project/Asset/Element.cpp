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

double Element::getElementModifier(Core::String name_to_get, Core::uuid id_to_find)
{
	if(elementAttributes.find({ name_to_get, id_to_find }) != elementAttributes.end())
		return elementAttributes[{name_to_get, id_to_find}];
	else
	{
		Engine::GetModule<OneLogger>().Info("UnknownElementType["+name_to_get +","+ id_to_find.to_string().c_str()+"] called [<TODO>] defaulting"
			"to internal damageToUnknownType("+std::to_string(damageToUnknownType).c_str()+")");
		return damageToUnknownType;
	}
}
