#include "Item.hpp"
#include "../Engine.hpp"
Item::Item() : ID(0), stackable(true), name("NotSet"), iconName("InventoryIconTest.png"), icon(*Engine::Graphic.requestTexture(iconName)), tag(undefined), weight(0), price(11110), description("Nan")
{

}
Item::Item(int ID, bool stackable, std::string name, std::string iconName, int tag, double weight, int price, std::string description) : ID(ID), stackable(stackable), name(name), iconName(iconName), icon(*Engine::Graphic.requestTexture(iconName)), tag(tag), weight(weight), price(price), description(description)
{

}
Item::Item(const Item& item) : ID(item.ID), stackable(item.stackable), name(item.name), iconName(item.iconName), price(item.price), icon(*Engine::Graphic.requestTexture(iconName)), weight(item.weight), tag(item.tag), description(item.description)
{

}
Item::~Item()
{

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
std::string Item::toToolTipString()
{
	std::string _tag;
	if (tag == undefined)
		_tag = "undefined";
	return description + "\n" + "Weight: " + std::to_string(weight) + "\n" + _tag + "\n§Icon|coins|16|0|" + std::to_string(price) + "§";
}