#include "WorldInstance.hpp"

of::common::uuid of::file::archive::Trait<File::Asset::Resource::Template::WorldInstance>::typeId = of::common::uuid("f57ee805-75e7-47ce-b852-d59a452c2338");
of::common::uuid of::file::archive::Trait<File::Asset::Resource::Template::ObjectChunk>::typeId = of::common::uuid("72f0e022-884a-4cc5-bc84-9a5f55cd9eb6");
namespace File::Asset::Resource::Template
{
	size_t WorldInstance::getLoadingCount() const
	{
		return tileAtlases.size() + prefabs.size() + tileInfo.size() + colliderInfo.size();
	}

	of::file::archive::TypeInfo WorldInstance::getTrait() const
	{
		return { of::file::archive::Trait<WorldInstance>::typeId };
	}

	of::file::archive::TypeInfo ObjectChunk::getTrait() const
	{
		return { of::file::archive::Trait<ObjectChunk>::typeId };
	}
}