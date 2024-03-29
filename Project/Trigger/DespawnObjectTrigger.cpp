#include "DespawnObjectTrigger.hpp"

#include <Object/ObjectInstanceHandler.hpp>

namespace Trigger
{
	void DespawnObjectTrigger::executeInternal()
	{
		Engine::GetModule<EngineModule::ObjectInstanceHandler>().removeObject(gameObjectToDespawn);
	}
	std::unique_ptr<Trigger> DespawnObjectTrigger::clone() const
	{
		return std::make_unique<DespawnObjectTrigger>(*this);
	}
}