#include "SFMLFileFactory.h"

#include "../spriterengine/override/imagefile.h"
#include "../spriterengine/override/soundfile.h"

#include "tinyxmlspriterfiledocumentwrapper.h"

#include "sfmlimagefile.h"
#include "sfmlsoundfile.h"
namespace SpriterEngine
{
	SFMLFileFactory::SFMLFileFactory(SpriterTextureMapper *validTextureMapper) :
		textureMapper(validTextureMapper)
	{
	}

	ImageFile * SFMLFileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot)
	{
		return new SfmlImageFile(initialFilePath, initialDefaultPivot, point(0, 0), textureMapper);
	}

	ImageFile * SFMLFileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot, point size)
	{
		return new SfmlImageFile(initialFilePath, initialDefaultPivot, size, textureMapper);
	}

	SoundFile * SFMLFileFactory::newSoundFile(const std::string & initialFilePath)
	{
		return new SfmlSoundFile(initialFilePath);
	}

	SpriterFileDocumentWrapper * SFMLFileFactory::newScmlDocumentWrapper()
	{
		return new TinyXmlSpriterFileDocumentWrapper();
	}
}