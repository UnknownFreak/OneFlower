#ifndef Armor_HPP
#define Armor_HPP

#include "Item.hpp"
class Armor : public Item
{
public:
	enum Type
	{
		Helm = 0,
		Chest,
		Gloves,
		Leggings,
		Boots
	};
	Armor();
	Armor(int ID, int defense, std::string name, std::string iconName, double weight, int price, std::string description, std::string armorType);
	Armor(const Armor& armor);
	Armor& operator=(const Armor& other);

	int defense;

	std::string armorType;
	std::string armorIcon;
	sf::Sprite armorSprite;

	std::string toToolTipString();

private:

	template<class Archive>
	friend void save(Archive &Ar, const Armor& item);
	template<class Archive>
	friend void load(Archive &Ar, Armor& item);
};

#endif