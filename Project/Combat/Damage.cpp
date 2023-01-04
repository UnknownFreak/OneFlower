#include "Damage.hpp"

#include <Object/GameObject.hpp>
#include <module/ObjectInstanceHandler.hpp>
#include <file/Handler.hpp>
#include <Items/Inventory.hpp>

//of::common::uuid of::object::component::IBase<of::object::component::Damage>::typeID = of::common::uuid("e7bfcebf-4147-4af8-b881-2ea64812700f");
//of::common::String of::object::component::IBase<of::object::component::Damage>::componentName = "Damage";

namespace of::object::component
{

	void onMessage(const of::object::messaging::Message&)
	{
	}

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
			effects.push_back(of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<Combat::Effect>(id));
		damageElement = of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<Combat::Element>(elementId);
	}

	void component::Damage::onMessage(const of::object::messaging::Message&)
	{
	}

	void Damage::setDirection(const glm::vec2& newDirection, const float& newSpeed)
	{
		direction = newDirection;
		speed = newSpeed;
	}

	void Damage::attachOn(GameObject* go)
	{
		Base::attachOn(go);
		transform = go->get<Transform>();
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

	std::unique_ptr<of::object::component::Base> Damage::ucopy() const
	{
		return std::make_unique<Damage>(*this);
	}

	void Damage::onCollision(GameObject* the_collidee)
	{
		if (the_collidee != owner->attachedOn)
		{
			if (std::find(targetsHit.begin(), targetsHit.end(), the_collidee) != targetsHit.end() && eachTargetUnique || targetsHit.size() == maxTargets)
				return;

			if (locked)
				return;

			auto* stats = the_collidee ->get<of::object::component::Stats>();
			auto* inventory = the_collidee->get<of::object::component::Inventory>();

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
						of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Component::Damage").Error("An attack was performed without an equipped main weapon.");
					}
				}
				else
				{
					double theDamage = 15.0 * stats->getLevel();
					of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Component::Damage").Warning("Attacking entity does not have any inventory and will use /default /15.0 weapon damage * level scaling for a total of (" + std::to_string(theDamage) + ")");
					stats->doDamage(theDamage, damageCoef, damageElement, owner);
				}
			
				targetsHit.push_back(the_collidee);
				if (canLockNextFrame)
					lockNextFrame = true;
			}
		}
	}
};
