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
	typedef std::map<std::string, AnimationInstance*> AnimationInstanceNameMap;

	typedef std::map<s_int, UniversalObjectInterface*> ObjectInterfaceIdMap;
	typedef std::map<std::string, UniversalObjectInterface*> ObjectInterfaceNameMap;

	typedef std::map<s_int, VariableInstanceNameAndIdMap> VariableInstanceObjectIdMap;
	typedef std::map<std::string, VariableInstanceNameAndIdMap*> VariableInstanceObjectNameMap;

	typedef std::map<s_int, TagObjectInfoReference*> TagIdMap;
	typedef std::map<std::string, TagObjectInfoReference*> TagNameMap;

	typedef std::map<s_int, SoundObjectInfoReference*> SoundIdMap;
	typedef std::map<std::string, SoundObjectInfoReference*> SoundNameMap;

	typedef std::map<s_int, TriggerObjectInfo*> TriggerIdMap;
	typedef std::map<std::string, TriggerObjectInfo*> TriggerNameMap;

	class EntityInstanceData : UniversalObjectInterface
	{
	public:
		EntityInstanceData(SpriterModel *model, EntityInstance *entityInstance, Entity *entity, ObjectFactory *objectFactory);
		~EntityInstanceData();

		UniversalObjectInterface *getObjectInstance(s_int objectId);
		UniversalObjectInterface * getObjectInstance(const std::string &objectName);

		TransformProcessor *getTransformer(s_int id);

		VariableInstanceNameAndIdMap *getVariables() override;
		UniversalObjectInterface *getVariable(s_int variableId);
		VariableInstanceNameAndIdMap *getVariables(s_int objectId);
		UniversalObjectInterface *getVariable(s_int objectId, s_int variableId);

		UniversalObjectInterface *getVariable(const std::string &variableName);
		VariableInstanceNameAndIdMap *getVariables(const std::string &objectName);
		UniversalObjectInterface *getVariable(const std::string &objectName, const std::string &variableName);

		UniversalObjectInterface *getTags() const override;
		UniversalObjectInterface *getTags(s_int objectId) const;
		bool tagIsActive(s_int objectId, const std::string &tagToCheck) const;

		bool tagIsActive(const std::string &tagToCheck) const override;
		UniversalObjectInterface *getTags(const std::string &objectName) const;
		bool tagIsActive(const std::string &objectName, const  std::string &tagToCheck) const;

		UniversalObjectInterface *getTriggerObject(s_int triggerId);
		UniversalObjectInterface *getTriggerObject(const std::string &triggerName);

		UniversalObjectInterface *getSoundObject(s_int soundId);
		UniversalObjectInterface *getSoundObject(const std::string &soundName);

		void setCurrentAnimation(s_int newAnimationIndex, AnimationInstance **currentAnimation);
		void setCurrentAnimation(const std::string &animationName, AnimationInstance **currentAnimation);

		void pushBackAnimationInstance(const std::string &name, AnimationInstance *newAnimationInstance);
		void setObjectInstance(s_int id, const  std::string &name, UniversalObjectInterface *newObjectInstance);
		VariableInstanceNameAndIdMap *getVariableInstanceMap(s_int objectId, const std::string &objectName);
		void setTagInstance(s_int objectId, const std::string &objectName);
		void setSoundInstance(s_int id, const std::string &name, FileReference * soundRef);
		void setTriggerInstance(s_int id, const std::string &name, TriggerObjectInfo *newCustomTriggerObject = 0);

		AnimationInstance *getAnimation(s_int animationIndex);
		AnimationInstance *getAnimation(const std::string &animationName);

		void playSoundTriggers();
		void playEventTriggers();

		void updateTransformProcessor();

		std::string getName();

		s_int animationCount();

	protected:
		std::string entityName;

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
