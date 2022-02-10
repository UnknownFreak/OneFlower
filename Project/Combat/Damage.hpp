#ifndef Damage_HPP
#define Damage_HPP

#include <vector>

#include <Object/IBaseComponent.hpp>
#include <Object/Transform.hpp>
#include <Combat/Effect.hpp>
#include <Helpers/TickTimer.hpp>

namespace Component
{

	class Damage : public IBase<Damage>
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

	public:
		std::vector<File::Mod::ModFileUUIDHelper> effectsIds;
		File::Mod::ModFileUUIDHelper elementId;

		bool attachToOwner;
		// Buff/debuffs that get applied (includes DoTs)
		size_t maxTargets;
		bool eachTargetUnique;
		bool killWhenMaxTargetsHit;

		Core::TickTimer timeToLive;

		Core::TickTimer intervalPerHit;
		bool canLockNextFrame;
		Core::Vector2f direction;
		float speed;
		double damageCoef;
	public:
		std::shared_ptr<Component::Stats> owner;

		void setDirection(const Core::Vector2f& direction, const float& speed);
		void attachOn(GameObject* go);

		// Inherited via IBase
		virtual void onCollision(Interfaces::ICollider* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;

		virtual Damage* copy() const override;
		virtual std::unique_ptr<Base> ucopy() const override;

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
			ar(direction);
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
			ar(direction);
			ar(speed);
			ar(damageCoef);
			ar(elementId);
			loadEffects();
		}
	};
}

#endif