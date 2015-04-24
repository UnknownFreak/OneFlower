#ifndef Item_HPP
#define Item_HPP
#include <string>
#include <map>



class Item
{
public:

	Item();
	~Item();
	std::string type = "Generic";
	unsigned int ID;

private:

	template<class Archive>
	friend void save(Archive &Ar, const Item& item);
	template<class Archive>
	friend void load(Archive &Ar, Item& item);
};

#endif