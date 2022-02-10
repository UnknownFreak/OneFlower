#ifndef SFMLIMAGEFILE_H
#define SFMLIMAGEFILE_H

#include "../spriterengine/override/imagefile.h"
#include <Graphics\Model\TextureMap.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace SpriterEngine
{
	class SfmlImageFile : public ImageFile
	{
	public:
		SfmlImageFile(Core::String initialFilePath, point initialDefaultPivot, point size, TextureMap *textureMap, std::shared_ptr<sf::Sprite> sprite);

		void renderSprite(UniversalObjectInterface *spriteInfo) override;

		void preRenderSprite(const UniversalObjectInterface *spriteInfo) override;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:

		std::shared_ptr<sf::Sprite> sprite;
		Core::String refName;
		TextureMap *textureMap;

		void initializeFile();
	};
}

#endif // SFMLIMAGEFILE_H
