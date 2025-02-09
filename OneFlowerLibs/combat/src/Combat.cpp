#include <component/combat.hpp>

#include <logger/Logger.hpp>
#include <courier/courier.hpp>
#include <engine/courier/topic.hpp>

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
		if (subscriberId == courier::SubscriberId::NOT_SET)
		{
			using Topic = of::engine::courier::Topic;
			constexpr auto to = of::Topic::convert;
			// todo create channel and push skills into the channel once executed & remove them automatically via it's instance id when the skill is done updating
			subscriberId = courier::get().addSubscriber(to(Topic::Update), courier::Subscriber(isAlive(), [this](const courier::Message& msg) {update(msg.get<float>()); }));
		}
	}

	void CombatComponent::initialize()
	{

	}

	void CombatComponent::deconstruct()
	{
		if (subscriberId != courier::SubscriberId::NOT_SET)
		{
			using Topic = of::engine::courier::Topic;
			constexpr auto from = of::Topic::convert;

			courier::get().removeSubscriber(from(Topic::Update), subscriberId);
			subscriberId = courier::SubscriberId::NOT_SET;
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
			of::logger::get().getLogger("Component::CombatComponent").Warning("Trying to execute a skill, when no skill equipped in slot " + Enums::to_string(skill) + ".");
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
