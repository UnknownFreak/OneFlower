#ifndef EQUIPMENTCOMPONENT_HPP
#define EQUIPMENTCOMPONENT_HPP

#include "IBaseComponent.hpp"
class Armor;
class Item;
class EquipmentComponent : public IBaseComponent < EquipmentComponent >
{
public:

	EquipmentComponent();

	Armor* helm;
	Armor* chest;
	Armor* gloves;
	Armor* leggings;
	Armor* boots;


	Item* equipArmor(Item* item);

private:

	template<class Archive>
	friend void save(Archive& ar, const EquipmentComponent& ecp);
	template<class Archive>
	friend void load(Archive& ar, EquipmentComponent& ecp);

};


#endif