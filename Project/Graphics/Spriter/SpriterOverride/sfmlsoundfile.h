#ifndef SFMLSOUNDFILE_H
#define SFMLSOUNDFILE_H

#include "../spriterengine/override/soundfile.h"

#include "SFML/Audio.hpp"

namespace SpriterEngine
{
	class SfmlSoundFile : public SoundFile
	{
	public:
		SfmlSoundFile(Core::String initialFilePath);

		SoundObjectInfoReference * newSoundInfoReference();

	private:
		//sf::SoundBuffer buffer;

		void initializeFile();
	};
}

#endif // SFMLSOUNDFILE_H
