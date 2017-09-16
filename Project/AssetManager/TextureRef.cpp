#include "TextureRef.hpp"
#include "AssetManagerCore.hpp"
#include "TextureLoader.hpp"


const sf::Texture * TextureRef::getTexture()
{
#ifdef _EDITOR_
	return &myTexture;
#else
	return &myTexture.get();
#endif
}

bool TextureRef::isValid()
{
#ifdef _EDITOR_
	return true;
#else
	return myTexture.valid();
#endif
}
#ifdef _EDITOR_
void TextureRef::setNewFuture(sf::Texture texture)
#else
void TextureRef::setNewFuture(std::shared_future<sf::Texture> texture)
#endif
{
	myTexture = texture;
}

void TextureRef::reloadTexture()
{
	myTexture = Engine::Textureloader.loadTextureAsync(name);
}


TextureRef::TextureRef(Core::String name) : name(name)
{
	reloadTexture();
}

TextureRef::TextureRef(const TextureRef & copy) : name(copy.name), myTexture(copy.myTexture), useCount(copy.useCount)
{
}
