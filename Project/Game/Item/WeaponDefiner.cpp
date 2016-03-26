#include "Weapon.hpp"
#include "../../Engine.hpp"
Weapon::Weapon() : Item(0, false, "name", "test.png", Item::weapon, 0, 0, "none")
{

}
Weapon::Weapon(unsigned int ID, int damage, int defense, std::string name, std::string iconName, double weight,
	int price, std::string desciption, std::string spriteName, std::string WeaponType, std::map<std::string, Vector2> attachPoints) :
	Item(ID, false, name, iconName, Item::weapon, weight, price, desciption),
	damage(damage), defense(defense), WeaponType(WeaponType), sprite(*Engine::Graphic.requestTexture(spriteName)), spriteName(spriteName)
{
	attachmentPoints.insert(attachPoints.begin(), attachPoints.end());
}
Weapon::Weapon(const Weapon& copy) : Item(copy.ID, copy.stackable, copy.name, copy.iconName, Item::weapon, copy.weight, copy.price, copy.description),
damage(copy.damage), defense(copy.defense), WeaponType(copy.WeaponType), sprite(copy.sprite), spriteName(copy.spriteName)
{
	attachmentPoints = copy.attachmentPoints;
}
Weapon& Weapon::operator=(const Weapon& copy)
{
	damage = copy.damage;
	defense = copy.defense;
	WeaponType = copy.WeaponType;
	sprite = copy.sprite;
	spriteName = copy.spriteName;
	ID = copy.ID;
	stackable = copy.stackable;
	name = copy.name;
	iconName = copy.iconName;
	icon = copy.icon;
	tag = copy.tag;
	weight = copy.weight;
	price = copy.price;
	description = copy.description;
	attachmentPoints = copy.attachmentPoints;
	return *this;
}

std::string Weapon::toToolTipString()
{
	return Item::toToolTipString() + "\n TODO <WeaponDefiner.hpp>";
}