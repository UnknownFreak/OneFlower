#include "sfmlimagefile.h"

#include "../spriterengine/global/settings.h"

#include "../spriterengine/objectinfo/universalobjectinterface.h"
namespace SpriterEngine
{
	SfmlImageFile::SfmlImageFile(Core::String initialFilePath, point initialDefaultPivot, point size,
		TextureMap *textureMap, SpriteRef*& sprite) :
		ImageFile(initialFilePath, initialDefaultPivot, size),
		textureMap(textureMap), sprite(sprite)
	{
		initializeFile();
	}

	void SfmlImageFile::initializeFile()
	{
		refName = path();
		size_t tmp = refName.find_first_not_of("Spriter/");
		refName.erase(refName.begin(), refName.begin() + tmp);

		if (textureMap->TexturePoints.find(refName) == textureMap->TexturePoints.end())
			textureMap->TexturePoints.insert(std::pair<Core::String, TextureMapPoint>(refName, TextureMapPoint()));
		if(sprite)
			sprite->setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	}

	void SfmlImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
	}

	void SfmlImageFile::preRenderSprite(const UniversalObjectInterface * spriteInfo)
	{
		TextureMapPoint& p = textureMap->getTextureMapPoint(refName);
		//int textureRes = (int)Engine::settings.textureQuality;
		int textureRes = 1;
		// sprite = TextureMapper->currentSprite;
		sprite->setColor(sf::Color(p.color.r, p.color.g, p.color.b, sf::Uint8(255 * spriteInfo->getAlpha())));
		sprite->setPosition(spriteInfo->getPosition().x, spriteInfo->getPosition().y);
		if (p.rotated)
		{
			sprite->setOrigin((1 - spriteInfo->getPivot().y)*p.size.y, spriteInfo->getPivot().x*p.size.x);
			sprite->setRotation(toDegrees(spriteInfo->getAngle()) - 90.0f);
			sprite->setTextureRect(sf::IntRect(p.pos.x / textureRes, p.pos.y / textureRes, p.size.y / textureRes, p.size.x / textureRes));
			sprite->setScale(spriteInfo->getScale().y, spriteInfo->getScale().x);
		}
		else
		{
			sprite->setOrigin(spriteInfo->getPivot().x*p.size.x, spriteInfo->getPivot().y*p.size.y);
			sprite->setRotation(toDegrees(spriteInfo->getAngle()));
			sprite->setTextureRect(sf::IntRect(p.pos.x / textureRes, p.pos.y / textureRes, p.size.x / textureRes, p.size.y / textureRes));
			sprite->setScale(spriteInfo->getScale().x, spriteInfo->getScale().y);
		}
	}

	void SfmlImageFile::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(*sprite, states);
	}
}