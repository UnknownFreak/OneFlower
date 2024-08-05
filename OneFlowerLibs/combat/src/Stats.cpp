#include <component/stats.hpp>

#include <file/Handler.hpp>
#include <rng/rng.hpp>

#include <Object/GameObject.hpp>
#include <resource/Prefab.hpp>
#include <component/attachToParent.hpp>
#include <courier/courier.hpp>

namespace of::component
{
	void Stats::setStats()
	{
		auto& health = mainStat[Enums::StatType::Health];
		health.max = health.current = health.getValue();
		auto& mana = mainStat[Enums::StatType::Mana];
		mana.max = mana.current = mana.getValue();
		auto& barrier = mainStat[Enums::StatType::BarrierStrength];
		barrier.max = barrier.getValue();
		barrier.current = 0;

		for (auto& it : statValues)
			it.second.value = it.second.getValue();


		for (auto& it : statChances)
			it.second.value = it.second.getValue();
	}

	void Stats::recalculateAttribute(of::combat::Attribute& attribute, const double& modifiedValue)
	{
		attribute.valueFromItems += modifiedValue;
	}

	void Stats::recalculateMainStat(of::combat::MainAttribute& attribute, const double& modifiedValue)
	{
		auto percent = attribute.current / attribute.max;
		attribute.modifier += modifiedValue;
		attribute.max = attribute.getValue();
		attribute.current = attribute.max * percent;
	}

	void Stats::recalculateStatValues(of::combat::StatAttribute& attribute, const double& modifiedValue)
	{
		attribute.modifier += modifiedValue;
		attribute.value = attribute.getValue();
	}

	void Stats::recalculateStatChances(of::combat::PercentualAttribute& attribute, const double& modifiedValue)
	{
		attribute.modifier += modifiedValue;
		attribute.value = attribute.getValue();
	}

	void Stats::recalculateStat(const Enums::StatType& attribute, const double& modifiedValue)
	{
		switch (attribute)
		{
		case Enums::StatType::Health:
		case Enums::StatType::Mana:
		case Enums::StatType::BarrierStrength:
			recalculateMainStat(mainStat[attribute], modifiedValue);
			break;
		case Enums::StatType::Power:
		case Enums::StatType::Toughness:
		case Enums::StatType::SpellPower:
			recalculateStatValues(statValues[attribute], modifiedValue);
			break;
		case Enums::StatType::CritDamage:
		case Enums::StatType::CritChange:
		case Enums::StatType::BarrierDuration:
		case Enums::StatType::Loot:
			recalculateStatChances(statChances[attribute], modifiedValue);
			break;
		default:
		{
			recalculateAttribute(attributes[attribute], modifiedValue);
			recalculateMainStat(mainStat[Enums::StatType::Health], 0);
			recalculateMainStat(mainStat[Enums::StatType::Mana], 0);
			recalculateMainStat(mainStat[Enums::StatType::BarrierStrength], 0);

			recalculateStatValues(statValues[Enums::StatType::Health], 0);
			recalculateStatValues(statValues[Enums::StatType::Mana], 0);
			recalculateStatValues(statValues[Enums::StatType::BarrierStrength], 0);

			recalculateStatChances(statChances[Enums::StatType::Health], 0);
			recalculateStatChances(statChances[Enums::StatType::Mana], 0);
			recalculateStatChances(statChances[Enums::StatType::BarrierStrength], 0);
			recalculateStatChances(statChances[Enums::StatType::BarrierStrength], 0);
		}
		}
	}


	void Stats::attached()
	{
		using namespace object::messaging;
		post(Topic::of(Topics::REQUEST_DATA), std::make_shared<RequestData>(Topic::of(Topics::REQUEST_DATA), typeId));
		if (subscriberId == 0)
		{
			subscriberId = of::courier::get().addSubscriber(of::courier::Topic::Update, of::courier::Subscriber(isAlive(), [this](const of::courier::Message& msg) {update(msg.get<float>()); }));
		}
	}

	void Stats::initialize()
	{

	}

	void Stats::deconstruct()
	{
		if (subscriberId != 0)
		{
			of::courier::get().removeSubscriber(of::courier::Topic::Update, subscriberId);
			subscriberId = 0;
		}
	}

	void Stats::onMessage(const object::messaging::Message& message)
	{
		using namespace of::object::messaging;
		if (message.messageTopic == Topic::of(Topics::TRANSFORM_SPEED_MODIFIER))
		{
			if (message.messageBody->bodyType == BodyType::FLOAT_PTR)
			{
				auto x = (FloatPtr*)message.messageBody.get();
				speedModifier = x->fp;
			}
		}
	}

