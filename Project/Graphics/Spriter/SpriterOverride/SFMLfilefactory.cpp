#include "SFMLFileFactory.h"

#include "../spriterengine/override/imagefile.h"
#include "../spriterengine/override/soundfile.h"

#include "tinyxmlspriterfiledocumentwrapper.h"

#include "sfmlimagefile.h"
#include "sfmlsoundfile.h"
namespace SpriterEngine
{
	SFMLFileFactory::SFMLFileFactory(TextureMap *textureMap) :
		textureMap(textureMap)
	{
	}

	ImageFile * SFMLFileFactory::newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, std::shared_ptr<sf::Sprite> sprite)
	{
		return new SfmlImageFile(initialFilePath, initialDefaultPivot, point{ 0, 0 }, textureMap, sprite);
	}

	ImageFile * SFMLFileFactory::newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size, std::shared_ptr<sf::Sprite>  sprite)
	{
		return new SfmlImageFile(initialFilePath, initialDefaultPivot, size, textureMap, sprite);
	}

	SoundFile * SFMLFileFactory::newSoundFile(const Core::String & initialFilePath)
	{
		return new SfmlSoundFile(initialFilePath);
	}

	SpriterFileDocumentWrapper * SFMLFileFactory::newScmlDocumentWrapper()
	{
		return new TinyXmlSpriterFileDocumentWrapper();
	}
}