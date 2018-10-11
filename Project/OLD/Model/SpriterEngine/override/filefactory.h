#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <Core/String.hpp>

#include "../global/global.h"

class SpriteRef;
namespace SpriterEngine
{
	class ImageFile;
	class SoundFile;
	class SpriterFileDocumentWrapper;

	class FileFactory
	{
	public:
		FileFactory();
		virtual ~FileFactory();

		virtual ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, SpriteRef*& sprite);
		virtual ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size, SpriteRef*& sprite);
		virtual SoundFile *newSoundFile(const Core::String &initialFilePath);

		virtual SpriterFileDocumentWrapper *newScmlDocumentWrapper();
		virtual SpriterFileDocumentWrapper *newSconDocumentWrapper();
	};
}

#endif // FILEFACTORY_H
