#include "EffectProperty.hpp"
#include <File/Asset/Manager.hpp>

void Combat::VisualEffect::loadVfx()
{
	of::engine::GetModule<File::Asset::Manager>().requestor.request<Asset::Resource::Prefab>(vfxPrefab);
}
