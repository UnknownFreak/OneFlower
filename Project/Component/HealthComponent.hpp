#ifndef HealthComponent_HPP
#define HealthComponent_HPP

#include "IBaseComponent.hpp"
#include "../Vector.h"
class StatsComponent;
class HealthComponent: public IBaseComponent < HealthComponent >
{
public:

	HealthComponent();
	HealthComponent(const HealthComponent& hcp);

	bool invulnerable;
	bool dead;
#if _DEBUG
	std::string tmp;
	std::string tmp2;
#endif
	//probably rework this
	StatsComponent* stats;

	double getHealthPercent();
	double getHealthPercentDecimals();

	void attachOn(GameObject* attachTo);

	void doDamage(int damageDealt);

	bool UpdateFromEditor();

	Vector2 GetHealthStats();
private:

	template<class Archive>
	void save(Archive& ar,const HealthComponent &hcp);
	template<class Archive>
	void load(Archive& ar,HealthComponent &hcp);
};

#endif