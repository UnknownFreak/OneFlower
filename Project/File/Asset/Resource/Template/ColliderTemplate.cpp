#include "ColliderTemplate.hpp"

of::common::uuid Interfaces::Trait<File::Asset::Resource::Template::ColliderChunk>::typeId = of::common::uuid("f581efed-f907-49e2-a3f0-6df1c35c641c");

namespace File::Asset::Resource::Template
{
    Interfaces::TypeInfo ColliderChunk::getTrait() const
    {
        return { Interfaces::Trait<ColliderChunk>::typeId };
    }
}