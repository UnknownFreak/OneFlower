#include "Consumable.hpp"

Consumable::Consumable() : Item(0, true, "name", "test.png", Item::consumable, 0, 0, "none")
{

}
Consumable::Consumable(unsigned int ID, std::string name, std::string iconName, double weight, int price, std::string desciption):
Item(ID,true,name,iconName,Item::consumable,weight,price, desciption)
{

}
Consumable::Consumable(const Consumable& copy) : Item(copy.ID,copy.stackable,copy.name,copy.iconName,Item::consumable,copy.weight,copy.price,copy.description)
{

}
Consumable& Consumable::operator=(const Consumable& copy)
{
	ID = copy.ID;
	stackable = copy.stackable;
	name = copy.name;
	iconName = copy.iconName;
	icon = copy.icon;
	tag = copy.tag;
	weight = copy.weight;
	price = copy.price;
	description = copy.description;
	return *this;
}
std::string Consumable::toToolTipString()
{
	return Item::toToolTipString() + "\n TODO <ConsumableDefiner.hpp>";
}
