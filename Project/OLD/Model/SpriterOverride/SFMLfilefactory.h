#ifndef SFMLFileFactory_H
#define SFMLFileFactory_H

#include "../spriterengine/override/filefactory.h"

#include "../SpriterTextureMapper.hpp"

namespace SpriterEngine
{
	class SFMLFileFactory : public FileFactory
	{
	public:
		SFMLFileFactory(TextureMap *textureMap);

		ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, SpriteRef*& sprite) override;

		ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size, SpriteRef*& sprite) override;

		SoundFile *newSoundFile(const Core::String &initialFilePath) override;

		SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

	private:
		TextureMap *textureMap;
	};
}

#endif // SFMLFileFactory_H
