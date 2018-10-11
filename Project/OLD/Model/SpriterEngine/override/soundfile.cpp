#include "soundfile.h"

#include "soundobjectinforeference.h"

namespace SpriterEngine
{
	SoundFile::SoundFile(Core::String initialFilePath) :
		File(initialFilePath)
	{
	}

	SoundFile *SoundFile::soundFile()
	{
		return this;
	}

	SoundObjectInfoReference * SoundFile::newSoundInfoReference()
	{
		return new SoundObjectInfoReference();
	}
}