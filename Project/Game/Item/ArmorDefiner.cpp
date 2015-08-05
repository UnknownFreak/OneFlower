#include "Armor.hpp"
#include "../../Engine.hpp"
#include "../Component/EquipmentComponent.hpp"
Armor::Armor() : Item(0,false,"None", "InventoryIconTest.png",Item::armor,0,2, "§Color|150|25|25|Armor|sColor|25|150|25| <De|sColor|25|25|150|bug>§"), armorType("None"), defense(0)
{

}
Armor::Armor(int ID, int defense, std::string name, std::string iconName, double weight, int price, std::string description, std::string armorType) : Item(ID, false, name, iconName, Item::armor, weight, price, description), armorType(armorType), defense(defense)
{

}
Armor::Armor(const Armor& armor) : Item(armor.ID, armor.stackable, armor.name, armor.iconName, armor.tag, armor.weight,armor.price, armor.description), armorType(armor.armorType), defense(armor.defense), armorIcon(armor.armorIcon)
{

}

Armor& Armor::operator=(const Armor& other)
{
	ID = other.ID;
	stackable = other.stackable;
	name = other.name;
	iconName = other.iconName;
	icon = other.icon;
	tag = other.tag;
	defense = other.defense;
	armorType = other.armorType;
	price = other.price;
	weight = other.weight;
	return *this;
}

std::string Armor::toToolTipString()
{
	std::string _defense = std::to_string(defense);
	std::string _price = std::to_string(price);
	int size = _price.length();
	if (size > 4)
		return description + "\n" + "Defense: " + _defense + "§Compare|i|" + _defense + "|s-i|" + armorType + "§" + "\nWeight: " + std::to_string(weight) + "\n" + armorType + "\n§Icon|coins|72|NumberOfRows|" + _price + "§";
	else if (size > 2)
		return description + "\n" + "Defense: " + _defense + "§Compare|i|" + _defense + "|s-i|" + armorType + "§" + "\nWeight: " + std::to_string(weight) + "\n" + armorType + "\n§Icon|coins|42|NumberOfRows|" + _price + "§";
	else
		return description + "\n" + "Defense: "+ _defense + "§Compare|i|"+ _defense + "|s-i|"+ armorType + "§" + "\nWeight: " + std::to_string(weight) + "\n" + armorType + "\n§Icon|coins|12|NumberOfRows|" + _price + "§";
}