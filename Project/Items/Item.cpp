#include "Item.hpp"
#include <File/Resource/TextureLoader.hpp>

of::common::uuid Interfaces::Trait<Items::Base>::typeId = of::common::uuid("d2ab3ecd-a468-4170-bd8b-d4fdd6fd9235");

void Items::Base::loadIcon()
{
	iconTexture = of::engine::GetModule<File::Resource::Texture::Loader>().requestTexture(itemIconName, Globals::uiTexturePath);
}

Interfaces::TypeInfo Items::Base::getTrait() const
{
	return { Interfaces::Trait<Items::Base>::typeId };
}
