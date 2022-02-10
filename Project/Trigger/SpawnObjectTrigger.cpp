#include "SpawnObjectTrigger.hpp"

#include <File/AssetManagerCore.hpp>
#include <File/Resource/Prefab.hpp>

namespace Trigger
{
	void SpawnObjectTrigger::executeInternal()
	{
		auto prefab = Engine::GetModule<Asset::AssetManager>().requestor.requestShared<Prefab>(prefabId);
		prefab->createNewInstance(position);
	}
	std::unique_ptr<Trigger> SpawnObjectTrigger::clone() const
	{
		return std::make_unique<SpawnObjectTrigger>(*this);
	}
}