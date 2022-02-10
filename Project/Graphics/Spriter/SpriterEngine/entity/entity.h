#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>

#include "../animation/animation.h"
#include "../variable/variablecontainer.h"
#include "../charactermap/charactermapinterface.h"
#include "../charactermap/charactermap.h"

#include "object.h"

namespace SpriterEngine
{
	class AnimationInstance;
	class UniversalObjectInterface;
	class EntityInstance;
	class EntityInstanceData;
	class SpriterModel;
	class ObjectFactory;

	typedef std::vector<Animation*> AnimationVector;
	typedef std::map<Core::String, Object> ObjectNameMap;
	typedef std::map<s_int, Object*> ObjectIdMap;
	typedef std::map<Core::String, CharacterMap> CharacterMapMap;

	class Entity : public VariableContainer, private CharacterMapInterface
	{
	public:
		Entity(Core::String initialName, s_int initialId, FileVector *initialFileVector);
		~Entity();

		s_int getId();

		Core::String getName();

		EntityInstance *getNewEntityInstance(SpriterModel *model, ObjectFactory *objectFactory);
		void setupInstance(SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory);

		Animation *pushBackAnimation(Core::String animationName, real length, bool looping);

		Object *setObject(Core::String objectName, Object::ObjectType objectType);
		Object *getObject(s_int objectId);

		Variable *getVariable(s_int objectId, s_int variableId);

		CharacterMap *addCharacterMap(Core::String name);

		void applyCharacterMap(Core::String mapName, FileReferenceVector *mappedFiles) override;
		void removeAllCharacterMaps(FileReferenceVector *mappedFiles) override;

		UniversalObjectInterface *getNewObjectInfoInstance(s_int objectId);

		void setupDefaultVariableTimelines();

	private:
		s_int entityId;

		Core::String name;

		Object *setSpatialObject(Core::String objectName, Object::ObjectType objectType);
		Object *setTriggerObject(Core::String objectName);
		Object *setSubEntityObject(Core::String objectName);
		Object *setSoundObject(Core::String objectName);

		void setupAnimationInstances(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData);
		void setupObjectInstance(Object * object, SpriterModel * model, EntityInstance * entityInstance, EntityInstanceData * entityInstanceData, ObjectFactory * objectFactory);
		void setupObjectInstances(SpriterModel * model, EntityInstance * entityInstance, EntityInstanceData * entityInstanceData, ObjectFactory * objectFactory);

		AnimationVector animations;
		ObjectNameMap objectNameMap;
		ObjectIdMap objectIdMap;
		CharacterMapMap characterMaps;

		ObjectIdMap triggerIdMap;
		ObjectIdMap soundIdMap;
		ObjectIdMap subEntityIdMap;

		FileVector *files;
	};
}

#endif // ENTITY_H
