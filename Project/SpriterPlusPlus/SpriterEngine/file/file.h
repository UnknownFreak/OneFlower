#ifndef FILE_H
#define FILE_H

#include <Core/String.hpp>

namespace SpriterEngine
{
	class ImageFile;
	class SoundFile;

	class File
	{
	public:
		File(Core::String initialFilePath);
		virtual ~File() {}

		virtual ImageFile *imageFile();
		virtual SoundFile *soundFile();

	protected:
		Core::String path();

	private:
		Core::String filePath;
	};
}

#endif // FILE_H
