#include "TileTemplate.hpp"

Core::uuid Interfaces::Trait<File::Asset::Resource::Template::TileChunk>::typeId = Core::uuid("30e7ad6f-7b35-4cbb-bf1e-7470290c9381");

namespace File::Asset::Resource::Template
{
	Interfaces::TypeInfo TileChunk::getTrait() const
	{
		return { Interfaces::Trait<TileChunk>::typeId };
	}
}