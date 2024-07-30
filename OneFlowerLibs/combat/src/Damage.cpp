#include <component/damage.hpp>

#include <object/GameObject.hpp>
#include <file/Handler.hpp>
#include <courier/courier.hpp>

//#include <Items/Inventory.hpp>

namespace of::component
{

	void Damage::onMessage(const of::object::messaging::Message& message)
	{

		using namespace of::object::messaging;
		if (message.messageTopic == Topic::of(Topics::ON_COLLISION) && message.messageBody->bodyType == BodyType::GAMEOBJECT_PTR)
		{
			object::GameObject* the_collidee = (object::GameObject*)((GameObjectPtr*)message.messageBody.get())->go;
			if (the_collidee != owner->attachedOn)
			{
				if (std::find(targetsHit.begin(), targetsHit.end(), the_collidee) != targetsHit.end() && eachTargetUnique || targetsHit.size() == maxTargets)
					return;

				if (locked)
					return;

				auto* stats = the_collidee->get<of::component::Stats>();

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
							of::engine::GetModule<of::logger::Logger>().getLogger("Component::Damage").Error("An attack was performed without an equipped main weapon.");
						}
					}
					else
					*/

					{
						double theDamage = 15.0 * stats->getLevel();
						of::engine::GetModule<of::logger::Logger>().getLogger("Component::Damage").Warning("Attacking entity does not have any inventory and will use \"default \"15.0 weapon damage * level scaling for a total of (" + std::to_string(theDamage) + ")");
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

	void Damage::attached()
	{
		transform = attachedOn->get<Transform>();

		auto& courier = of::engine::GetModule<of::courier::Courier>();
		courier.addSubscriber(of::courier::Topic::Update, of::courier::Subscriber(instanceId, isAlive(), [this](const of::courier::Message& msg) {update(msg.get<float>()); }));
	}

	void Damage::initialize()
	{
	}

	void Damage::deconstruct()
	{
		auto& courier = of::engine::GetModule<of::courier::Courier>();
		courier.removeSubscriber(of::courier::Topic::Update, instanceId);
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

	std::unique_ptr<of::component::Base> Damage::ucopy() const
	{
		return std::make_unique<Damage>(*this);
	}
};
