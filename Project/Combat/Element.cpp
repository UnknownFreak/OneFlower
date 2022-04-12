#include "Element.hpp"

#include <File/Asset/Manager.hpp>
#include <Module/EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

Core::uuid Interfaces::Trait<Combat::Element>::typeId = Core::uuid("1423d23c-e7d0-493a-9e03-0c68a1714703");

namespace Combat
{
	Element::Element() : IRequestable(), IObject()
	{

	}

	Element::Element(const Element& copy) : IRequestable(copy), IObject(copy), elementAttributes(copy.elementAttributes), damageToUnknownType(copy.damageToUnknownType)
	{

	}

	double Element::getElementModifier() const
	{
		return 1.0;
	}

	double Element::getElementModifier(const File::Mod::ModFileUUIDHelper& element) const
	{
		if (elementAttributes.find(element) != elementAttributes.end())
			return elementAttributes.at(element);
		else
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Combat::Element").Warning("Unknown Element type[" + element.name + "," + element.uuid.to_string() + "] called [<TODO>] defaulting "
				"to internal damageToUnknownType(" + std::to_string(damageToUnknownType).c_str() + ")");
			return damageToUnknownType;
		}
	}
	
	Core::String Element::getElementAttributeName(const File::Mod::ModFileUUIDHelper& element) const
	{
		return Engine::GetModule<File::Asset::Manager>().requestor.requestUniqueInstance<Element>(element).name;
	}
	
	Interfaces::TypeInfo Element::getTrait() const
	{
		return { Interfaces::Trait<Element>::typeId };
	}
	
	bool Element::operator==(const Element& other) const
	{
		return other.ID == ID;
	}
}