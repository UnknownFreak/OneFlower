#include "Stats.hpp"
#include <File/AssetManagerCore.hpp>

#include <Object/GameObject.hpp>
#include "AttachToParent.hpp"

Enums::ComponentType Component::IBase<Component::Stats>::typeID = Enums::ComponentType::Vitality;
Core::String Component::IBase<Component::Stats>::componentName = "Stats";

void Component::Stats::setStats()
{
	auto& health = mainStat[Enums::Attribute::Health];
	health.max = health.current = health.getValue();
	auto& mana = mainStat[Enums::Attribute::Mana];
	mana.max = mana.current = mana.getValue();
	auto& barrier = mainStat[Enums::Attribute::BarrierStrength];
	barrier.max = barrier.getValue();
	barrier.current = 0;

	for (auto& it : statValues)
		it.second.value = it.second.getValue();


	for (auto& it : statChances)
		it.second.value = it.second.getValue();
}

void Component::Stats::recalculateAttribute(Combat::Attribute& attribute, const double& modifiedValue)
{
	attribute.valueFromItems += modifiedValue;
}

void Component::Stats::recalculateMainStat(Combat::MainAttribute& attribute, const double& modifiedValue)
{
	auto percent = attribute.current / attribute.max;
	attribute.modifier += modifiedValue;
	attribute.max = attribute.getValue();
	attribute.current = attribute.max * percent;
}

void Component::Stats::recalculateStatValues(Combat::StatAttribute& attribute, const double& modifiedValue)
{
	attribute.modifier += modifiedValue;
	attribute.value = attribute.getValue();
}

void Component::Stats::recalculateStatChances(Combat::PercentualAttribute& attribute, const double& modifiedValue)
{
	attribute.modifier += modifiedValue;
	attribute.value = attribute.getValue();
}

void Component::Stats::recalculateStat(const Enums::Attribute& attribute, const double& modifiedValue)
{
	switch (attribute)
	{
	case Enums::Attribute::Health:
	case Enums::Attribute::Mana:
	case Enums::Attribute::BarrierStrength:
		recalculateMainStat(mainStat[attribute], modifiedValue);
		break;
	case Enums::Attribute::Power:
	case Enums::Attribute::Toughness:
	case Enums::Attribute::SpellPower:
		recalculateStatValues(statValues[attribute], modifiedValue);
		break;
	case Enums::Attribute::CritDamage:
	case Enums::Attribute::CritChange:
	case Enums::Attribute::BarrierDuration:
	case Enums::Attribute::Loot:
		recalculateStatChances(statChances[attribute], modifiedValue);
		break;
	default:
	{
		recalculateAttribute(attributes[attribute], modifiedValue);
		recalculateMainStat(mainStat[Enums::Attribute::Health], 0);
		recalculateMainStat(mainStat[Enums::Attribute::Mana], 0);
		recalculateMainStat(mainStat[Enums::Attribute::BarrierStrength], 0);

		recalculateStatValues(statValues[Enums::Attribute::Health], 0);
		recalculateStatValues(statValues[Enums::Attribute::Mana], 0);
		recalculateStatValues(statValues[Enums::Attribute::BarrierStrength], 0);

		recalculateStatChances(statChances[Enums::Attribute::Health], 0);
		recalculateStatChances(statChances[Enums::Attribute::Mana], 0);
		recalculateStatChances(statChances[Enums::Attribute::BarrierStrength], 0);
		recalculateStatChances(statChances[Enums::Attribute::BarrierStrength], 0);
	}
	}
}

