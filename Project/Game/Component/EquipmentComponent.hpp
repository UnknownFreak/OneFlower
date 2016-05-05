#ifndef EQUIPMENTCOMPONENT_HPP
#define EQUIPMENTCOMPONENT_HPP

#include "IBaseComponent.hpp"
#include "../Item/Armor.hpp"
class EquipmentComponent: public IBaseComponent < EquipmentComponent >
{
public:

	EquipmentComponent();

	Items::Armor* helm;
	Items::Armor* chest;
	Items::Armor* gloves;
	Items::Armor* leggings;
	Items::Armor* boots;

	Items::Item* equipArmor(Items::Item* item);

private:

	template<class Archive>
	friend void save(Archive& ar,const EquipmentComponent& ecp);
	template<class Archive>
	friend void load(Archive& ar,EquipmentComponent& ecp);
};

#endif