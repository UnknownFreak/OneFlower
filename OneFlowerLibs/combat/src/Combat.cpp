#include <component/combat.hpp>

#include <logger/Logger.hpp>
#include <courier/courier.hpp>


namespace of::component
{
	void CombatComponent::onMessage(const of::object::messaging::Message&)
	{
	}
	std::unordered_map<Enums::CombatSkill, of::combat::Skill >& CombatComponent::getSkills()
	{
		return skills;
	}

	void CombatComponent::attached()
	{
		if (subscriberId == 0)
		{
			// todo create channel and push skills into the channel once executed & remove them automatically via it's instance id when the skill is done updating
			subscriberId = of::courier::get().addSubscriber(of::courier::Topic::Update, of::courier::Subscriber(isAlive(), [this](const of::courier::Message& msg) {update(msg.get<float>()); }));
		}
	}

	void CombatComponent::initialize()
	{

	}

	void CombatComponent::deconstruct()
	{
		if (subscriberId != 0)
		{
			of::courier::get().removeSubscriber(of::courier::Topic::Update, subscriberId);
			subscriberId = 0;
		}
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
			of::engine::GetModule < of::logger::Logger>().getLogger("Component::CombatComponent").Warning("Trying to execute a skill, when no skill equipped in slot " + Enums::to_string(skill) + ".");
			return;
		}
		skills[skill].onSkillExecution(attachedOn);
	}

	CombatComponent* CombatComponent::copy() const
	{
		return new CombatComponent(*this);
	}

	std::unique_ptr<of::component::Base> CombatComponent::ucopy() const
	{
		return std::make_unique<CombatComponent>(*this);
	}
};
