#include "ColliderTemplate.hpp"

of::common::uuid of::file::archive::Trait<File::Asset::Resource::Template::ColliderChunk>::typeId = of::common::uuid("f581efed-f907-49e2-a3f0-6df1c35c641c");

namespace File::Asset::Resource::Template
{
    of::file::archive::TypeInfo ColliderChunk::getTrait() const
    {
        return { of::file::archive::Trait<ColliderChunk>::typeId };
    }
}