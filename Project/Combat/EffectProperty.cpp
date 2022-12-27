#include "EffectProperty.hpp"

#include <resource/Prefab.hpp>
#include <file/Handler.hpp>

void Combat::VisualEffect::loadVfx()
{
	of::engine::GetModule<of::file::Handler>().archive.request<of::resource::Prefab>(vfxPrefab);
}
