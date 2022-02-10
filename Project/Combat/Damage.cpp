#include "Damage.hpp"

#include <Object/GameObject.hpp>
#include <Object/ObjectInstanceHandler.hpp>
#include <Physics/Colliders/EntityCollider.hpp>
#include <File/AssetManagerCore.hpp>
#include <Items/Inventory.hpp>


Enums::ComponentType Component::IBase<Component::Damage>::typeID = Enums::ComponentType::Damage;
Core::String Component::IBase<Component::Damage>::componentName = "Damage";

namespace Component
{
	bool Damage::hasLivedTooLong()
	{
		return timeToLive.maxTime > 0 && timeToLive.ready();
	}

	bool Damage::hasHitEnoughEnemiesAndDestroy()
	{
		return targetsHit.size() == maxTargets && killWhenMaxTargetsHit;
	}

	void Damage::loadEffects()
	{
		for (auto& id : effectsIds)
			effects.push_back(Engine::GetModule<Asset::AssetManager>().requestor.requestUniqueInstance<Combat::Effect>(id));
		damageElement = Engine::GetModule<Asset::AssetManager>().requestor.requestUniqueInstance<Combat::Element>(elementId);
	}

	void Damage::setDirection(const Core::Vector2f& newDirection, const float& newSpeed)
	{
		direction = newDirection;
		speed = newSpeed;
	}

	void Damage::attachOn(GameObject* go)
	{
		Base::attachOn(go);
		transform = go->getComponent<Transform>();
	}

	void Damage::Update()
	{
		if (hasHitEnoughEnemiesAndDestroy() || hasLivedTooLong())
		{
			attachedOn->onDeath(nullptr);
		}
		if (lockNextFrame)
		{
			intervalPerHit.reset(true);
			locked = true;
		}
	}

	void Damage::Simulate(const float& fElapsedTime)
	{
		timeToLive.tick(fElapsedTime);
		if (intervalPerHit.tick(fElapsedTime))
			locked = false;
		transform->move(direction * (speed * fElapsedTime));
	}

	void Damage::onDeath()
	{
	}

	Damage* Damage::copy() const
	{
		return new Damage(*this);
	}

	std::unique_ptr<Component::Base> Damage::ucopy() const
	{
		return std::make_unique<Damage>(*this);
	}

	void Damage::onCollision(Interfaces::ICollider* the_collidee)
	{
		Collider* x = (Collider*)the_collidee;
		//if (x->attachedOn != owner->attachedOn)
		{
			if (std::find(targetsHit.begin(), targetsHit.end(), x->attachedOn) != targetsHit.end() && eachTargetUnique || targetsHit.size() == maxTargets)
				return;

			if (locked)
				return;

			auto* stats = x->attachedOn->getComponent<Component::Stats>();
			auto* inventory = x->attachedOn->getComponent<Component::Inventory>();

			if (stats)
			{
				stats->doEffects(effects, owner);

				if (inventory)
				{
					if (inventory->mainHand)
					{
						double theDamage = inventory->mainHand->weaponStrength;
						if (inventory->offHand)
							theDamage += inventory->offHand->weaponStrength;
						stats->doDamage(theDamage, damageCoef, damageElement, owner);
					}
					else
					{
						Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Component::Damage").Error("An attack was performed without an equipped main weapon.");
					}
				}
				else
				{
					double theDamage = 15.0 * stats->getLevel();
					Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Component::Damage").Warning("Attacking entity does not have any inventory and will use default 15.0 weapon damage * level scaling for a total of (" + std::to_string(theDamage) + ")");
					stats->doDamage(theDamage, damageCoef, damageElement, owner);
				}

				targetsHit.push_back(x->attachedOn);
				if (canLockNextFrame)
					lockNextFrame = true;
			}
		}
	}
};
