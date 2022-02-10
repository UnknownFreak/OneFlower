#include "WeaponItem.hpp"
#include <File/AssetManagerCore.hpp>

void Items::Weapon::loadModel()
{
	mesh = Engine::GetModule<Asset::AssetManager>().requestor.request<Prefab>(modelId);
}
