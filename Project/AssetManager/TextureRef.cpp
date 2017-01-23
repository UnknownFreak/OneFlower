#include "TextureRef.hpp"
#include "AssetManagerCore.hpp"
#include "TextureLoader.hpp"
const sf::Texture * TextureRef::getTexture()
{
	return &myTexture.get();
}

bool TextureRef::isReady()
{
	return myTexture.valid();
}

void TextureRef::setNewFuture(std::shared_future<sf::Texture> fut)
{
	myTexture = fut;
}

void TextureRef::reloadTexture()
{
	myTexture = Engine::Textureloader.loadTextureAsync(name);
}


TextureRef::TextureRef(std::string name) : name(name)
{
	reloadTexture();
}

TextureRef::TextureRef(const TextureRef & copy) : name(copy.name), myTexture(copy.myTexture), useCount(copy.useCount)
{
}
