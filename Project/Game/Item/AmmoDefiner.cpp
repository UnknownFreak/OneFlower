#include "Ammo.hpp"
#include "../../Engine.hpp"

namespace Items
{
	Ammo::Ammo() : Item(0, true, "ndef", "test.png", Item::ammo, 0, 0, "None"), damage(0), ammoType("Undefined")
	{

	}
	Ammo::Ammo(unsigned int ID, std::string name, std::string iconName, double weight, int price, std::string description, std::string ammoSprite, int damage, int ammoType) :
		Item(ID, true, name, iconName, Item::ammo, weight, price, description), damage(damage), ammoSprite(ammoSprite), sprite(*Engine::Graphic.requestTexture(ammoSprite))
	{
		switch (ammoType)
		{
		case Ammo::Arrow:
			this->ammoType = "Arrow";
			break;
		case Ammo::Bolt:
			this->ammoType = "Bolt";
			break;
		case Ammo::Undefined:
			this->ammoType = "Undefined";
			break;
		default:
			break;
		}
	}
	Ammo::Ammo(const Ammo& cpy) :Item(cpy.ID, cpy.stackable, cpy.name, cpy.iconName, cpy.tag, cpy.tag, cpy.price, cpy.description), damage(cpy.damage), ammoType(cpy.ammoType), ammoSprite(cpy.ammoSprite), sprite(cpy.sprite)
	{
	}
	Ammo& Ammo::operator=(const Ammo& other)
	{
		ID = other.ID;
		stackable = other.stackable;
		name = other.name;
		iconName = other.iconName;
		icon = other.icon;
		tag = other.tag;
		price = other.price;
		weight = other.weight;
		damage = other.damage;
		ammoType = other.ammoType;
		ammoSprite = other.ammoSprite;
		sprite = other.sprite;
		return *this;
	}

	std::string Ammo::toToolTipString()
	{
		std::string _damage = std::to_string(damage);
		std::string _price = std::to_string(price);
		int size = _price.length();
		if (size > 4)
			return description + "\n" + "Defense: " + _damage + "§Compare|i|" + _damage + "|s-i|" + "Ammo" + "§" + "\nWeight: " + std::to_string(weight) + "\n" + ammoType + "\n§Icon|coins|72|NumberOfRows|" + _price + "§";
		else if (size > 2)
			return description + "\n" + "Defense: " + _damage + "§Compare|i|" + _damage + "|s-i|" + "Ammo" + "§" + "\nWeight: " + std::to_string(weight) + "\n" + ammoType + "\n§Icon|coins|42|NumberOfRows|" + _price + "§";
		else
			return description + "\n" + "Defense: " + _damage + "§Compare|i|" + _damage + "|s-i|" + "Ammo" + "§" + "\nWeight: " + std::to_string(weight) + "\n" + ammoType + "\n§Icon|coins|12|NumberOfRows|" + _price + "§";
	}
}