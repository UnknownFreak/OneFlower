#ifndef SFMLIMAGEFILE_H
#define SFMLIMAGEFILE_H

#include "../spriterengine/override/imagefile.h"
#include "../SpriterTextureMapper.hpp"

#include <AssetManager\SpriteRef.hpp>

namespace SpriterEngine
{
	class SfmlImageFile : public ImageFile
	{
	public:
		SfmlImageFile(Core::String initialFilePath, point initialDefaultPivot, point size, TextureMap *textureMap, SpriteRef*& sprite);

		void renderSprite(UniversalObjectInterface *spriteInfo) override;

		void preRenderSprite(const UniversalObjectInterface *spriteInfo) override;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:

		SpriteRef*& sprite;
		Core::String refName;
		TextureMap *textureMap;

		void initializeFile();
	};
}

#endif // SFMLIMAGEFILE_H
