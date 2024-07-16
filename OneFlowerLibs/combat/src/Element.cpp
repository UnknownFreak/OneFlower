#include <combat/Element.hpp>

#include <file/Handler.hpp>
#include <logger/OneLogger.hpp>

of::common::uuid of::file::archive::Trait<of::combat::Element>::typeId = of::common::uuid("1423d23c-e7d0-493a-9e03-0c68a1714703");

namespace of::combat
{
	Element::Element() : Requestable(of::file::ObjectType::Element)
	{

	}

	Element::Element(const Element& copy) : Requestable(copy), name(copy.name), elementAttributes(copy.elementAttributes), damageToUnknownType(copy.damageToUnknownType)
	{

	}

	double Element::getElementModifier() const
	{
		return 1.0;
	}

	double Element::getElementModifier(const of::file::FileId& element) const
	{
		if (elementAttributes.find(element) != elementAttributes.end())
			return elementAttributes.at(element);
		else
		{
			of::engine::GetModule<of::logger::OneLogger>().getLogger("Combat::Element").Warning("Unknown Element type[" + element.name + "," + element.uuid.to_string() + "] called [<TODO>] defaulting "
				"to internal damageToUnknownType(" + std::to_string(damageToUnknownType).c_str() + ")");
			return damageToUnknownType;
		}
	}
	
	of::common::String Element::getElementAttributeName(const of::file::FileId& element) const
	{
		return of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<Element>(element).name;
	}
	
	of::file::archive::TypeInfo Element::getTrait() const
	{
		return { of::file::archive::Trait<Element>::typeId };
	}

	of::common::String Element::getName() const
	{
		return name;
	}

	bool Element::operator==(const Element& other) const
	{
		return other.ID == ID;
	}
}