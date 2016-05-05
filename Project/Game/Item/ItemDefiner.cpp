#include "Item.hpp"
#include "../../Engine.hpp"
namespace Items
{
	Item::Item() : ID(0), stackable(true), name("NotSet"), iconName("InventoryIconTest.png"), icon(*Engine::Graphic.requestTexture(iconName)), tag(undefined), weight(0), price(11110), description("Nan"), attachmentPoints({ { "Default", Vector2(0, 0) } })
	{
	}
	Item::Item(unsigned int ID, bool stackable, std::string name, std::string iconName, ItemType tag, double weight, int price, std::string description) : ID(ID), stackable(stackable), name(name), iconName(iconName), icon(*Engine::Graphic.requestTexture(iconName)), tag(tag), weight(weight), price(price), description(description), attachmentPoints({ { "Default", Vector2(0, 0) } })
	{
	}
	Item::Item(const Item& item) : ID(item.ID), stackable(item.stackable), name(item.name), iconName(item.iconName), price(item.price), icon(*Engine::Graphic.requestTexture(iconName)), weight(item.weight), tag(item.tag), description(item.description), attachmentPoints({ { "Default", Vector2(0, 0) } })
	{
	}
	Vector2& Item::getAttachmentPoint(std::string& name)
	{
		std::map<std::string, Vector2>::iterator it = attachmentPoints.find(name);
		if (it != attachmentPoints.end())
			return it->second;
		else
			return attachmentPoints.find("Default")->second;
	}
	bool Item::getStackable()
	{
		return stackable;
	}
	std::string Item::getName()
	{
		return name;
	}
	std::string Item::getIconName()
	{
		return iconName;
	}
	double Item::getWeight()
	{
		return weight;
	}
	int Item::getPrice()
	{
		return price;
	}
	Item::ItemType Item::getTag()
	{
		return tag;
	}
	unsigned int Item::getID()
	{
		return ID;
	}
	Item& Item::operator=(const Item& other)
	{
		ID = other.ID;
		stackable = other.stackable;
		name = other.name;
		iconName = other.iconName;
		price = other.price;
		icon = other.icon;
		weight = other.weight;
		tag = other.tag;
		return *this;
	}
	std::string Item::getTagAsString()
	{
		switch (tag)
		{
		case undefined:
			return "Undefined";
		case bag:
			return "Bag";
		case armor:
			return "Armor";
		case weapon:
			return "Weapon";
		case consumable:
			return "Consumable";
		case craftingMaterial:
			return "CraftingMaterial";
		case junk:
			return "Junk";
		case ammo:
			return "Ammo";
		case trophy:
			return "Trophy";
		default:
			return "None";
		}
	}

	std::string Item::toToolTipString()
	{

		std::string _price = std::to_string(price);
		int size = _price.length();
		if (size > 4)
			return description + "\n" + "Weight: " + std::to_string(weight) + "\n" + getTagAsString() + "\n§Icon|coins|72|NumberOfRows|" + _price;
		else if (size > 2)
			return description + "\n" + "Weight: " + std::to_string(weight) + "\n" + getTagAsString() + "\n§Icon|coins|42|NumberOfRows|" + _price;
		else
			return description + "\n" + "Weight: " + std::to_string(weight) + "\n" + getTagAsString() + "\n§Icon|coins|12|NumberOfRows|" + _price;
	}
}