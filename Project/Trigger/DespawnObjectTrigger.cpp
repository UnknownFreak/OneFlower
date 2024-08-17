#include "DespawnObjectTrigger.hpp"

#include <object/InstanceHandler.hpp>

namespace Trigger
{
	void DespawnObjectTrigger::executeInternal()
	{
		of::object::removeObject(gameObjectToDespawn);
	}
	std::unique_ptr<of::trigger::Trigger> DespawnObjectTrigger::clone() const
	{
		return std::make_unique<DespawnObjectTrigger>(*this);
	}
}