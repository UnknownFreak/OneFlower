#include "TileTemplate.hpp"

of::common::uuid of::file::archive::Trait<File::Asset::Resource::Template::TileChunk>::typeId = of::common::uuid("30e7ad6f-7b35-4cbb-bf1e-7470290c9381");

namespace File::Asset::Resource::Template
{
	of::file::archive::TypeInfo TileChunk::getTrait() const
	{
		return { of::file::archive::Trait<TileChunk>::typeId };
	}
}