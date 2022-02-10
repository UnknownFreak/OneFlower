#include "TileTemplate.hpp"

Core::uuid Interfaces::Trait<TileChunk>::typeId = Core::uuid("30e7ad6f-7b35-4cbb-bf1e-7470290c9381");

Interfaces::TypeInfo TileChunk::getTrait() const
{
	return { Interfaces::Trait<TileChunk>::typeId };
}
