#ifndef PickupComponent_HPP
#define PickupComponent_HPP
#include "IBaseComponent.hpp"


class PickupComponent : public IBaseComponent < PickupComponent >
{
public:

	PickupComponent() = default;
	PickupComponent(unsigned int itemID);

	void attachOn(GameObject* attachTo);
	bool UpdateFromEditor();
private:
	unsigned int itemID;
	bool pickedUp = false;

	template<class Archive>
	friend void save(Archive& ar, const PickupComponent &stats);
	template<class Archive>
	friend void load(Archive& ar, PickupComponent &stats);
};


#endif