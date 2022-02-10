#include "boneref.h"

#include "../entity/entityinstancedata.h"

#include "bonerefinstance.h"

namespace SpriterEngine
{
	BoneRef::BoneRef(s_int initialObjectId, s_int initialParentObjectId, TimelineKey *initialKey) :
		ObjectRef(initialObjectId, initialParentObjectId, initialKey)
	{
	}

	ObjectRefInstance *BoneRef::getNewSpecializedObjectRefInstance(EntityInstance *, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance)
	{
		return new BoneRefInstance(objectInstance, initialParentTransformer, entityInstanceData->getTransformer(id()), getKey());
	}
}