#include "Item.hpp"
#include <File/Resource/TextureLoader.hpp>

Core::uuid Interfaces::Trait<Items::Base>::typeId = Core::uuid("d2ab3ecd-a468-4170-bd8b-d4fdd6fd9235");

void Items::Base::loadIcon()
{
	iconTexture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture(itemIconName, Globals::uiTexturePath);
}

Interfaces::TypeInfo Items::Base::getTrait() const
{
	return { Interfaces::Trait<Items::Base>::typeId };
}
