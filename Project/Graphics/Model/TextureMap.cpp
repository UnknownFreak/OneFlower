#include "TextureMap.hpp"

Core::uuid Interfaces::Trait<TextureMap>::typeId = Core::uuid("81a0cc9a-f987-4288-9345-350549bc8e42");

TextureMapPoint& TextureMap::getTextureMapPoint(Core::String pointName)
{
	return TexturePoints[pointName];
}

Interfaces::TypeInfo TextureMap::getTrait() const
{
	return { Interfaces::Trait<TextureMap>::typeId };
}
