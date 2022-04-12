#include "EffectProperty.hpp"
#include <File/Asset/Manager.hpp>

void Combat::VisualEffect::loadVfx()
{
	Engine::GetModule<File::Asset::Manager>().requestor.request<Asset::Resource::Prefab>(vfxPrefab);
}
