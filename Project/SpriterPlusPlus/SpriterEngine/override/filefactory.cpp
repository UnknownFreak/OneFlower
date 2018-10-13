#include "filefactory.h"

#include "imagefile.h"
#include "soundfile.h"

#include "spriterfiledocumentwrapper.h"

namespace SpriterEngine
{
	FileFactory::FileFactory()
	{
	}

	FileFactory::~FileFactory()
	{
	}

	ImageFile * FileFactory::newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, SpriteRef*& /*sprite*/)
	{
		return new ImageFile(initialFilePath, initialDefaultPivot);
	}
	ImageFile * FileFactory::newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size, SpriteRef*& /*sprite*/)
	{
		return new ImageFile(initialFilePath, initialDefaultPivot, size);
	}
	SoundFile * FileFactory::newSoundFile(const Core::String &initialFilePath)
	{
		return new SoundFile(initialFilePath);
	}

	SpriterFileDocumentWrapper * FileFactory::newScmlDocumentWrapper()
	{
		return 0;
	}

	SpriterFileDocumentWrapper * FileFactory::newSconDocumentWrapper()
	{
		return 0;
	}
}