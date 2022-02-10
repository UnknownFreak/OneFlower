#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "../variable/variablecontainer.h"

#include "../global/global.h"

namespace SpriterEngine
{
	class UniversalObjectInterface;
	class VariableInstanceNameAndIdMap;
	class ObjectFactory;
	class SpriterModel;
	class EntityInstance;
	class EntityInstanceData;

	typedef std::vector<Variable*> VariableVector;
	typedef std::vector<s_int> IdVector;

	class Object : public VariableContainer
	{
	public:
		enum ObjectType
		{
			OBJECTTYPE_NONE,
			OBJECTTYPE_POINT,
			OBJECTTYPE_BONE,
			OBJECTTYPE_BOX,
			OBJECTTYPE_SPRITE,
			OBJECTTYPE_ENTITY,
			OBJECTTYPE_SOUND,
			OBJECTTYPE_TRIGGER
		};

		Object(Core::String initialName, s_int initialId, ObjectType initialObjectType);

		Core::String getName();
		s_int getId();
		ObjectType getType();

		void addInitializationId(s_int newId);
		void setSize(point newSize);

		UniversalObjectInterface *getNewObjectInfoInstance();

		virtual void addObjectInstanceToEntityInstanceData(SpriterModel * model, EntityInstance * entityInstance, EntityInstanceData * entityInstanceData, ObjectFactory * objectFactory);

	private:
		Core::String name;
		ObjectType objectType;
		s_int objectId;

		point size;
		IdVector initializationIds;
	};
}

#endif // OBJECT_H
