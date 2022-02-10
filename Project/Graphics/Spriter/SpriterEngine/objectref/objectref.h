#ifndef OBJECTREF_H
#define OBJECTREF_H
#include "../global/global.h"
namespace SpriterEngine
{
	class ObjectRefInstance;
	class EntityInstance;
	class EntityInstanceData;
	class TransformProcessor;
	class TimelineKey;
	class UniversalObjectInterface;

	class ObjectRef
	{
	public:
		ObjectRef(s_int initialObjectId, s_int initialParentObjectId, TimelineKey *initialKey);
		virtual ~ObjectRef() {}

		ObjectRefInstance *getNewObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData);
		s_int id();

	protected:
		TimelineKey *getKey();

	private:
		virtual ObjectRefInstance *getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance);

		s_int objectId;
		s_int parentObjectId;

		TimelineKey *key;
	};
}

#endif // OBJECTREF_H