	Stats::Stats() :
		// Take a look at Combat/Attribute.hpp for initializer list construction for attributes
		// and MainAttribute.hpp for mainStat
		attributes({
			{ Enums::StatType::Strength , {68, 13, 0, 2.5, &level} },
			{ Enums::StatType::Vitality , {92, 87, 0, 10, &level} },
			{ Enums::StatType::Defense , {48, 8, 0, 1.5, &level} },
			{ Enums::StatType::Focus , {11, 0, 0, 1.45, &level} },
			{ Enums::StatType::Intelligence , {48, 8, 0, 1.4, &level} },
			{ Enums::StatType::Luck , {1, 0, 0, 0.09, &level} },
			{ Enums::StatType::Wisdom , {68, 13, 0, 2.5, &level} },
			{ Enums::StatType::Charisma , {1, 0, 0 ,1, &level} },
			{ Enums::StatType::Speed , {1, 0, 0 ,1, &level} },
			}),
			mainStat({
				{Enums::StatType::Health, { { {attributes[Enums::StatType::Vitality], 0.91 }, {attributes[Enums::StatType::Defense], 0.07}, {attributes[Enums::StatType::Strength], 0.02}}}},
				{Enums::StatType::Mana, { { {attributes[Enums::StatType::Intelligence], 0.95 }, {attributes[Enums::StatType::Wisdom], 0.05}}}},
				{Enums::StatType::BarrierStrength, { { {attributes[Enums::StatType::Wisdom], 0.75 }, {attributes[Enums::StatType::Intelligence], 0.15}, {attributes[Enums::StatType::Vitality], 0.15}}}},
				}),
				statValues({
					{Enums::StatType::Power, { { {attributes[Enums::StatType::Strength], 0.95}, {attributes[Enums::StatType::Focus], 0.05}}}},
					{Enums::StatType::Toughness, { { {attributes[Enums::StatType::Defense], 0.95}, {attributes[Enums::StatType::Vitality], 0.05}}}},
					{Enums::StatType::SpellPower, { { {attributes[Enums::StatType::Wisdom], 0.92}, {attributes[Enums::StatType::Intelligence], 0.08}}}},
					}),
					statChances({
						{Enums::StatType::CritDamage, { { {attributes[Enums::StatType::Focus], 1} }, 1000, 2}},
						{Enums::StatType::CritChange, { { {attributes[Enums::StatType::Luck], 1}}, 100, 0}},
						{Enums::StatType::BarrierDuration, { { {attributes[Enums::StatType::Wisdom], 1}}, 7500, 0, 0, 1}},
						{Enums::StatType::Loot, { { {attributes[Enums::StatType::Luck], 1}}, 400, 0}},
						})
	{
		setStats();
	}

	Stats* Stats::copy() const
	{
		return new Stats(*this);
	}

	std::unique_ptr<of::component::Base> Stats::ucopy() const
	{
		return std::make_unique<Stats>(*this);
	}

	float Stats::getSpeed() const
	{
		return float(attributes.at(Enums::StatType::Speed).getStatValue());
	}

	void Stats::addModifier(const of::combat::Modifier& modifier)
	{
		buffAndDebuffs[modifier.attributeToModify].modifiers.push_back(modifier);
		recalculateStat(modifier.attributeToModify, modifier.statModification);
	}

	void Stats::removeModifier(const of::combat::Modifier& modifier)
	{
		auto& modifierList = buffAndDebuffs[modifier.attributeToModify].modifiers;
		auto it = std::find(modifierList.begin(), modifierList.end(), modifier);
		buffAndDebuffs[modifier.attributeToModify].modifiers.erase(it);
		recalculateStat(modifier.attributeToModify, -modifier.statModification);
	}

	void Stats::doEffects(const std::vector<of::combat::Effect>& newEffects, std::shared_ptr<Stats> owner)
	{
		for (of::combat::Effect effect : newEffects)
		{
			effect.owner = owner;
			effects[effect.ID].effectType = effect.effectType;
			effects[effect.ID].effectIcon = effect.effectIcon;
			effects[effect.ID].hiddenStack = effect.hideFromBuffsUI;
			effects[effect.ID].modifiers.push_back(effect);
		}
	}

