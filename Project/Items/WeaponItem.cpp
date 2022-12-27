#include "WeaponItem.hpp"
#include <file/Handler.hpp>

#include <resource/Prefab.hpp>

void Items::Weapon::loadModel()
{
	mesh = of::engine::GetModule<of::file::Handler>().archive.request<of::resource::Prefab>(modelId);
}
