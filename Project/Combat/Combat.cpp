#include "Combat.hpp"

Enums::ComponentType Component::IBase<Component::CombatComponent>::typeID = Enums::ComponentType::Combat;
of::common::String Component::IBase<Component::CombatComponent>::componentName = "Combat";

namespace Component
{

	std::unordered_map<Enums::CombatSkill, ::Combat::Skill >& CombatComponent::getSkills()
	{
		return skills;
	}

	CombatComponent::CombatComponent()
	{
	}

	void CombatComponent::onCollision(GameObject*)
	{
	}

	void CombatComponent::Update()
	{
	}

	void CombatComponent::Simulate(const float& fElapsedTime)
	{
		for (auto& skill : skills)
			skill.second.update(fElapsedTime);
	}

	void CombatComponent::onDeath()
	{
	}

	void CombatComponent::execute(const Enums::CombatSkill& skill)
	{
		if (skills.find(skill) == skills.end())
		{
			of::engine::GetModule < of::module::logger::OneLogger>().getLogger("Component::CombatComponent").Warning("Trying to execute a skill, when no skill equipped in slot " + Enums::to_string(skill) + ".");
			return;
		}
		skills[skill].onSkillExecution(attachedOn);
	}

	CombatComponent* CombatComponent::copy() const
	{
		return new CombatComponent(*this);
	}

	std::unique_ptr<Component::Base> CombatComponent::ucopy() const
	{
		return std::make_unique<CombatComponent>(*this);
	}
};
