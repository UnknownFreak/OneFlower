#ifndef Damage_HPP
#define Damage_HPP

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include <vector>

#include <component/transform.hpp>
#include "Stats.hpp"
#include <combat/effect/Effect.hpp>
#include <timer/TickTimer.hpp>

namespace of::component
{
	class Damage : public Base
	{
		Transform* transform;
		bool hasLivedTooLong();
		bool hasHitEnoughEnemiesAndDestroy();
		std::vector<object::GameObject*> targetsHit;
		std::vector<of::combat::Effect> effects;
		bool lockNextFrame;
		bool locked;
		of::combat::Element damageElement;

		void loadEffects();

		virtual void onMessage(const of::object::messaging::Message& message) override;
		virtual void attached() override;
		virtual void initialize() override;
		virtual void deconstruct() override;

		size_t notifyIntervalPerHits = 0;

	public:
		std::vector<of::file::FileId> effectsIds;
		of::file::FileId elementId;

		bool attachToOwner;
		// Buff/debuffs that get applied (includes DoTs)
		size_t maxTargets;
		bool eachTargetUnique;
		bool killWhenMaxTargetsHit;

		of::timer::TickTimer timeToLive;

		of::timer::TickTimer intervalPerHit;
		bool canLockNextFrame;
		glm::vec2 direction;
		float speed;
		double damageCoef;
	public:
		std::shared_ptr<of::component::Stats> owner;

		void setDirection(const glm::vec2& direction, const float& speed);

		virtual void update(const float& fElapsedTime);

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		virtual Damage* copy() const override;
		virtual std::unique_ptr<Base> ucopy() const override;

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Damage";
		};

		static constexpr of::common::uuid typeId = "e7bfcebf-4147-4af8-b881-2ea64812700f";

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(effectsIds);
			ar(attachToOwner);
			ar(maxTargets);
			ar(eachTargetUnique);
			ar(killWhenMaxTargetsHit);
			ar(timeToLive);
			ar(intervalPerHit);
			ar(canLockNextFrame);
			ar(direction.x, direction.y);
			ar(speed);
			ar(damageCoef);
			ar(elementId);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(effectsIds);
			ar(attachToOwner);
			ar(maxTargets);
			ar(eachTargetUnique);
			ar(killWhenMaxTargetsHit);
			ar(timeToLive);
			ar(intervalPerHit);
			ar(canLockNextFrame);
			ar(direction.x, direction.y);
			ar(speed);
			ar(damageCoef);
			ar(elementId);
			loadEffects();
		}
	};
}

CEREAL_REGISTER_TYPE_WITH_NAME(of::component::Damage, "Component::Damage");
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::component::Base, of::component::Damage);
#endif