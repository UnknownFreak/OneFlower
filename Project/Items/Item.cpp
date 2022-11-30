#include "Item.hpp"
#include <module/ModuleManager.hpp>
#include <module/resource/TextureLoader.hpp>

of::common::uuid Interfaces::Trait<Items::Base>::typeId = of::common::uuid("d2ab3ecd-a468-4170-bd8b-d4fdd6fd9235");

void Items::Base::loadIcon()
{
	iconTexture = of::engine::GetModule<of::module::texture::Loader>().requestTexture(itemIconName, of::module::Settings::uiTexturePath);
}

Interfaces::TypeInfo Items::Base::getTrait() const
{
	return { Interfaces::Trait<Items::Base>::typeId };
}
