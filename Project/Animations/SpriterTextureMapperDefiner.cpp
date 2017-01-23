#include "SpriterTextureMapper.hpp"
#include <AssetManager\AssetManagerCore.hpp>
SpriterTextureMapper::SpriterTextureMapper(sf::RenderWindow& renderWindow) : currentTextureMapString("DEFAULT", "Default"), DefaultSprite(Engine::Textureloader.requestTexture("Test.png")), currentSprite(&DefaultSprite)
{
	textureMaps.insert(std::pair<std::pair<std::string, std::string>, TextureMap>(currentTextureMapString, TextureMap()));
	this->renderWindow = &renderWindow;
	currentTextureMap = &textureMaps.at(currentTextureMapString);
	currentTextureMap->modName = "DEFAULT";
}

void SpriterTextureMapper::setTextureMap(std::pair<std::string, std::string> newTextureMap)
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
void SpriterTextureMapper::setRenderWindow(sf::RenderWindow* newRenderWindow)
{
	renderWindow = newRenderWindow;
}
void SpriterTextureMapper::setTextureMapAndSprite(std::pair<std::string, std::string> texMap, SpriteRef* sprite)
{
	setTextureMap(texMap);
	setSpritePointer(sprite);
}