#ifndef Damage_HPP
#define Damage_HPP

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include <vector>

#include <object/component/Transform.hpp>
#include "Stats.hpp"
#include <Combat/Effect.hpp>
#include <resource/TickTimer.hpp>

namespace of::object::component
{
	class Damage : public Base
	{
		Transform* transform;
		bool hasLivedTooLong();
		bool hasHitEnoughEnemiesAndDestroy();
		std::vector<GameObject*> targetsHit;
		std::vector<::Combat::Effect> effects;
		bool lockNextFrame;
		bool locked;
		Combat::Element damageElement;

		void loadEffects();

		virtual void onMessage(const of::object::messaging::Message& message) override;

	public:
		std::vector<of::file::FileId> effectsIds;
		of::file::FileId elementId;

		bool attachToOwner;
		// Buff/debuffs that get applied (includes DoTs)
		size_t maxTargets;
		bool eachTargetUnique;
		bool killWhenMaxTargetsHit;

		of::resource::TickTimer timeToLive;

		of::resource::TickTimer intervalPerHit;
		bool canLockNextFrame;
		glm::vec2 direction;
		float speed;
		double damageCoef;
	public:
		std::shared_ptr<of::object::component::Stats> owner;

		void setDirection(const glm::vec2& direction, const float& speed);
		void attachOn(GameObject* go);

		// Inherited via IBase
		virtual void onCollision(GameObject* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;

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

CEREAL_REGISTER_TYPE_WITH_NAME(of::object::component::Damage, "Component::Damage");
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::object::component::Base, of::object::component::Damage);
#endif