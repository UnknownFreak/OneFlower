#include "SpawnObjectTrigger.hpp"

#include <File/Asset/Manager.hpp>
#include <File/Asset/Resource/Prefab.hpp>

namespace Trigger
{
	void SpawnObjectTrigger::executeInternal()
	{
		auto prefab = of::engine::GetModule<File::Asset::Manager>().requestor.requestShared<Asset::Resource::Prefab>(prefabId);
		prefab->createNewInstance(position);
	}
	std::unique_ptr<Trigger> SpawnObjectTrigger::clone() const
	{
		return std::make_unique<SpawnObjectTrigger>(*this);
	}
}