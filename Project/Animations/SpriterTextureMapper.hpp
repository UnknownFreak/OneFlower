#ifndef SPRITERTEXTUREMAPPER_HPP
#define	SPRITERTEXTUREMAPPER_HPP

#include "TextureMap.hpp"
#include <AssetManager\SpriteRef.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <map>
//included via TextureMap
//#include <Core\String.hpp>
class SpriterTextureMapper
{
public:

	SpriterTextureMapper(sf::RenderWindow& renderWindow);

	void setTextureMap(std::pair<Core::String, Core::String> newTextureMap);
	void setSpritePointer(SpriteRef* sprite);
	void setTextureMapAndSprite(std::pair<Core::String, Core::String> newTextureMap, SpriteRef* sprite);

	void setRenderWindow(sf::RenderWindow* newRenderWindow);

	sf::RenderWindow* renderWindow;
	std::pair<Core::String, Core::String> currentTextureMapString;
	TextureMap* currentTextureMap;
	std::map<std::pair<Core::String, Core::String>, TextureMap> textureMaps;

	SpriteRef* currentSprite;
private:
	SpriteRef DefaultSprite;

	template<class Archive>
	friend void save(Archive& ar, const SpriterTextureMapper& textureMapper);
	template<class Archive>
	friend void load(Archive& ar, SpriterTextureMapper& textureMapper);
};

#endif