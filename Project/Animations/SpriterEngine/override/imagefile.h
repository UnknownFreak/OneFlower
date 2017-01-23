#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <string>

#include "../file/file.h"

#include "../global/global.h"

namespace SpriterEngine
{
	class UniversalObjectInterface;

	class ImageFile : public File
	{
	public:
		ImageFile(std::string initialFilePath, point initialDefaultPivot);
		ImageFile(std::string initialFilePath, point initialDefaultPivot, point size);

		ImageFile *imageFile() override;

		point defaultPivot;
		point size;
		virtual void renderSprite(UniversalObjectInterface *spriteInfo);
	};
}

#endif // IMAGEFILE_H
