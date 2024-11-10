#include <combat/effect/Effect.hpp>
#include <asset/asset.hpp>

of::common::uuid of::asset::Trait<of::combat::Effect>::typeId = of::common::uuid("ce4cf3dd-435b-41a3-912f-925cfaa8f6b8");

namespace of::combat
{

	Element Effect::getElement()
	{
		return asset::getAssetRequestor().requestUniqueInstance<Element>(effectElememtId);
	}

	Effect::Effect() : IAsset()
	{
	}

	of::asset::TypeInfo Effect::getTrait() const
	{
		return of::asset::TypeInfo{ of::asset::Trait<Effect>::typeId };
	}
};
