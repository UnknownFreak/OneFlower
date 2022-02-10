#ifndef Combat_HPP
#define Combat_HPP
#include "Skill.hpp"

#include <vector>
#include <Object/IBaseComponent.hpp>

#include <Helpers/Enum/CombatSkill.hpp>

namespace Component
{

	class CombatComponent : public IBase<CombatComponent>
	{

	public:
		std::unordered_map<Enums::CombatSkill, ::Combat::Skill> skills;

		std::unordered_map<Enums::CombatSkill, ::Combat::Skill>& getSkills();

		bool wasSkillChanged = true;

		CombatComponent();

		virtual void onCollision(Interfaces::ICollider* the_collidee) override;

		virtual void Update() override;

		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;

		void execute(const Enums::CombatSkill& skill);

		virtual CombatComponent* copy() const override;

		virtual std::unique_ptr<Base> ucopy() const override;

	};

}

#endif