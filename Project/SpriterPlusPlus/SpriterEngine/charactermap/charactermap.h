#ifndef CHARACTERMAP_H
#define CHARACTERMAP_H

#include <vector>
#include "../global/global.h"
#include "charactermapinstruction.h"

namespace SpriterEngine
{
	typedef std::vector<File*> FileVector;
	typedef std::vector<CharacterMapInstruction> CharacterMapInstructionVector;

	class CharacterMap
	{
	public:
		CharacterMap();

		void applyCharacterMap(FileReferenceVector *mappedFiles);

		void appendMapInstruction(s_int initialFileToReplaceIndex, File * replacementFile);

	private:
		CharacterMapInstructionVector mapInstructions;
	};
}

#endif // CHARACTERMAP_H
