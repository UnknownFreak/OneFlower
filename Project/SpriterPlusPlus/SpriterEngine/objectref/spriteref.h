#ifndef SPRITEREF_H
#define SPRITEREF_H

#include "objectref.h"

namespace SpriterEngine
{
	class TransformProcessor;

	class SpriteRef : public ObjectRef
	{
	public:
		SpriteRef(s_int initialObjectId, s_int initialParentObjectId, TimelineKey *initialKey, s_int initialFileId, bool initialUseDefaultPivot);

	private:
		ObjectRefInstance *getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance) override;

		s_int fileId;
		bool useDefaultPivot;
	};
}

#endif // SPRITEREF_H
