#include "SpawnObjectTrigger.hpp"

#include <file/Handler.hpp>
#include <resource/Prefab.hpp>

namespace Trigger
{
	void SpawnObjectTrigger::executeInternal()
	{
		auto prefab = of::engine::GetModule<of::file::Handler>().archive.requestShared<of::resource::Prefab>(prefabId);
		prefab->createNewInstance(position);
	}
	std::unique_ptr<of::trigger::Trigger> SpawnObjectTrigger::clone() const
	{
		return std::make_unique<SpawnObjectTrigger>(*this);
	}
}