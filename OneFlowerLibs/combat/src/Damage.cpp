#include <object/component/Damage.hpp>

#include <Object/GameObject.hpp>
#include <module/ObjectInstanceHandler.hpp>
#include <file/Handler.hpp>

//#include <Items/Inventory.hpp>

namespace of::object::component
{

	void Damage::onMessage(const of::object::messaging::Message& message)
	{

		using namespace of::object::messaging;
		if (message.messageTopic == Topic::of(Topics::ON_COLLISION) && message.messageBody->bodyType == BodyType::GAMEOBJECT_PTR)
		{
			GameObject* the_collidee = (GameObject*)((GameObjectPtr*)message.messageBody.get())->go;
			if (the_collidee != owner->attachedOn)
			{
				if (std::find(targetsHit.begin(), targetsHit.end(), the_collidee) != targetsHit.end() && eachTargetUnique || targetsHit.size() == maxTargets)
					return;

				if (locked)
					return;

				auto* stats = the_collidee->get<of::object::component::Stats>();

				/*
				
				auto* inventory = the_collidee->get<of::object::component::Inventory>();
				*/
				if (stats)
				{
					stats->doEffects(effects, owner);
					/*
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
					*/

					{
						double theDamage = 15.0 * stats->getLevel();
						of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Component::Damage").Warning("Attacking entity does not have any inventory and will use \"default \"15.0 weapon damage * level scaling for a total of (" + std::to_string(theDamage) + ")");
						stats->doDamage(theDamage, damageCoef, damageElement, owner);
					}

					targetsHit.push_back(the_collidee);
					if (canLockNextFrame)
						lockNextFrame = true;
				}
			}

		}

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
			effects.push_back(of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<of::combat::Effect>(id));
		damageElement = of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<of::combat::Element>(elementId);
	}

	void component::Damage::initialize()
	{
		transform = attachedOn->get<Transform>();
	}

	void Damage::setDirection(const glm::vec2& newDirection, const float& newSpeed)
	{
		direction = newDirection;
		speed = newSpeed;
	}

	void Damage::update(const float& fElapsedTime)
	{

		timeToLive.tick(fElapsedTime);
		if (intervalPerHit.tick(fElapsedTime))
			locked = false;
		transform->move(direction * (speed * fElapsedTime));

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

	Damage* Damage::copy() const
	{
		return new Damage(*this);
	}

	std::unique_ptr<of::object::component::Base> Damage::ucopy() const
	{
		return std::make_unique<Damage>(*this);
	}
};
