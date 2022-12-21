#ifndef Combat_HPP
#define Combat_HPP
#include "Skill.hpp"

#include <vector>
#include <object/component/IBaseComponent.hpp>

#include <Helpers/Enum/CombatSkill.hpp>

namespace of::object::component
{

	class CombatComponent : public IBase<CombatComponent>
	{
		virtual void onMessage(const of::object::messaging::Message& message) override;
	public:
		std::unordered_map<Enums::CombatSkill, ::Combat::Skill> skills;

		std::unordered_map<Enums::CombatSkill, ::Combat::Skill>& getSkills();

		bool wasSkillChanged = true;

		CombatComponent();

		virtual void onCollision(GameObject* the_collidee) override;

		virtual void Update() override;

		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;

		void execute(const Enums::CombatSkill& skill);

		virtual CombatComponent* copy() const override;

		virtual std::unique_ptr<Base> ucopy() const override;

	};

}

CEREAL_REGISTER_TYPE(of::object::component::CombatComponent);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::object::component::Base, of::object::component::CombatComponent);
#endif