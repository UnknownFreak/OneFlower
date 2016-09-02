#include "StatsComponent.hpp"
#include "GameObject.h"

//tmp
#include "../../Engine.hpp"

const unsigned int IBaseComponent<StatsComponent>::typeID = 1007;
std::string IBaseComponent<StatsComponent>::componentName = "StatsComponent";

StatsComponent::StatsComponent(): health(100),maxHealth(health),mana(health),maxMana(health),stamina(health),maxStamina(health),agility(4)
{
}

StatsComponent::StatsComponent(const StatsComponent& comp)
{
}

void StatsComponent::attachOn(GameObject* attachTo)
{
	BaseComponent::attachOn(attachTo);
}

bool StatsComponent::updateFromEditor()
{
	//tmp - remove this later.
	//Engine::GUI.stats.updateStats = true;
	return true;
}