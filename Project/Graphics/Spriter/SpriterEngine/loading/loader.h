#ifndef LOADER_H
#define LOADER_H

#include <Helpers/String.hpp>

#include "spriterdocumentloader.h"

namespace SpriterEngine
{
	class SpriterFileDocumentWrapper;
	class SpriterModel;
	class FileFactory;

	class Loader
	{
	public:
		Loader(FileFactory *newFileFactory);
		~Loader();

		void loadFile(SpriterModel *model, const Core::String &fileName);

	private:
		enum SpriterFileType
		{
			SPRITERFILETYPE_NONE,
			SPRITERFILETYPE_SCML,
			SPRITERFILETYPE_SCON
		};

		FileFactory *fileFactory;

		SpriterFileType extractFileTypeFromFileName(const Core::String &fileName);
	};
}

#endif // LOADER_H
