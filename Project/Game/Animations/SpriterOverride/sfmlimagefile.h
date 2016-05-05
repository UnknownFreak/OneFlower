#ifndef SFMLIMAGEFILE_H
#define SFMLIMAGEFILE_H

#include "../spriterengine/override/imagefile.h"

#include "../../../Vector.h"
#include "../SpriterTextureMapper.hpp"
namespace SpriterEngine
{
	class SfmlImageFile : public ImageFile
	{
	public:
		SfmlImageFile(std::string initialFilePath, point initialDefaultPivot, point size, SpriterTextureMapper *validTextureMapper );

		void renderSprite(UniversalObjectInterface *spriteInfo) override;

	private:

		sf::Sprite* sprite;
		std::string refName;
		SpriterTextureMapper *TextureMapper;

		Vector2 position;
		void initializeFile();
	};

}

#endif // SFMLIMAGEFILE_H
