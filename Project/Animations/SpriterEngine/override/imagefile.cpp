#include "imagefile.h"

#include "../objectinfo/universalobjectinterface.h"

namespace SpriterEngine
{
	ImageFile::ImageFile(std::string initialFilePath, point initialDefaultPivot) :
		File(initialFilePath),
		defaultPivot(initialDefaultPivot)
	{
	}

	ImageFile::ImageFile(std::string initialFilePath, point initialDefaultPivot, point size) :
		File(initialFilePath),
		defaultPivot(initialDefaultPivot),
		size(size)
	{
	}

	ImageFile *ImageFile::imageFile()
	{
		return this;
	}

	void ImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
		// TODO: override and add custom rendering code here using:

		// spriteInfo->getAlpha()
		// spriteInfo->getPosition()
		// spriteInfo->getAngle()
		// spriteInfo->getScale()
		// spriteInfo->getPivot()
	}
}