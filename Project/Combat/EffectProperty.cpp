#include "EffectProperty.hpp"

#include <File/Asset/Resource/Prefab.hpp>
#include <file/Handler.hpp>

void Combat::VisualEffect::loadVfx()
{
	of::engine::GetModule<of::file::Handler>().archive.request<Asset::Resource::Prefab>(vfxPrefab);
}
