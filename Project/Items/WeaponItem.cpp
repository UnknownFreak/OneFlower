#include "WeaponItem.hpp"
#include <file/Handler.hpp>

#include <File/Asset/Resource/Prefab.hpp>

void Items::Weapon::loadModel()
{
	mesh = of::engine::GetModule<of::file::Handler>().archive.request<Asset::Resource::Prefab>(modelId);
}
