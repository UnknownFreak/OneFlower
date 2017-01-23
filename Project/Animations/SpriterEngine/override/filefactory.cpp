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

	ImageFile * FileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot)
	{
		return new ImageFile(initialFilePath, initialDefaultPivot);
	}
	ImageFile * FileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot, point size)
	{
		return new ImageFile(initialFilePath, initialDefaultPivot, size);
	}
	SoundFile * FileFactory::newSoundFile(const std::string &initialFilePath)
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