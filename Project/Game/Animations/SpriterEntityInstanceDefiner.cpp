#include "SpriterEntityInstance.hpp"

SpriterEntityInstance::SpriterEntityInstance(SpriterEngine::EntityInstance* myEntity, SpriterTextureMapper* textureMap) :
MyEntityInstance(myEntity), textureMaps(textureMap)
{

}
SpriterEntityInstance::SpriterEntityInstance()
{

}
void SpriterEntityInstance::render(sf::Sprite* sprite)
{
	if (MyEntityInstance != NULL)
	{
		textureMaps->setTextureMapAndSprite(myTextureMap, sprite);
		MyEntityInstance->setCurrentTime(MyEntityInstance->getCurrentTime());
		MyEntityInstance->render();
	}
}