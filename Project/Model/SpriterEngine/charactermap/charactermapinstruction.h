#ifndef CHARACTERMAPINSTRUCTION_H
#define CHARACTERMAPINSTRUCTION_H

#include <vector>
#include "../global/global.h"
namespace SpriterEngine
{
	class File;
	class FileReference;

	typedef std::vector<FileReference*> FileReferenceVector;

	class CharacterMapInstruction
	{
	public:
		CharacterMapInstruction(s_int initialFileToReplaceIndex, File *initialReplacementFile);

		void applyMapInstruction(FileReferenceVector *mappedFiles);

	private:
		int fileToReplace;
		File *replacementFile;
	};
}

#endif // CHARACTERMAPINSTRUCTION_H
