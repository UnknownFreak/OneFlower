#include "WeaponItem.hpp"
#include <asset/asset.hpp>

#include <resource/Prefab.hpp>

void Items::Weapon::loadModel()
{
	mesh = of::asset::getAssetRequestor().request<of::resource::Prefab>(modelId);
}