Component::Stats::Stats():
// Take a look at Combat/Attribute.hpp for initializer list construction for attributes
// and MainAttribute.hpp for mainStat
	attributes({
		{ Enums::Attribute::Strength , {68, 13, 0, 2.5, &level} },
		{ Enums::Attribute::Vitality , {92, 87, 0, 10, &level} },
		{ Enums::Attribute::Defense , {48, 8, 0, 1.5, &level} },
		{ Enums::Attribute::Focus , {11, 0, 0, 1.45, &level} },
		{ Enums::Attribute::Intelligence , {48, 8, 0, 1.4, &level} },
		{ Enums::Attribute::Luck , {1, 0, 0, 0.09, &level} },
		{ Enums::Attribute::Wisdom , {68, 13, 0, 2.5, &level} },
		{ Enums::Attribute::Charisma , {1, 0, 0 ,1, &level} },
		{ Enums::Attribute::Speed , {1, 0, 0 ,1, &level} },
		}),
	mainStat({
		{Enums::Attribute::Health, { { {attributes[Enums::Attribute::Vitality], 0.91 }, {attributes[Enums::Attribute::Defense], 0.07}, {attributes[Enums::Attribute::Strength], 0.02}}}},
		{Enums::Attribute::Mana, { { {attributes[Enums::Attribute::Intelligence], 0.95 }, {attributes[Enums::Attribute::Wisdom], 0.05}}}},
		{Enums::Attribute::BarrierStrength, { { {attributes[Enums::Attribute::Wisdom], 0.75 }, {attributes[Enums::Attribute::Intelligence], 0.15}, {attributes[Enums::Attribute::Vitality], 0.15}}}},
		}),
	statValues({
		{Enums::Attribute::Power, { { {attributes[Enums::Attribute::Strength], 0.95}, {attributes[Enums::Attribute::Focus], 0.05}}}},
		{Enums::Attribute::Toughness, { { {attributes[Enums::Attribute::Defense], 0.95}, {attributes[Enums::Attribute::Vitality], 0.05}}}},
		{Enums::Attribute::SpellPower, { { {attributes[Enums::Attribute::Wisdom], 0.92}, {attributes[Enums::Attribute::Intelligence], 0.08}}}},
	}),
	statChances({
		{Enums::Attribute::CritDamage, { { {attributes[Enums::Attribute::Focus], 1} }, 1000, 2}},
		{Enums::Attribute::CritChange, { { {attributes[Enums::Attribute::Luck], 1}}, 100, 0}},
		{Enums::Attribute::BarrierDuration, { { {attributes[Enums::Attribute::Wisdom], 1}}, 7500, 0, 0, 1}},
		{Enums::Attribute::Loot, { { {attributes[Enums::Attribute::Luck], 1}}, 400, 0}},
	})
{
	setStats();
}

Component::Stats* Component::Stats::copy() const
{
	return new Stats(*this);
}

std::unique_ptr<Component::Base> Component::Stats::ucopy() const
{
	return std::make_unique<Stats>(*this);
}

float Component::Stats::getSpeed() const
{
	return float(attributes.at(Enums::Attribute::Speed).getStatValue());
}

void Component::Stats::addModifier(const Combat::Modifier& modifier)
{
	buffAndDebuffs[modifier.attributeToModify].modifiers.push_back(modifier);
	recalculateStat(modifier.attributeToModify, modifier.statModification);
}

void Component::Stats::removeModifier(const Combat::Modifier& modifier)
{
	auto& modifierList = buffAndDebuffs[modifier.attributeToModify].modifiers;
	auto it = std::find(modifierList.begin(), modifierList.end(), modifier);
	buffAndDebuffs[modifier.attributeToModify].modifiers.erase(it);
	recalculateStat(modifier.attributeToModify, -modifier.statModification);
}

void Component::Stats::doEffects(const std::vector<Combat::Effect>& newEffects, std::shared_ptr<Stats> owner)
{
	for (Combat::Effect effect : newEffects)
	{
		effect.owner = owner;
		effects[effect.ID].effectType = effect.effectType;
		effects[effect.ID].effectIcon = effect.effectIcon;
		effects[effect.ID].hiddenStack = effect.hideFromBuffsUI;
		effects[effect.ID].modifiers.push_back(effect);
	}
}

