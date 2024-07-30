#ifndef Stats_HPP
#define Stats_HPP

#include <unordered_map>

#include <component/base.hpp>

#include <combat/attribute/StatType.hpp>
#include <combat/attribute/Attribute.hpp>
#include <combat/attribute/MainAttribute.hpp>

#include <combat/Element.hpp>
#include <combat/Barrier.hpp>
#include <combat/Modifier.hpp>
#include <combat/effect/EffectStack.hpp>

namespace of::component
{

	class Stats : public Base
	{
		float* speedModifier;
		bool died = false;
		const size_t maxLevel = 100;
		size_t level = 1;

		std::unordered_map<Enums::StatType, of::combat::Attribute> attributes;
		std::unordered_map<Enums::StatType, of::combat::ModifierStack> buffAndDebuffs;
		std::unordered_map<of::common::uuid, of::combat::EffectStack> effects;

		void setStats();
		void recalculateAttribute(of::combat::Attribute& attribute, const double& modifiedValue);
		void recalculateMainStat(of::combat::MainAttribute& attribute, const double& modifiedValue);
		void recalculateStatValues(of::combat::StatAttribute& attribute, const double& modifiedValue);
		void recalculateStatChances(of::combat::PercentualAttribute& attribute, const double& modifiedValue);
		void recalculateStat(const Enums::StatType& attribute, const double& modifiedValue);

		virtual void onMessage(const object::messaging::Message& message) override;

		virtual void attached() override;
		virtual void initialize() override;
		virtual void deconstruct() override;

	public:
		of::combat::Element attunedTo;

		std::unordered_map<Enums::StatType, of::combat::MainAttribute> mainStat;
		std::unordered_map<Enums::StatType, of::combat::StatAttribute> statValues;
		std::unordered_map<Enums::StatType, of::combat::PercentualAttribute> statChances;
		std::unordered_map<of::common::uuid, of::combat::Barrier> barriers;

		Stats();

		virtual Stats* copy() const override;
		virtual std::unique_ptr<Base> ucopy() const override;

		float getSpeed() const;
		void addModifier(const of::combat::Modifier& modifier);
		void removeModifier(const of::combat::Modifier& modifier);
		void doEffects(const std::vector<of::combat::Effect>& effects, std::shared_ptr<Stats> owner);
		void doDamage(const double& weaponStrength, const double& damageCoef, const of::combat::Element& damageElement, std::shared_ptr<Stats> owner);

		std::unordered_map<of::common::uuid, of::combat::EffectStack>& getEffects();

		size_t getLevel() const;

		//void addItemStat();

		virtual void update(const float& fElapsedTime);

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Stats";
		};

		static constexpr of::common::uuid typeId = "7fa92fde-ab34-4477-a9db-0b590f51b7b9";
	};

}
CEREAL_REGISTER_TYPE(of::component::Stats);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::component::Base, of::component::Stats);

#endif