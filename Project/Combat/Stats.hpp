#ifndef Stats_HPP
#define Stats_HPP

#include <unordered_map>

#include <object/component/IBaseComponent.hpp>
#include <Helpers/Enum/Attribute.hpp>
#include "Attribute.hpp"
#include "MainAttribute.hpp"

#include "Element.hpp"
#include "Barrier.hpp"
#include "Modifier.hpp"
#include "EffectStack.hpp"

namespace of::object::component
{

	class Stats : public IBase<Stats>
	{
		float* speedModifier;
		bool died = false;
		const size_t maxLevel = 100;
		size_t level = 1;

		std::unordered_map<Enums::Attribute, ::Combat::Attribute> attributes;
		std::unordered_map<Enums::Attribute, ::Combat::ModifierStack> buffAndDebuffs;
		std::unordered_map<of::common::uuid, ::Combat::EffectStack> effects;

		void setStats();
		void recalculateAttribute(Combat::Attribute& attribute, const double& modifiedValue);
		void recalculateMainStat(Combat::MainAttribute& attribute, const double& modifiedValue);
		void recalculateStatValues(Combat::StatAttribute& attribute, const double& modifiedValue);
		void recalculateStatChances(Combat::PercentualAttribute& attribute, const double& modifiedValue);
		void recalculateStat(const Enums::Attribute& attribute, const double& modifiedValue);

		virtual void onMessage(const messaging::Message& message) override;

	public:
		Combat::Element attunedTo;

		std::unordered_map<Enums::Attribute, Combat::MainAttribute> mainStat;
		std::unordered_map<Enums::Attribute, Combat::StatAttribute> statValues;
		std::unordered_map<Enums::Attribute, Combat::PercentualAttribute> statChances;
		std::unordered_map<of::common::uuid, Combat::Barrier> barriers;

		Stats();

		virtual Stats* copy() const override;
		virtual std::unique_ptr<Base> ucopy() const override;

		float getSpeed() const;
		void addModifier(const Combat::Modifier& modifier);
		void removeModifier(const Combat::Modifier& modifier);
		void doEffects(const std::vector<Combat::Effect>& effects, std::shared_ptr<Stats> owner);
		void doDamage(const double& weaponStrength, const double& damageCoef, const Combat::Element& damageElement, std::shared_ptr<Stats> owner);

		std::unordered_map<of::common::uuid, Combat::EffectStack>& getEffects();

		size_t getLevel() const;

		//void addItemStat();

		// Inherited via IBase
		virtual void onCollision(GameObject* the_collidee) override;

		virtual void Update() override;

		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

	};

}
CEREAL_REGISTER_TYPE(of::object::component::Stats);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::object::component::Base, of::object::component::Stats);

#endif