#include "SpriterTextureMapper.hpp"
#include <AssetManager\AssetManagerCore.hpp>

void SpriterTextureMapper::initialize()
{
	textureMaps.insert(std::pair<std::pair<Core::String, Core::String>, TextureMap>(currentTextureMapString, TextureMap()));
	currentTextureMap = &textureMaps.at(currentTextureMapString);
	currentTextureMap->fromMod = "DEFAULT";
}


//SpriterTextureMapper::SpriterTextureMapper() : currentTextureMapString("DEFAULT", "Default"),
//DefaultSprite(Engine::Get<AssetManager>().textureloader.requestTexture("Test.png")), currentSprite(&DefaultSprite),
//renderWindow(nullptr)
//{
//	initialize();
//}

SpriterTextureMapper::SpriterTextureMapper(sf::RenderWindow& renderWindow) : currentTextureMapString("DEFAULT", "Default"),
DefaultSprite(Engine::Get<AssetManager>().textureloader.requestTexture("Test.png")), currentSprite(&DefaultSprite)
{
	this->renderWindow = &renderWindow;
	initialize();
}

void SpriterTextureMapper::setTextureMap(std::pair<Core::String, Core::String> newTextureMap)
{
	if (currentTextureMapString != newTextureMap)
		if (textureMaps.find(newTextureMap) != textureMaps.end())
		{
			currentTextureMapString = newTextureMap;
			currentTextureMap = &textureMaps[newTextureMap];
		}
}
void SpriterTextureMapper::setSpritePointer(SpriteRef* sprite)
{
	currentSprite = sprite;
}
void SpriterTextureMapper::setRenderWindow(sf::RenderWindow& newRenderWindow)
{
	renderWindow = &newRenderWindow;
}
void SpriterTextureMapper::setTextureMapAndSprite(std::pair<Core::String, Core::String> texMap, SpriteRef* sprite)
{
	setTextureMap(texMap);
	setSpritePointer(sprite);
}