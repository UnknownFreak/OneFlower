#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <Core/String.hpp>

#include "../global/global.h"

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

		virtual ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot);
		virtual ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size);
		virtual SoundFile *newSoundFile(const Core::String &initialFilePath);

		virtual SpriterFileDocumentWrapper *newScmlDocumentWrapper();
		virtual SpriterFileDocumentWrapper *newSconDocumentWrapper();
	};
}

#endif // FILEFACTORY_H
