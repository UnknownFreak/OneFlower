#include "EffectProperty.hpp"
#include <File/AssetManagerCore.hpp>

void Combat::VisualEffect::loadVfx()
{
	Engine::GetModule<Asset::AssetManager>().requestor.request<Prefab>(vfxPrefab);
}
