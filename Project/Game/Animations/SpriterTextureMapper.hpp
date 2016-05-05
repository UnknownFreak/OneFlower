#ifndef SPRITERTEXTUREMAPPER_HPP
#define	SPRITERTEXTUREMAPPER_HPP

#include "TextureMap.hpp"
#include <SFML\Graphics\RenderWindow.hpp>
#include <map>
class SpriterTextureMapper
{
public:

	SpriterTextureMapper();

	void setTextureMap(std::pair<std::string, std::string> newTextureMap);
	void setSpritePointer(sf::Sprite* sprite);
	void setTextureMapAndSprite(std::pair<std::string, std::string> newTextureMap, sf::Sprite* sprite);

	void setRenderWindow(sf::RenderWindow* newRenderWindow);

	sf::RenderWindow* renderWindow;
	std::pair<std::string,std::string> currentTextureMapString;
	TextureMap* currentTextureMap;
	std::map<std::pair<std::string,std::string>, TextureMap> textureMaps;

	sf::Sprite* currentSprite;
private:
	sf::Sprite DefaultSprite;

	template<class Archive>
	friend void save(Archive& ar, const SpriterTextureMapper& textureMapper);
	template<class Archive>
	friend void load(Archive& ar, SpriterTextureMapper& textureMapper);
};

#endif