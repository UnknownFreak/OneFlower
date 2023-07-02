#include <object/component/Combat.hpp>

#include <module/logger/OneLogger.hpp>
#include <messaging/courier.hpp>


namespace of::object::component
{
	void component::CombatComponent::onMessage(const of::object::messaging::Message&)
	{
	}
	std::unordered_map<Enums::CombatSkill, of::combat::Skill >& CombatComponent::getSkills()
	{
		return skills;
	}

	void CombatComponent::initialize()
	{
		auto courier = of::engine::GetModule<of::messaging::Courier>();
		// todo create channel and push skills into the channel once executed & remove them automatically via it's instance id when the skill is done updating
		courier.addSubscriber(of::messaging::Topic::Update, of::messaging::Subscriber(instanceId, warrantyFromThis(), [this](const of::messaging::Message& msg) {update(msg.as<of::messaging::BasicMessage<float>>().value); }));
	}

	void CombatComponent::deconstruct()
	{
		auto courier = of::engine::GetModule<of::messaging::Courier>();
		courier.removeSubscriber(of::messaging::Topic::Update, instanceId);
	}

	CombatComponent::CombatComponent()
	{
	}

	void CombatComponent::update(const float& fElapsedTime)
	{
		for (auto& skill : skills)
			skill.second.update(fElapsedTime);
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
