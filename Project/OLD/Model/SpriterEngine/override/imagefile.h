#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <Core/String.hpp>

#include "../file/file.h"

#include "../global/global.h"

#include <SFML\Graphics\Drawable.hpp>

namespace SpriterEngine
{
	class UniversalObjectInterface;

	class ImageFile : public File, public sf::Drawable
	{
	public:
		ImageFile(Core::String initialFilePath, point initialDefaultPivot);
		ImageFile(Core::String initialFilePath, point initialDefaultPivot, point size);

		ImageFile *imageFile() override;

		point defaultPivot;
		point size;
		virtual void renderSprite(UniversalObjectInterface *spriteInfo);

		virtual void preRenderSprite(const UniversalObjectInterface* spriteInfo);

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	};
}

#endif // IMAGEFILE_H
