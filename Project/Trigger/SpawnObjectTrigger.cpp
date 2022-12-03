#include "SpawnObjectTrigger.hpp"

#include <file/Handler.hpp>
#include <File/Asset/Resource/Prefab.hpp>

namespace Trigger
{
	void SpawnObjectTrigger::executeInternal()
	{
		auto prefab = of::engine::GetModule<of::file::Handler>().archive.requestShared<Asset::Resource::Prefab>(prefabId);
		prefab->createNewInstance(position);
	}
	std::unique_ptr<Trigger> SpawnObjectTrigger::clone() const
	{
		return std::make_unique<SpawnObjectTrigger>(*this);
	}
}