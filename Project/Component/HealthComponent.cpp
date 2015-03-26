#include "HealthComponent.hpp"
#include "GameObject.h"
#include "StatsComponent.hpp"

const unsigned int IBaseComponent<HealthComponent>::typeID = 1006;
std::string IBaseComponent<HealthComponent>::componentName = "HealthComponent";

HealthComponent::HealthComponent(): invulnerable(false),dead(false),tmp("false"),tmp2("false")
{
}

void HealthComponent::attachOn(GameObject* attachTo)
{
	BaseComponent::attachOn(attachTo);
	stats = attachTo->GetComponent < StatsComponent>();
	if(!stats)
	{
		attachTo->AddComponent<StatsComponent>();
		stats = attachTo->GetComponent<StatsComponent>();
	}
#ifdef _DEBUG
	REGISTER_EDITOR_VARIABLE(std::string,tmp,Invuln);
	REGISTER_EDITOR_VARIABLE(std::string,tmp2,Dead);
#endif
}

void HealthComponent::doDamage(int damageDealt)
{
	if(!invulnerable && !dead)
	{
		stats->health -= damageDealt;
		if(stats->health <= 0)
			dead = true;
	}
}

double HealthComponent::getHealthPercent()
{
	return (double)(stats->health / (double)stats->maxHealth * 100);
}

double HealthComponent::getHealthPercentDecimals()
{
	return (double)(stats->health / double(stats->maxHealth));
}

bool HealthComponent::UpdateFromEditor()
{
#if _DEBUG
	if(tmp == "True" || tmp == "true")
	{
		invulnerable = true;
	}
	else
	{
		invulnerable = false;
		tmp = "false";
	}
	if(tmp2 == "True" || tmp2 == "true")
	{
		dead = true;
	}
	else
	{
		dead = false;
		tmp2 = "false";
	}
#endif
	return true;
}

Vector2 HealthComponent::GetHealthStats()
{
	return Vector2(stats->health,stats->maxHealth);
}