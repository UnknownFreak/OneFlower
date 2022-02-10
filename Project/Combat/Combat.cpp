#include "Combat.hpp"

Enums::ComponentType Component::IBase<Component::CombatComponent>::typeID = Enums::ComponentType::Combat;
Core::String Component::IBase<Component::CombatComponent>::componentName = "Combat";

std::unordered_map<Enums::CombatSkill, ::Combat::Skill >& Component::CombatComponent::getSkills()
{
	return skills;
}

Component::CombatComponent::CombatComponent()
{
}

void Component::CombatComponent::onCollision(Interfaces::ICollider* )
{
}

void Component::CombatComponent::Update()
{
}

void Component::CombatComponent::Simulate(const float& fElapsedTime)
{
	for (auto& skill : skills)
		skill.second.update(fElapsedTime);
}

void Component::CombatComponent::onDeath()
{
}

void Component::CombatComponent::execute(const Enums::CombatSkill& skill)
{
	if (skills.find(skill) == skills.end())
	{
		Engine::GetModule < EngineModule::Logger::OneLogger>().getLogger("Component::CombatComponent").Warning("Trying to execute a skill, when no skill equipped in slot " + Enums::to_string(skill) + ".");
		return;
	}
	skills[skill].onSkillExecution(attachedOn);
}

Component::CombatComponent* Component::CombatComponent::copy() const
{
	return new CombatComponent(*this);
}

std::unique_ptr<Component::Base> Component::CombatComponent::ucopy() const
{
	return std::make_unique<CombatComponent>(*this);
}
