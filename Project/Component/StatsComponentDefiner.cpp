#include "StatsComponent.hpp"
#include "GameObject.h"

//tmp
#include "../Engine.hpp"

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

	REGISTER_EDITOR_VARIABLE(std::string,race.raceName,RaceName);
	REGISTER_EDITOR_VARIABLE(int,health,Health);
	REGISTER_EDITOR_VARIABLE(int,maxHealth,MaxHealth);
	REGISTER_EDITOR_VARIABLE(int,mana,Mana);
	REGISTER_EDITOR_VARIABLE(int,maxMana,MaxMana);
	REGISTER_EDITOR_VARIABLE(int,stamina,Stamina);
	REGISTER_EDITOR_VARIABLE(int,maxStamina,MaxStamina);
	REGISTER_EDITOR_VARIABLE(int,agility,Agility);
}

bool StatsComponent::UpdateFromEditor()
{
	//tmp - remove this later.
	Engine::GUI.stats.updateStats = true;
	return true;
}