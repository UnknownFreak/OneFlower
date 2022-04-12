#include "WorldInstance.hpp"

Core::uuid Interfaces::Trait<File::Asset::Resource::Template::WorldInstance>::typeId = Core::uuid("f57ee805-75e7-47ce-b852-d59a452c2338");
Core::uuid Interfaces::Trait<File::Asset::Resource::Template::ObjectChunk>::typeId = Core::uuid("72f0e022-884a-4cc5-bc84-9a5f55cd9eb6");
namespace File::Asset::Resource::Template
{
	size_t WorldInstance::getLoadingCount() const
	{
		return tileAtlases.size() + prefabs.size() + tileInfo.size() + colliderInfo.size();
	}

	Interfaces::TypeInfo WorldInstance::getTrait() const
	{
		return { Interfaces::Trait<WorldInstance>::typeId };
	}

	Interfaces::TypeInfo ObjectChunk::getTrait() const
	{
		return { Interfaces::Trait<ObjectChunk>::typeId };
	}
}