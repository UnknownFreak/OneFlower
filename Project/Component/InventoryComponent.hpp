#ifndef InventoryComponent_HPP
#define InventoryComponent_HPP
#include "IBaseComponent.hpp"
#include <vector>
class Item;
class InventoryComponent : public IBaseComponent < InventoryComponent >
{
public:
	int maxItems;
	int maxWeight;
	void addItem(Item* item);
	std::vector<Item*> items;
	InventoryComponent();

	void attachOn(GameObject* attachTo);
private:
	template<class Archive>
	friend void save(Archive&Ar, const InventoryComponent& Icp);
	template<class Archive>
	friend void load(Archive&Ar, InventoryComponent& Icp);

};


#endif