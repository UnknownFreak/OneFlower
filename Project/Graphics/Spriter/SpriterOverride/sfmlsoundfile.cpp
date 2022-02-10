#include "sfmlsoundfile.h"

#include "../spriterengine/global/settings.h"

#include "sfmlsoundobjectinforeference.h"

namespace SpriterEngine
{
	SfmlSoundFile::SfmlSoundFile(Core::String initialFilePath) :
		SoundFile(initialFilePath)
	{
		initializeFile();
	}

	void SfmlSoundFile::initializeFile()
	{
		//if (!buffer.loadFromFile(path()))
		{
			Settings::error("SfmlSoundFile::initializeFile - sfml sound buffer unable to load file from path \"" + path() + "\"");
		}
	}

	SoundObjectInfoReference * SfmlSoundFile::newSoundInfoReference()
	{
		return NULL;//new SfmlSoundObjectInfoReference(buffer);
	}
}