	void Stats::doDamage(const double& weaponStrength, const double& damageCoef, const of::combat::Element& damageElement, std::shared_ptr<Stats> damageOwner)
	{
		auto trueDamage = weaponStrength * damageCoef * damageOwner->statValues[Enums::StatType::Power].getValue() / statValues[Enums::StatType::Toughness].getValue();
		auto critChance = statChances[Enums::StatType::CritChange].getValue() * 100.0;
		if (critChance > of::rng::get().randomDouble(0.0, 100.0))
		{
			auto critDamageMult = statChances[Enums::StatType::CritDamage].getValue();
			trueDamage *= critDamageMult;
		}
		of::engine::GetModule<of::logger::Logger>().getLogger("Component::Stats").Info("Damage dealt: " + std::to_string(trueDamage));
		mainStat[Enums::StatType::Health].current -= trueDamage * attunedTo.getElementModifier(damageElement.getModfile());
		if (mainStat[Enums::StatType::Health].current <= 0)
		{
			attachedOn->onDeath(damageOwner->attachedOn, 5);
			died = true;
		}
	}

	std::unordered_map<of::common::uuid, of::combat::EffectStack>& Stats::getEffects()
	{
		return effects;
	}

	size_t Stats::getLevel() const
	{
		return level;
	}

	void Stats::update(const float& dt)
	{
		if (died)
			return;
		for (auto& it : buffAndDebuffs)
		{
			recalculateStat(it.first, -it.second.tick(dt));
		}
		for (auto& it : effects)
		{
			if (it.second.modifiers.size() != 0)
			{
				if (it.second.effectType == of::combat::EffectType::TickDamage)
				{
					auto element = it.second.modifiers[0].effectElement;
					auto tickDamages = it.second.tick<of::combat::DamageEffect>(dt);
					double tickDamage = 0;
					for (auto& x : tickDamages)
						tickDamage += x.first.damage * x.second;

					for (auto& id : element.elementAttributes)
						tickDamage = barriers[id.first.uuid].doDamage(tickDamage, element.getElementModifier(id.first));


					mainStat[Enums::StatType::Health].current -= tickDamage * attunedTo.getElementModifier(element.getModfile());
				}
				else if (it.second.effectType == of::combat::EffectType::Healing)
				{

					auto element = it.second.modifiers[0].effectElement;
					auto tickDamages = it.second.tick<of::combat::DamageEffect>(dt);
					double tickDamage = 0;
					for (auto& x : tickDamages)
						tickDamage += x.first.damage * x.second;

					mainStat[Enums::StatType::Health].current += tickDamage * attunedTo.getElementModifier(element.getModfile());
				}
				else if (it.second.effectType == of::combat::EffectType::Barrier)
				{

					auto element = it.second.modifiers[0].effectElement;
					auto barrierValues = it.second.tick<of::combat::BarrierEffect>(dt);
					for (auto& barrier : barrierValues)
					{
						auto& b = barriers[element.ID];
						if (b.totalBarrier + barrier.first.barrierStrength > mainStat[Enums::StatType::BarrierStrength].max)
							barrier.first.barrierStrength = mainStat[Enums::StatType::BarrierStrength].max - b.totalBarrier;
						b.add(barrier.first.barrierDuration * (float)statChances[Enums::StatType::BarrierDuration].getValue(), barrier.first.barrierStrength);

					}
				}
				else if (it.second.effectType == of::combat::EffectType::VisualEffect)
				{
					auto vfxs = it.second.tick<of::combat::VisualEffect>(dt);
					for (auto& vfx : vfxs)
					{
						auto pref = of::engine::GetModule<of::file::Handler>().archive.request<of::resource::Prefab>(vfx.first.vfxPrefab);
						auto x = glm::vec3(0.f);
						auto go = pref->createNewInstance(x);
						go->add<AttachToParent>(attachedOn);
					}
				}
				else if (it.second.effectType == of::combat::EffectType::Modifier)
				{
					auto modifiers = it.second.tick<of::combat::ModifierEffect>(dt);
					for (auto& modif : modifiers)
					{
						if (!modif.first.applied)
						{
							addModifier(modif.first.modifier);
							modif.first.applied = true;
						}
					}
				}
			}
		}
		if (mainStat[Enums::StatType::Health].current > mainStat[Enums::StatType::Health].max)
			mainStat[Enums::StatType::Health].current = mainStat[Enums::StatType::Health].max;
		for (auto& it : barriers)
		{
			it.second.tick(dt);
		}
	}
};
