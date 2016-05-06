#include "sfmlimagefile.h"

#include "../spriterengine/global/settings.h"

#include "../spriterengine/objectinfo/universalobjectinterface.h"
#include "../../../Engine.hpp"
namespace SpriterEngine
{

	SfmlImageFile::SfmlImageFile(std::string initialFilePath, point initialDefaultPivot, point size,
		SpriterTextureMapper *validTextureMapper) :
		ImageFile(initialFilePath, initialDefaultPivot, size),
		TextureMapper(validTextureMapper)
	{
		initializeFile();
	}

	void SfmlImageFile::initializeFile()
	{
		refName = path();
		size_t tmp = refName.find_first_not_of("Spriter/");
		refName.erase(refName.begin(), refName.begin() + tmp);

		if (TextureMapper->currentTextureMap->TexturePoints.find(refName) == TextureMapper->currentTextureMap->TexturePoints.end())
			TextureMapper->currentTextureMap->TexturePoints.insert(std::pair<std::string, TextureMapPoint>(refName, TextureMapPoint()));
		else
		{
			//Do nothing
		}
		if (!sprite)
			sprite = TextureMapper->currentSprite;
		sprite->setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	}

	void SfmlImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
		TextureMapPoint& p = TextureMapper->currentTextureMap->getTextureMapPoint(refName);
		sprite = TextureMapper->currentSprite;
		sprite->setColor(sf::Color(p.color.r, p.color.g, p.color.b, 255 * spriteInfo->getAlpha()));
		sprite->setPosition(spriteInfo->getPosition().x, spriteInfo->getPosition().y);
		if (p.rotated)
		{
			sprite->setOrigin((1-spriteInfo->getPivot().y)*p.size.y, spriteInfo->getPivot().x*p.size.x);
			sprite->setRotation(toDegrees(spriteInfo->getAngle()) - 90.0);
			sprite->setTextureRect(sf::IntRect(p.pos.x, p.pos.y, p.size.y, p.size.x));
			sprite->setScale(spriteInfo->getScale().y, spriteInfo->getScale().x);
		}
		else
		{
			sprite->setOrigin(spriteInfo->getPivot().x*p.size.x, spriteInfo->getPivot().y*p.size.y);
			sprite->setRotation(toDegrees(spriteInfo->getAngle()));
			sprite->setTextureRect(sf::IntRect(p.pos.x, p.pos.y, p.size.x, p.size.y));
			sprite->setScale(spriteInfo->getScale().x, spriteInfo->getScale().y);
		}
		TextureMapper->renderWindow->draw(*sprite);
	}

}
