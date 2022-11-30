#include "WeaponItem.hpp"
#include <File/Asset/Manager.hpp>

void Items::Weapon::loadModel()
{
	mesh = of::engine::GetModule<File::Asset::Manager>().requestor.request<Asset::Resource::Prefab>(modelId);
}
