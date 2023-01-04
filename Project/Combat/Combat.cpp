#include "Combat.hpp"

#include <module/ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>
//of::common::uuid of::object::component::IBase<of::object::component::CombatComponent>::typeID = of::common::uuid("4d167cc6-90bd-491e-8def-0def351fec54");
//of::common::String of::object::component::IBase<of::object::component::CombatComponent>::componentName = "Combat";

namespace of::object::component
{
	void component::CombatComponent::onMessage(const of::object::messaging::Message&)
	{
	}
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

	std::unique_ptr<of::object::component::Base> CombatComponent::ucopy() const
	{
		return std::make_unique<CombatComponent>(*this);
	}
};
