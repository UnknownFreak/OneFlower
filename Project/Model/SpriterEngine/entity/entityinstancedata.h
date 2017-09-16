#ifndef ENTITYINSTANCEDATA_H
#define ENTITYINSTANCEDATA_H

#include <vector>
#include <map>

#include "../objectinfo/universalobjectinterface.h"

#include "../variable/variableinstancenameandidmap.h"

namespace SpriterEngine
{
	class SpriterModel;
	class Entity;
	class ObjectFactory;
	class TransformProcessor;
	class AnimationInstance;
	class TagObjectInfoReference;
	class SoundObjectInfoReference;
	class TriggerObjectInfo;
	class FileReference;
	class EntityInstance;
	class Animation;

	typedef std::map<s_int, TransformProcessor> TransformProcessorMap;

	typedef std::vector<AnimationInstance*> AnimationInstanceIdMap;
	typedef std::map<Core::String, AnimationInstance*> AnimationInstanceNameMap;

	typedef std::map<s_int, UniversalObjectInterface*> ObjectInterfaceIdMap;
	typedef std::map<Core::String, UniversalObjectInterface*> ObjectInterfaceNameMap;

	typedef std::map<s_int, VariableInstanceNameAndIdMap> VariableInstanceObjectIdMap;
	typedef std::map<Core::String, VariableInstanceNameAndIdMap*> VariableInstanceObjectNameMap;

	typedef std::map<s_int, TagObjectInfoReference*> TagIdMap;
	typedef std::map<Core::String, TagObjectInfoReference*> TagNameMap;

	typedef std::map<s_int, SoundObjectInfoReference*> SoundIdMap;
	typedef std::map<Core::String, SoundObjectInfoReference*> SoundNameMap;

	typedef std::map<s_int, TriggerObjectInfo*> TriggerIdMap;
	typedef std::map<Core::String, TriggerObjectInfo*> TriggerNameMap;

	class EntityInstanceData : UniversalObjectInterface
	{
	public:
		EntityInstanceData(SpriterModel *model, EntityInstance *entityInstance, Entity *entity, ObjectFactory *objectFactory);
		~EntityInstanceData();

		UniversalObjectInterface *getObjectInstance(s_int objectId);
		UniversalObjectInterface * getObjectInstance(const Core::String &objectName);

		TransformProcessor *getTransformer(s_int id);

		VariableInstanceNameAndIdMap *getVariables() override;
		UniversalObjectInterface *getVariable(s_int variableId);
		VariableInstanceNameAndIdMap *getVariables(s_int objectId);
		UniversalObjectInterface *getVariable(s_int objectId, s_int variableId);

		UniversalObjectInterface *getVariable(const Core::String &variableName);
		VariableInstanceNameAndIdMap *getVariables(const Core::String &objectName);
		UniversalObjectInterface *getVariable(const Core::String &objectName, const Core::String &variableName);

		UniversalObjectInterface *getTags() const override;
		UniversalObjectInterface *getTags(s_int objectId) const;
		bool tagIsActive(s_int objectId, const Core::String &tagToCheck) const;

		bool tagIsActive(const Core::String &tagToCheck) const override;
		UniversalObjectInterface *getTags(const Core::String &objectName) const;
		bool tagIsActive(const Core::String &objectName, const  Core::String &tagToCheck) const;

		UniversalObjectInterface *getTriggerObject(s_int triggerId);
		UniversalObjectInterface *getTriggerObject(const Core::String &triggerName);

		UniversalObjectInterface *getSoundObject(s_int soundId);
		UniversalObjectInterface *getSoundObject(const Core::String &soundName);

		void setCurrentAnimation(s_int newAnimationIndex, AnimationInstance **currentAnimation);
		void setCurrentAnimation(const Core::String &animationName, AnimationInstance **currentAnimation);

		void pushBackAnimationInstance(const Core::String &name, AnimationInstance *newAnimationInstance);
		void setObjectInstance(s_int id, const  Core::String &name, UniversalObjectInterface *newObjectInstance);
		VariableInstanceNameAndIdMap *getVariableInstanceMap(s_int objectId, const Core::String &objectName);
		void setTagInstance(s_int objectId, const Core::String &objectName);
		void setSoundInstance(s_int id, const Core::String &name, FileReference * soundRef);
		void setTriggerInstance(s_int id, const Core::String &name, TriggerObjectInfo *newCustomTriggerObject = 0);

		AnimationInstance *getAnimation(s_int animationIndex);
		AnimationInstance *getAnimation(const Core::String &animationName);

		void playSoundTriggers();
		void playEventTriggers();

		void updateTransformProcessor();

		Core::String getName();

		s_int animationCount();

	protected:
		Core::String entityName;

		AnimationInstanceIdMap animations;
		AnimationInstanceNameMap animationNameMap;

		ObjectInterfaceIdMap objects;
		ObjectInterfaceNameMap objectNameMap;

		TransformProcessorMap transformers;

		VariableInstanceObjectIdMap variables;
		VariableInstanceObjectNameMap variableObjectNameMap;

		TagIdMap tags;
		TagNameMap tagObjectNameMap;

		SoundIdMap sounds;
		SoundNameMap soundNameMap;

		TriggerIdMap triggers;
		TriggerNameMap triggerNameMap;

		TransformProcessor *transformProcessor;
	};
}

#endif // ENTITYINSTANCEDATA_H
