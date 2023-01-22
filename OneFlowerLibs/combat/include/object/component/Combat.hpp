#ifndef Combat_HPP
#define Combat_HPP

#include <combat/Skill.hpp>

#include <vector>
#include <object/component/BaseComponent.hpp>

#include <combat/CombatSkill.hpp>

namespace of::object::component
{

	class CombatComponent : public Base
	{
		virtual void onMessage(const of::object::messaging::Message& message) override;
		virtual void initialize() override {};
		virtual void deconstruct() override {};
	public:
		std::unordered_map<Enums::CombatSkill, of::combat::Skill> skills;

		std::unordered_map<Enums::CombatSkill, of::combat::Skill>& getSkills();

		bool wasSkillChanged = true;

		CombatComponent();

		virtual void update(const float& fElapsedTime) override;

		void execute(const Enums::CombatSkill& skill);

		virtual CombatComponent* copy() const override;

		virtual std::unique_ptr<Base> ucopy() const override;

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Combat";
		};

		static constexpr of::common::uuid typeId = "4d167cc6-90bd-491e-8def-0def351fec54";

	};

}

CEREAL_REGISTER_TYPE(of::object::component::CombatComponent);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::object::component::Base, of::object::component::CombatComponent);
#endif