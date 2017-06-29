#ifndef ENTITYREF_H
#define ENTITYREF_H

#include "objectref.h"

namespace SpriterEngine
{
	class TransformProcessor;

	class EntityRef : public ObjectRef
	{
	public:
		EntityRef(s_int initialObjectId, s_int initialParentObjectId, TimelineKey *initialKey, s_int initialEntityId, s_int initialAnimationIndex);

	private:
		ObjectRefInstance *getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance) override;

		s_int entityId;
		s_int animationIndex;
	};
}

#endif // ENTITYREF_H
