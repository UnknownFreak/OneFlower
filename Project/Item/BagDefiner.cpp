#include "Bag.hpp"
#include "Armor.hpp"
Bag::Bag() : Item(0, false, "None", "InventoryIconTest.png",Item::bag,0,0, "15 Slot bag. <Debug>"), size(15),freeSlots(15), items(size,std::pair<Item*,int>(NULL,0))
{

}

Bag::~Bag()
{
	for (auto it = items.begin(); it != items.end(); ++it)
		if (it->first)
			delete it->first;
}

Bag::Bag(const Bag& bag) : Item(bag.ID, bag.stackable, bag.name, bag.iconName, bag.tag, bag.weight,bag.price,bag.description), size(bag.size), freeSlots(bag.freeSlots), items(bag.items)
{

}

Bag& Bag::operator=(const Bag& other)
{
	freeSlots = other.freeSlots;
	icon = other.icon;
	iconName = other.iconName;
	ID = other.ID;
	tag = other.tag;
	
	name = other.name;
	price = other.price;
	
	size = other.size;
	stackable = other.stackable;
	for (auto it = other.items.begin(); it != other.items.end(); ++it)
		items.push_back(*it);
	return *this;
}

//only returns first found (Rework this)
std::pair<Item*,int>* Bag::findItem(int ID)
{
	for (std::vector<std::pair<Item*, int>>::iterator it = items.begin(); it != items.end(); ++it)
	{
		if (it->first->ID == ID)
			return &*it;
	}
	return NULL;
}	

//finds the first non filled stack of item ID
std::pair<Item*, int>* Bag::FindNonFilledStack(int ID)
{
	for (std::vector<std::pair<Item*, int>>::iterator it = items.begin(); it != items.end(); ++it)
	{
		if (it->first)
			if (it->first->ID == ID && it->first->stackable)
				if (it->second < STACKSIZE)
					return &*it;
	}
	return NULL;
}


int Bag::findFirstEmptySlot()
{
	for (size_t i = 0; i < size; ++i)
		if (items[i].first==NULL)
			return i;
	return -1;
}

int Bag::addItem(Item *item)
{
	int i = findFirstEmptySlot();
	if (i == -1)
		return -1;
	std::vector<std::pair<Item*, int>>::iterator it = items.erase(items.begin() + i);
	if (it->first)
		delete it->first;
	if (item->tag == Item::armor)
	{
		Armor* arm = (Armor*)item;
		items.insert(items.begin() + i, std::pair<Item*, int>(new Armor(*arm), 1));
	}
	else if (item->tag == Item::bag)
	{
		Bag* arm = (Bag*)item;
		items.insert(items.begin() + i, std::pair<Item*, int>(new Bag(*arm), 1));
	}
	else if (item->tag == Item::undefined)
	{
		Item* arm = (Item*)item;
		items.insert(items.begin() + i, std::pair<Item*, int>(new Item(*arm), 1));
	}
	--freeSlots;
	return i;
}
std::string Bag::toToolTipString()
{
	return description + "\n" + std::to_string(size - freeSlots) + "/" + std::to_string(size) + " slots used.\n" + "weight: " + std::to_string(weight) + "\nBag" + "\n§Icon|coins|16|0|" + std::to_string(price) + "§";
}