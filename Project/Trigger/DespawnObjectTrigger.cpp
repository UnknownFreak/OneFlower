#include "DespawnObjectTrigger.hpp"

#include <module/ObjectInstanceHandler.hpp>

namespace Trigger
{
	void DespawnObjectTrigger::executeInternal()
	{
		of::engine::GetModule<of::module::ObjectInstanceHandler>().removeObject(gameObjectToDespawn);
	}
	std::unique_ptr<of::resource::trigger::Trigger> DespawnObjectTrigger::clone() const
	{
		return std::make_unique<DespawnObjectTrigger>(*this);
	}
}