#include <resource/WorldInstance.hpp>

of::common::uuid of::file::archive::Trait<of::resource::WorldInstance>::typeId = of::common::uuid("f57ee805-75e7-47ce-b852-d59a452c2338");
of::common::uuid of::file::archive::Trait<of::resource::ObjectChunk>::typeId = of::common::uuid("72f0e022-884a-4cc5-bc84-9a5f55cd9eb6");

namespace of::resource
{
	size_t WorldInstance::getLoadingCount() const
	{
		return prefabs.size() + navMesh.size() + worldGeometry.size() + objectChunk.size();
	}

	void WorldInstance::addTo(const WorldInstance& other, const bool& objectsOnly)
	{
		
		prefabs.reserve(prefabs.size() + other.prefabs.size());
		prefabs.insert(prefabs.end(), other.prefabs.begin(), other.prefabs.end());
		objectChunk.reserve(objectChunk.size() + other.objectChunk.size());
		objectChunk.insert(objectChunk.end(), other.objectChunk.begin(), other.objectChunk.end());
		
		if (objectsOnly)
			return;
		
		navMesh.reserve(navMesh.size() + other.navMesh.size());
		navMesh.insert(navMesh.end(), other.navMesh.begin(), other.navMesh.end());

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