#ifndef Item_HPP
#define Item_HPP
#include <map>
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include "../../Vector.h"
#include "../LoadAndSave/EditorObjectSaveMode.hpp"

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
	Item(unsigned int ID, bool stackable, std::string name, std::string iconName, ItemType tag, double weight, int price, std::string description);
	Item(const Item& item);
	Item& operator=(const Item& other);
	std::string getTagAsString();
	std::string getName();
	std::string getIconName();
	Vector2& getAttachmentPoint(std::string& name);
	virtual std::string toToolTipString();
	virtual ~Item() = default;
	double getWeight();
	unsigned int getID();
	ItemType getTag();
	int getPrice();
	bool getStackable();
	sf::Sprite icon;
	std::string fromMod = "OneFlower.main";
	EditorObjectSaveMode mode = EditorObjectSaveMode::ADD;
protected:
	

	unsigned int ID;
	bool stackable;
	double weight;
	ItemType tag;
	int price;

	std::string description;
	std::string name;
	std::string iconName;
	
	std::map<std::string, Vector2> attachmentPoints;
private:

	template<class Archive>
	friend void save(Archive &Ar,const Item& item);
	template<class Archive>
	friend void load(Archive &Ar,Item& item);
};

#endif