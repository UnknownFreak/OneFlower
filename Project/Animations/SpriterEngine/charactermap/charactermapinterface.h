#ifndef CHARACTERMAPINTERFACE_H
#define CHARACTERMAPINTERFACE_H

#include <vector>

namespace SpriterEngine
{
	class FileReference;

	typedef std::vector<FileReference*> FileReferenceVector;

	class CharacterMapInterface
	{
	public:
		virtual ~CharacterMapInterface() {}

		virtual void applyCharacterMap(Core::String mapName, FileReferenceVector *mappedFiles) = 0;
		virtual void removeAllCharacterMaps(FileReferenceVector *mappedFiles) = 0;
	};
}

#endif // CHARACTERMAPINTERFACE_H
