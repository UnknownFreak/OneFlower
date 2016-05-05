#ifndef Armor_HPP
#define Armor_HPP

#include "Item.hpp"
namespace Items
{
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
		Armor(unsigned int ID, int defense, std::string name, std::string iconName, double weight, int price, std::string description, std::string armorType, std::string armorSprite, std::map<std::string, Vector2>attachPoints);
		Armor(const Armor& armor);
		Armor& operator=(const Armor& other);

		int defense;

		std::string armorType;
		std::string armorIcon;
		sf::Sprite sprite;

		std::string toToolTipString();

	private:

		template<class Archive>
		friend void save(Archive &Ar, const Items::Armor& item);
		template<class Archive>
		friend void load(Archive &Ar, Items::Armor& item);
	};
}
#endif