#ifndef WEAPON_HPP 
#define	WEAPON_HPP
#include "Item.hpp"
#include "../Effect/Enchantment.hpp"
namespace Items
{
	class Weapon : public Item
	{
	public:
		Weapon();
		Weapon(unsigned int ID, int damage, int defense, std::string name, std::string iconName, double weight,
			int price, std::string desciption, std::string spriteName, std::string WeaponType, std::map<std::string, Vector2> attachmentPoints);
		Weapon(const Weapon& copy);
		Weapon& operator=(const Weapon& copy);

		std::string toToolTipString();
		//private:
		int damage;
		int defense;
		std::string spriteName;
		sf::Sprite sprite;
		std::string WeaponType;
	private:

		template<class T>
		friend void save(T& ar, const Items::Weapon& wpn);
		template<class T>
		friend void load(T& ar, Items::Weapon& wpn);
	};
}
#endif