void Component::Stats::doDamage(const double& weaponStrength, const double& damageCoef, const Combat::Element& damageElement, std::shared_ptr<Stats> damageOwner)
{
	auto trueDamage = weaponStrength * damageCoef * damageOwner->statValues[Enums::Attribute::Power].getValue() / statValues[Enums::Attribute::Toughness].getValue();
	auto critChance = statChances[Enums::Attribute::CritChange].getValue() * 100.0;
	if ( critChance > Engine::GetModule<EngineModule::RandomGen>().random_double(0.0, 100.0))
	{
		auto critDamageMult = statChances[Enums::Attribute::CritDamage].getValue();
		trueDamage *= critDamageMult;
	}
	Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Damage dealt: " + std::to_string(trueDamage));
	mainStat[Enums::Attribute::Health].current -= trueDamage * attunedTo.getElementModifier(damageElement.getModfile());
	if (mainStat[Enums::Attribute::Health].current <= 0)
	{
		attachedOn->onDeath(damageOwner->attachedOn, 5);
		died = true;
	}
}

std::unordered_map<Core::uuid, Combat::EffectStack>& Component::Stats::getEffects()
{
	return effects;
}

size_t Component::Stats::getLevel() const
{
	return level;
}

void Component::Stats::detach()
{
	auto t = attachedOn->getComponent<Transform>();
	if(t)
	{
		t->stats = nullptr;
	}
}

void Component::Stats::attachOn(GameObject* go)
{
	Base::attachOn(go);
	go->getComponent<Component::Transform>()->stats = this;
}

void Component::Stats::onCollision(Interfaces::ICollider* )
{
}

void Component::Stats::Update()
{
}

void Component::Stats::Simulate(const float& dt)
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
			if (it.second.effectType == Enums::EffectType::TickDamage)
			{
				auto element = it.second.modifiers[0].effectElement;
				auto tickDamages = it.second.tick<Combat::DamageEffect>(dt);
				double tickDamage = 0;
				for (auto& x : tickDamages)
					tickDamage += x.first.damage * x.second;

				for(auto& id : element.elementAttributes)
					tickDamage = barriers[id.first.uuid].doDamage(tickDamage, element.getElementModifier(id.first));


				mainStat[Enums::Attribute::Health].current -= tickDamage * attunedTo.getElementModifier(element.getModfile());
			}
			else if (it.second.effectType == Enums::EffectType::Healing)
			{

				auto element = it.second.modifiers[0].effectElement;
				auto tickDamages = it.second.tick<Combat::DamageEffect>(dt);
				double tickDamage = 0;
				for (auto& x : tickDamages)
					tickDamage += x.first.damage * x.second;

				mainStat[Enums::Attribute::Health].current += tickDamage * attunedTo.getElementModifier(element.getModfile());
			}
			else if (it.second.effectType == Enums::EffectType::Barrier)
			{

				auto element = it.second.modifiers[0].effectElement;
				auto barrierValues = it.second.tick<Combat::BarrierEffect>(dt);
				for (auto& barrier : barrierValues)
				{
					auto& b = barriers[element.ID];
					if (b.totalBarrier + barrier.first.barrierStrength > mainStat[Enums::Attribute::BarrierStrength].max)
						barrier.first.barrierStrength = mainStat[Enums::Attribute::BarrierStrength].max - b.totalBarrier;
					b.add(barrier.first.barrierDuration * (float)statChances[Enums::Attribute::BarrierDuration].getValue(), barrier.first.barrierStrength);

				}
			}
			else if (it.second.effectType == Enums::EffectType::VisualEffect)
			{
				auto vfxs = it.second.tick<Combat::VisualEffect>(dt);
				for (auto& vfx : vfxs)
				{
					auto pref = Engine::GetModule<Asset::AssetManager>().requestor.request<Prefab>(vfx.first.vfxPrefab);
					auto x = Core::Vector3f{ 0,0,0 };
					auto go = pref->createNewInstance(x);
					go->addComponent<AttachToParent>(attachedOn);
				}
			}
			else if (it.second.effectType == Enums::EffectType::Modifier)
			{
				auto modifiers = it.second.tick<Combat::ModifierEffect>(dt);
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
	if (mainStat[Enums::Attribute::Health].current > mainStat[Enums::Attribute::Health].max)
		mainStat[Enums::Attribute::Health].current = mainStat[Enums::Attribute::Health].max;
	for (auto& it : barriers)
	{
		it.second.tick(dt);
	}
}

void Component::Stats::onDeath()
{
}