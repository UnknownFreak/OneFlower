#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <Helpers/String.hpp>

#include "../global/global.h"
#include <SFML/Graphics/Sprite.hpp>

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

		virtual ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, std::shared_ptr<sf::Sprite> sprite);
		virtual ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size, std::shared_ptr<sf::Sprite> sprite);
		virtual SoundFile *newSoundFile(const Core::String &initialFilePath);

		virtual SpriterFileDocumentWrapper *newScmlDocumentWrapper();
		virtual SpriterFileDocumentWrapper *newSconDocumentWrapper();
	};
}

#endif // FILEFACTORY_H
