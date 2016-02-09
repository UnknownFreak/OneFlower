#ifndef Bag_HPP
#define Bag_HPP
#define STACKSIZE 50
#include "Item.hpp"
#include <vector>
class Bag: public Item
{
public:

	Bag();
	Bag(unsigned int ID, std::string name, std::string iconName, double weight, int price, std::string description, int size);
	Bag(const Bag& bag);
	~Bag();
	Bag& operator=(const Bag& other);

	int size;
	int freeSlots;
	std::vector<std::pair<Item*, int>> items;

	int addItem(Item* item,int numberOfItems);
	int findFirstEmptySlot();

	std::pair<Item*,int>* FindNonFilledStack(int ID);
	std::pair<Item*,int>* findItem(int ID);
	std::string toToolTipString();
private:

	template<class Archive>
	friend void save(Archive &Ar,const Bag& item);
	template<class Archive>
	friend void load(Archive &Ar,Bag& item);
};

#endif