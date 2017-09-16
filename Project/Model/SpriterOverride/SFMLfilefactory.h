#ifndef SFMLFileFactory_H
#define SFMLFileFactory_H

#include "../spriterengine/override/filefactory.h"

#include "../SpriterTextureMapper.hpp"
namespace SpriterEngine
{
	class SFMLFileFactory : public FileFactory
	{
	public:
		SFMLFileFactory(SpriterTextureMapper *validTextureMapper);

		ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot) override;

		ImageFile *newImageFile(const Core::String &initialFilePath, point initialDefaultPivot, point size) override;

		SoundFile *newSoundFile(const Core::String &initialFilePath) override;

		SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

	private:
		SpriterTextureMapper *textureMapper;
	};
}

#endif // SFMLFileFactory_H
