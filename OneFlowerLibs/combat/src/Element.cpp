#include <combat/Element.hpp>

#include <logger/Logger.hpp>

#include <asset/asset.hpp>

of::common::uuid of::asset::Trait<of::combat::Element>::typeId = of::common::uuid("1423d23c-e7d0-493a-9e03-0c68a1714703");

namespace of::combat
{
	Element::Element() : IAsset(of::asset::ObjectType::Element)
	{

	}

	Element::Element(const Element& copy) : IAsset(copy), name(copy.name), elementAttributes(copy.elementAttributes), damageToUnknownType(copy.damageToUnknownType)
	{

	}

	double Element::getElementModifier() const
	{
		return 1.0;
	}

	double Element::getElementModifier(const of::asset::AssetId& element) const
	{
		if (elementAttributes.find(element) != elementAttributes.end())
			return elementAttributes.at(element);
		else
		{
			of::logger::get().getLogger("Combat::Element").Warning("Unknown Element type[" + element.name + "," + element.uuid.to_string() + "] called [<TODO>] defaulting "
				"to internal damageToUnknownType(" + std::to_string(damageToUnknownType).c_str() + ")");
			return damageToUnknownType;
		}
	}
	
	of::common::String Element::getElementAttributeName(const of::asset::AssetId& element) const
	{
		return of::asset::getAssetRequestor().requestUniqueInstance<Element>(element).name;
	}
	
	of::asset::TypeInfo Element::getTrait() const
	{
		return { of::asset::Trait<Element>::typeId };
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