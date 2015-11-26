#ifndef Item_HPP
#define Item_HPP
#include <string>
#include <SFML\Graphics\Sprite.hpp>
class Item
{
public:
	enum ItemType
	{
		undefined = -1,
		bag = 0,
		armor,
		weapon,
		consumable,
		craftingMaterial,
		junk,
		ammo,
		trophy
	};
	Item();
	Item(int ID,bool stackable,std::string name,std::string iconName,int tag,double weight,int price,std::string description);
	Item(const Item& item);
	Item& operator=(const Item& other);
	virtual ~Item() = default;

	unsigned int ID;
	bool stackable;
	double weight;
	int tag;
	int price;

	std::string description;
	std::string name;
	std::string iconName;
	sf::Sprite icon;

	virtual std::string toToolTipString();
private:

	template<class Archive>
	friend void save(Archive &Ar,const Item& item);
	template<class Archive>
	friend void load(Archive &Ar,Item& item);
};

#endif