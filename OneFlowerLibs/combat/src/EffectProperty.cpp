#include <combat/effect/EffectProperty.hpp>

#include <resource/Prefab.hpp>
#include <file/Handler.hpp>

namespace of::combat
{
	void of::combat::VisualEffect::loadVfx()
	{
		of::engine::GetModule<of::file::Handler>().archive.request<of::resource::Prefab>(vfxPrefab);
	}
}
