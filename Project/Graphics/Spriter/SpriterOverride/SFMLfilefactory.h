#ifndef SFMLFileFactory_H
#define SFMLFileFactory_H

#include "../spriterengine/override/filefactory.h"

#include <Graphics\Model\TextureMap.hpp>

namespace SpriterEngine
{
	class SFMLFileFactory : public FileFactory
	{
	public:
		SFMLFileFactory(TextureMap *textureMap);

		ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, std::shared_ptr<sf::Sprite> sprite) override;

		ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size, std::shared_ptr<sf::Sprite> sprite) override;

		SoundFile *newSoundFile(const Core::String &initialFilePath) override;

		SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

	private:
		TextureMap *textureMap;
	};
}

#endif // SFMLFileFactory_H
