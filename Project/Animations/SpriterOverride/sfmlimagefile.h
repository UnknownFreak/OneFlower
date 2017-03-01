#ifndef SFMLIMAGEFILE_H
#define SFMLIMAGEFILE_H

#include "../spriterengine/override/imagefile.h"
#include "../SpriterTextureMapper.hpp"

namespace SpriterEngine
{
	class SfmlImageFile : public ImageFile
	{
	public:
		SfmlImageFile(Core::String initialFilePath, point initialDefaultPivot, point size, SpriterTextureMapper *validTextureMapper);

		void renderSprite(UniversalObjectInterface *spriteInfo) override;

	private:

		sf::Sprite* sprite;
		Core::String refName;
		SpriterTextureMapper *TextureMapper;

		void initializeFile();
	};
}

#endif // SFMLIMAGEFILE_H
