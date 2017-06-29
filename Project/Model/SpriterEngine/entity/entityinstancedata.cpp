#include "entityinstancedata.h"

#include "../global/settings.h"

#include "../objectref/transformprocessor.h"
#include "../objectinfo/tagobjectinforeference.h"
#include "../objectinfo/triggerobjectinfo.h"

#include "../override/soundobjectinforeference.h"
#include "../override/soundfile.h"

#include "../variable/variable.h"

#include "entityinstance.h"
#include "entity.h"

namespace SpriterEngine
{
	EntityInstanceData::EntityInstanceData(SpriterModel *model, EntityInstance *entityInstance, Entity *entity, ObjectFactory *objectFactory)
	{
		transformProcessor = &(*transformers.insert(std::make_pair(THIS_ENTITY, TransformProcessor(entityInstance))).first).second;
		entity->setupInstance(model, entityInstance, this, objectFactory);
		entityName = entity->getName();
	}

	EntityInstanceData::~EntityInstanceData()
	{
		for (auto& it : animations)
		{
			delete it;
		}

		for (auto& it : objects)
		{
			delete it.second;
		}

		for (auto& it : tags)
		{
			delete it.second;
		}

		for (auto& it : sounds)
		{
			delete it.second;
		}

		for (auto& it : triggers)
		{
			delete it.second;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getObjectInstance(s_int objectId)
	{
		auto it = objects.find(objectId);
		if (it != objects.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getObjectInstance - object interface with id " + std::to_string(objectId) + " not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getObjectInstance(const Core::String &objectName)
	{
		auto it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getObjectInstance - object interface with name \"" + objectName + "\" not found");
			return 0;
		}
	}

	TransformProcessor *EntityInstanceData::getTransformer(s_int id)
	{
		auto  it = transformers.find(id);
		if (it != transformers.end())
		{
			return &(*it).second;
		}
		else
		{
			UniversalObjectInterface *object = getObjectInstance(id);
			if (object)
			{
				return &(*transformers.insert(std::make_pair(id, TransformProcessor(object))).first).second;
			}
			else
			{
				Settings::error("EntityInstanceData::getTransformer - object instance with id " + std::to_string(id) + " not found");
				return 0;
			}
		}
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariables()
	{
		return getVariables(THIS_ENTITY);
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(s_int variableId)
	{
		return getVariable(THIS_ENTITY, variableId);
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariables(s_int objectId)
	{
		auto it = variables.find(objectId);
		if (it != variables.end())
		{
			return &(*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getVariables - variable instance map for object id " + std::to_string(objectId) + " not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(s_int objectId, s_int variableId)
	{
		VariableInstanceNameAndIdMap *variableMap = getVariables(objectId);
		if (variableMap)
		{
			return variableMap->getVariable(variableId);
		}
		else
		{
			Settings::error("EntityInstanceData::getVariable - variable instance map for object id " + std::to_string(objectId) + " not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(const Core::String &variableName)
	{
		return getVariable("", variableName);
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariables(const Core::String &objectName)
	{
		auto it = variableObjectNameMap.find(objectName);
		if (it != variableObjectNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getVariables - variable instance map for object name \"" + objectName + "\" not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(const Core::String &objectName, const Core::String &variableName)
	{
		VariableInstanceNameAndIdMap *variableMap = getVariables(objectName);
		if (variableMap)
		{
			return variableMap->getVariable(variableName);
		}
		else
		{
			Settings::error("EntityInstanceData::getVariable - variable instance map for object name \"" + objectName + "\" not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getTags() const
	{
		return getTags("");
	}

	UniversalObjectInterface *EntityInstanceData::getTags(s_int objectId) const
	{
		auto it = tags.find(objectId);
		if (it != tags.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getTags - taglist for object id " + std::to_string(objectId) + " not found");
			return 0;
		}
	}

	bool EntityInstanceData::tagIsActive(s_int objectId, const Core::String &tagToCheck) const
	{
		UniversalObjectInterface *tagList = getTags(objectId);
		if (tagList)
		{
			return tagList->tagIsActive(tagToCheck);
		}
		else
		{
			Settings::error("entityInstanceData::tagIsActive - taglist for object id " + std::to_string(objectId) + " not found");
			return false;
		}
	}

	bool EntityInstanceData::tagIsActive(const Core::String &tagToCheck) const
	{
		return tagIsActive("", tagToCheck);
	}

	UniversalObjectInterface *EntityInstanceData::getTags(const Core::String &objectName) const
	{
		auto it = tagObjectNameMap.find(objectName);
		if (it != tagObjectNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getTags - taglist for object name \"" + objectName + "\" not found");
			return 0;
		}
	}

	bool EntityInstanceData::tagIsActive(const Core::String &objectName, const Core::String &tagToCheck) const
	{
		UniversalObjectInterface *tagList = getTags(objectName);
		if (tagList)
		{
			return tagList->tagIsActive(tagToCheck);
		}
		else
		{
			Settings::error("EntityInstanceData::tagIsActive - taglist for object name \"" + objectName + "\" not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getTriggerObject(s_int triggerId)
	{
		auto it = triggers.find(triggerId);
		if (it != triggers.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getTriggerObject - trigger instance with id " + std::to_string(triggerId) + " not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getTriggerObject(const Core::String &triggerName)
	{
		auto it = triggerNameMap.find(triggerName);
		if (it != triggerNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getTriggerObject - trigger instance with name \"" + triggerName + "\" not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getSoundObject(s_int soundId)
	{
		auto it = sounds.find(soundId);
		if (it != sounds.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getSoundObject - sound instance with id " + std::to_string(soundId) + " not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getSoundObject(const Core::String &soundName)
	{
		auto it = soundNameMap.find(soundName);
		if (it != soundNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getSoundObject - sound instance with name \"" + soundName + "\" not found");
			return 0;
		}
	}

	void EntityInstanceData::setCurrentAnimation(s_int newAnimationIndex, AnimationInstance **currentAnimation)
	{
		if (newAnimationIndex < animations.size())
		{
			*currentAnimation = animations.at(newAnimationIndex);
		}
		else
		{
			Settings::error("EntityInstanceData::setCurrentAnimation - animation index " + std::to_string(newAnimationIndex) + " out of range");
		}
	}

	void EntityInstanceData::setCurrentAnimation(const Core::String & animationName, AnimationInstance **currentAnimation)
	{
		auto it = animationNameMap.find(animationName);
		if (it != animationNameMap.end())
		{
			*currentAnimation = (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::setCurrentAnimation - animation with name \"" + animationName + "\" not found");
		}
	}

	void EntityInstanceData::pushBackAnimationInstance(const Core::String &name, AnimationInstance * newAnimationInstance)
	{
		animations.push_back(newAnimationInstance);
		animationNameMap[name] = animations.back();
	}

	void EntityInstanceData::setObjectInstance(s_int id, const Core::String &name, UniversalObjectInterface * newObjectInstance)
	{
		if (objects.count(id)) {
			//TODO: what to do here?
			// Delete newObjectInstance or delete the current value in objects?
			// before this change newObjectInstance was just ignored, so I'll remove it.
			Settings::error("EntityInstanceData::setObjectInstance - object with id \"" + std::to_string(id) + "\" already exists");
			delete newObjectInstance;
			return;
		}
		objectNameMap[name] = (*objects.insert(std::make_pair(id, newObjectInstance)).first).second;
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariableInstanceMap(s_int objectId, const Core::String &objectName)
	{
		return variableObjectNameMap[objectName] = &variables[objectId];
	}

	void EntityInstanceData::setTagInstance(s_int objectId, const Core::String &objectName)
	{
		if (tags.count(objectId)) {
			Settings::error("EntityInstanceData::setTagInstance - tag with id \"" + std::to_string(objectId) + "\" already exists");
			return;
		}
		tagObjectNameMap[objectName] = (*tags.insert(std::make_pair(objectId, new TagObjectInfoReference())).first).second;
	}

	void EntityInstanceData::setSoundInstance(s_int id, const Core::String &name, FileReference * soundRef)
	{
		SoundFile *soundFile = soundRef->sound();
		if (soundFile)
		{
			if (sounds.count(id)) {
				Settings::error("EntityInstanceData::setSoundInstance - sounds with id \"" + std::to_string(id) + "\" already exists");
				return;
			}
			soundNameMap[name] = (*sounds.insert(std::make_pair(id, soundFile->newSoundInfoReference())).first).second;
		}
	}

	void EntityInstanceData::setTriggerInstance(s_int id, const Core::String &name, TriggerObjectInfo *newCustomTriggerObject)
	{
		if (triggers.count(id)) {
			Settings::error("EntityInstanceData::setTriggerInstance - sounds with id \"" + std::to_string(id) + "\" already exists");
			return;
		}
		TriggerObjectInfo *newTriggerObject = newCustomTriggerObject;
		if (!newTriggerObject)
		{
			newTriggerObject = new TriggerObjectInfo();
		}
		triggerNameMap[name] = (*triggers.insert(std::make_pair(id, newTriggerObject)).first).second;
	}

	AnimationInstance * EntityInstanceData::getAnimation(s_int animationIndex)
	{
		if (animationIndex < animations.size())
		{
			return animations.at(animationIndex);
		}
		else
		{
			Settings::error("EntityInstanceData::getAnimation - animation index " + std::to_string(animationIndex) + " out of range");
			return 0;
		}
	}

	AnimationInstance * EntityInstanceData::getAnimation(const Core::String &animationName)
	{
		auto it = animationNameMap.find(animationName);
		if (it != animationNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstanceData::getAnimation - animation with name \"" + animationName + "\" not found");
			return 0;
		}
	}

	void EntityInstanceData::playSoundTriggers()
	{
		for (auto& it : sounds)
		{
			it.second->playTrigger();
		}
	}

	void EntityInstanceData::playEventTriggers()
	{
		for (auto& it : triggers)
		{
			it.second->playTrigger();
		}
	}

	void EntityInstanceData::updateTransformProcessor()
	{
		transformProcessor->setTrigFunctions();
	}

	Core::String EntityInstanceData::getName()
	{
		return entityName;
	}

	s_int EntityInstanceData::animationCount()
	{
		return animations.size();
	}
}