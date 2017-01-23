#ifndef SPRITERTEXTUREMAPPER_HPP
#define	SPRITERTEXTUREMAPPER_HPP

#include "TextureMap.hpp"
#include <AssetManager\SpriteRef.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <map>
class SpriterTextureMapper
{
public:

	SpriterTextureMapper(sf::RenderWindow& renderWindow);

	void setTextureMap(std::pair<std::string, std::string> newTextureMap);
	void setSpritePointer(SpriteRef* sprite);
	void setTextureMapAndSprite(std::pair<std::string, std::string> newTextureMap, SpriteRef* sprite);

	void setRenderWindow(sf::RenderWindow* newRenderWindow);

	sf::RenderWindow* renderWindow;
	std::pair<std::string, std::string> currentTextureMapString;
	TextureMap* currentTextureMap;
	std::map<std::pair<std::string, std::string>, TextureMap> textureMaps;

	SpriteRef* currentSprite;
private:
	SpriteRef DefaultSprite;

	template<class Archive>
	friend void save(Archive& ar, const SpriterTextureMapper& textureMapper);
	template<class Archive>
	friend void load(Archive& ar, SpriterTextureMapper& textureMapper);
};

#endif