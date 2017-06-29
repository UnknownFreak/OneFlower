#include "file.h"

namespace SpriterEngine
{
	File::File(Core::String initialFilePath) :
		filePath(initialFilePath)
	{
	}

	ImageFile *File::imageFile()
	{
		return 0;
	}

	SoundFile *File::soundFile()
	{
		return 0;
	}

	Core::String File::path()
	{
		return filePath;
	}
}