#include "WeaponItem.hpp"
#include <File/Asset/Manager.hpp>

void Items::Weapon::loadModel()
{
	mesh = Engine::GetModule<File::Asset::Manager>().requestor.request<Asset::Resource::Prefab>(modelId);
}
