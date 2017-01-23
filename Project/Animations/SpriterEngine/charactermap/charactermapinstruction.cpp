#include "charactermapinstruction.h"

#include "../file/filereference.h"
#include "../global/global.h"
namespace SpriterEngine
{
	CharacterMapInstruction::CharacterMapInstruction(s_int initialFileToReplaceIndex, File *initialReplacementFile) :
		fileToReplace(initialFileToReplaceIndex),
		replacementFile(initialReplacementFile)
	{
	}

	void CharacterMapInstruction::applyMapInstruction(FileReferenceVector *mappedFiles)
	{
		mappedFiles->at(fileToReplace)->setFile(replacementFile);
	}
}