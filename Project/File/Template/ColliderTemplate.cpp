#include "ColliderTemplate.hpp"

Core::uuid Interfaces::Trait<ColliderChunk>::typeId = Core::uuid("f581efed-f907-49e2-a3f0-6df1c35c641c");

Interfaces::TypeInfo ColliderChunk::getTrait() const
{
    return { Interfaces::Trait<ColliderChunk>::typeId };
}
