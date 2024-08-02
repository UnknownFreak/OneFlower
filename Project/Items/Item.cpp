#include "Item.hpp"
#include <module/resource/TextureLoader.hpp>

of::common::uuid of::file::archive::Trait<Items::Base>::typeId = of::common::uuid("d2ab3ecd-a468-4170-bd8b-d4fdd6fd9235");

void Items::Base::loadIcon()
{
	iconTexture = of::engine::GetModule<of::module::texture::Loader>().requestTexture(itemIconName, of::engine::path::ui);
}

of::file::archive::TypeInfo Items::Base::getTrait() const
{
	return { of::file::archive::Trait<Items::Base>::typeId };
}
