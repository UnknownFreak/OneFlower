#include "DespawnObjectTrigger.hpp"

#include <object/InstanceHandler.hpp>

namespace Trigger
{
	void DespawnObjectTrigger::executeInternal()
	{
		of::engine::GetModule<of::object::InstanceHandler>().removeObject(gameObjectToDespawn);
	}
	std::unique_ptr<of::resource::trigger::Trigger> DespawnObjectTrigger::clone() const
	{
		return std::make_unique<DespawnObjectTrigger>(*this);
	}
}