#include "SpriterTextureMapper.hpp"
#include "../../Engine.hpp"
SpriterTextureMapper::SpriterTextureMapper() : currentTextureMapString("DEFAULT","Default"), DefaultSprite(*Engine::Graphic.requestTexture("Test.png")), currentSprite(&DefaultSprite)
{
	textureMaps.insert(std::pair<std::pair<std::string,std::string>, TextureMap>(currentTextureMapString, TextureMap()));
	renderWindow = &Engine::Graphic.view.render;
	currentTextureMap = &textureMaps.at(currentTextureMapString);
	currentTextureMap->modName = "DEFAULT";
}

void SpriterTextureMapper::setTextureMap(std::pair<std::string,std::string> newTextureMap)
{
	if (currentTextureMapString != newTextureMap)
		if (textureMaps.find(newTextureMap) != textureMaps.end())
		{
			currentTextureMapString = newTextureMap;
			currentTextureMap = &textureMaps[newTextureMap];
		}
}
void SpriterTextureMapper::setSpritePointer(sf::Sprite* sprite)
{
	currentSprite = sprite;
}
void SpriterTextureMapper::setRenderWindow(sf::RenderWindow* newRenderWindow)
{
	renderWindow = newRenderWindow;
}
void SpriterTextureMapper::setTextureMapAndSprite(std::pair<std::string, std::string> texMap, sf::Sprite* sprite)
{
	setTextureMap(texMap);
	setSpritePointer(sprite);
}