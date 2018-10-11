#ifndef SpriteRef_HPP
#define SpriteRef_HPP

#include <SFML\Graphics\Sprite.hpp>
#include "TextureRef.hpp"
class SpriteRef : public sf::Sprite
{
	sf::Sprite* privRef = nullptr;
	TextureRef* textureReference = nullptr;

	void unloadTexture();
	void reload(bool resize = false);

	bool textureLoaded = false;
	bool textureSet = false;

	bool resizeTextureOnReload = false;

public:

	void waitForTextureLoaded();

	SpriteRef();
	SpriteRef(const SpriteRef & ref);
	SpriteRef(const TextureRef * ref);
	SpriteRef& operator=(const SpriteRef& ref);
	~SpriteRef();

	void setTexture(TextureRef* texture, bool resize = false);
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

#endif
