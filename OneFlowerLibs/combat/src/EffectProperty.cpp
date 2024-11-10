#include <combat/effect/EffectProperty.hpp>

#include <resource/Prefab.hpp>
#include <asset/asset.hpp>

namespace of::combat
{
	void of::combat::VisualEffect::loadVfx()
	{
		asset::getAssetRequestor().request<of::resource::Prefab>(vfxPrefab);
	}
}
