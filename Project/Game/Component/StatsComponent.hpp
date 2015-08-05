#ifndef StatsComponent_HPP
#define StatsComponent_HPP

#include "IBaseComponent.hpp"

//tmp stuff, remove this later
struct Race
{
	std::string raceName = "null";
	//attribute stuff bonus / debuffs.
};

class StatsComponent: public IBaseComponent < StatsComponent >
{
public:

	StatsComponent();
	StatsComponent(const StatsComponent& comp);

	int health;
	int maxHealth;

	int mana;
	int maxMana;

	int stamina;
	int maxStamina;

	int agility;

	Race race;

	void attachOn(GameObject* attachTo);
	bool updateFromEditor();

private:

	template<class Archive>
	friend void save(Archive& ar,const StatsComponent &stats);
	template<class Archive>
	friend void load(Archive& ar,StatsComponent &stats);
};

#endif //StatsComponent