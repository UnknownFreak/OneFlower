#ifndef AMMO_HPP
#define	AMMO_HPP

#include "Item.hpp"
namespace Items
{
	class Ammo : public Item
	{
	public:
		enum ammoTypes
		{
			Arrow = 0,
			Bolt,
			Undefined
		};
		Ammo();
		Ammo(unsigned int ID, std::string name, std::string iconName, double weight, int price, std::string description, std::string ammoSprite, int damage, int ammoType);
		Ammo(const Ammo& cpy);
		Ammo& operator=(const Ammo& cpy);

		std::string toToolTipString();
		int damage;
		std::string ammoType;
		std::string ammoSprite;
		sf::Sprite sprite;
	private:

		template<class Archive>
		friend void save(Archive &Ar, const Items::Ammo& item);
		template<class Archive>
		friend void load(Archive &Ar, Items::Ammo& item);

	};
}
#endif