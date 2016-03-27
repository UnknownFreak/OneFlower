#ifndef InventoryComponent_HPP
#define InventoryComponent_HPP
#include "IBaseComponent.hpp"
#include <vector>
#include "../Item/Bag.hpp"
class InventoryComponent: public IBaseComponent < InventoryComponent >
{
public:
	double maxWeight;
	double currentWeight;
	int usedBags;
	int maxBags;

	int coins;

	std::vector<Items::Bag*> bags;

	InventoryComponent();
	~InventoryComponent();

	std::string getWeight();

	bool addItem(Items::Item& item, int numberOfItems);
	bool swapItem(Items::Bag* first, int firstPair, Items::Bag* second, int secondPair);
	bool equipBag(Items::Bag* first,int firstPair);
	bool unequipBag(Items::Bag* bag, Items::Bag* second, int emptySlot);
	bool updateFromEditor();

	void attachOn(GameObject* attachTo);
	void addGold(unsigned int goldToAdd);
	void removeGold(unsigned int goldToRemove);

	Items::Item* removeItem(int bag, int index, int numberOfItems);
private:

	template<class Archive>
	friend void save(Archive&Ar,const InventoryComponent& Icp);
	template<class Archive>
	friend void load(Archive&Ar,InventoryComponent& Icp);
};

#endif