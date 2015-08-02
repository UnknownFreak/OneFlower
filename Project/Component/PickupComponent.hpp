#ifndef PickupComponent_HPP
#define PickupComponent_HPP
#include "IBaseComponent.hpp"

class Item;
class PickupComponent : public IBaseComponent < PickupComponent >
{
public:

	PickupComponent() = default;
	PickupComponent(unsigned int itemID, int stackSize = 1);

	void attachOn(GameObject* attachTo);
#ifdef _DEBUG
	bool UpdateFromEditor();
#endif
private:
	int stackSize;
	unsigned int itemID;
	bool pickedUp = false;

	void pickupLoot(GameObject* character);
	Item createItem();



	template<class Archive>
	friend void save(Archive& ar, const PickupComponent &stats);
	template<class Archive>
	friend void load(Archive& ar, PickupComponent &stats);
};


#endif