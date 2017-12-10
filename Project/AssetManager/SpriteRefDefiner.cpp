#include "SpriteRef.hpp"
#include "AssetManagerCore.hpp"
#include <SFML\Graphics\RenderTarget.hpp>
void SpriteRef::unloadTexture()
{
	if (textureReference)
	{
		textureReference->useCount--;
		if (textureReference->useCount == 0)
			Engine::Get<AssetManager>().textureloader.requestRemovalOfTexture(textureReference->name);
	}
}

void SpriteRef::waitForTextureLoaded()
{
	if (textureReference)
	{
		textureReference->getTexture();
		reload(true);
	}
	else
		// textureRef was not set, so set a "default" texture
		privRef->setTexture(sf::Texture());
}

SpriteRef::SpriteRef() : sf::Sprite(), privRef(this)
{
}

SpriteRef::SpriteRef(const SpriteRef & ref) : sf::Sprite(ref), textureReference(ref.textureReference),privRef(this)
{
	setTexture(textureReference);
}

SpriteRef::SpriteRef(const TextureRef * ref) : sf::Sprite(), privRef(this)
{
	textureReference = (TextureRef*)ref;
	setTexture(textureReference, true);
}

SpriteRef::~SpriteRef()
{
	unloadTexture();
}

void SpriteRef::setTexture(TextureRef * texture, bool resize)
{
	resizeTextureOnReload = resize;
	unloadTexture();
	textureReference = texture;
	textureReference->useCount++;
	reload(resizeTextureOnReload);
}

void SpriteRef::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!textureSet)
		((SpriteRef&)*this).reload(resizeTextureOnReload);
	target.draw((sf::Sprite)*privRef, states);
}

void SpriteRef::reload(bool resize)
{
	textureLoaded = textureReference->isValid();
	if (textureLoaded)
	{
		privRef->setTexture(*textureReference->getTexture(), resize);
		textureSet = true;
		resizeTextureOnReload = false;
	}
}


