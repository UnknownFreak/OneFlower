#ifndef ENTITYINSTANCE_H
#define ENTITYINSTANCE_H

#include <map>
#include <vector>
#include <list>
#include "../animation/animationinstance.h"
#include "../objectref/transformprocessor.h"
#include "../file/filereference.h"
#include "../objectinfo/entityobjectinfo.h"
#include "../variable/variableinstancenameandidmap.h"

#include "entityinstancedata.h"

namespace SpriterEngine
{
	class Entity;
	class SpriterModel;
	class CharacterMapInterface;
	class ObjectFactory;

	typedef std::map<s_int, EntityInstanceData*> EntityInstanceDataMap;
	typedef std::vector<FileReference*> FileReferenceVector;
	typedef std::list<Core::String> StringList;

	class EntityInstance : public UniversalObjectInterface
	{
	public:
		EntityInstance();
		EntityInstance(SpriterModel *model, Entity *entity, CharacterMapInterface *initialCharacterMapInterface, ObjectFactory *objectFactory);
		~EntityInstance();

		void setTimeElapsed(real timeElapsed);

		void startResumePlayback();
		void pausePlayback();

		void blend(real blendRatio, real timeRatio);

		void reprocessCurrentTime() override;

		UniversalObjectInterface *getObjectInstance(s_int objectId);
		UniversalObjectInterface * getObjectInstance(const Core::String &objectName);
		FileReference *getFile(s_int fileId);

		point getPosition() const override;
		real getAngle() const override;
		point getScale() const override;
		real getAlpha() const override;

		real getCurrentTime() override;
		real getTimeRatio() override;

		Core::String currentEntityName();
		Core::String currentAnimationName();

		s_int animationCount();

		s_int currentMainlineKeyIndex();

		bool animationJustFinished(bool orLooped = false);
		bool animationJustLooped();

		VariableInstanceNameAndIdMap *getVariables() override;
		UniversalObjectInterface *getVariable(s_int variableId);
		VariableInstanceNameAndIdMap *getVariables(s_int objectId);
		UniversalObjectInterface *getVariable(s_int objectId, s_int variableId);

		UniversalObjectInterface *getVariable(const Core::String &variableName);
		VariableInstanceNameAndIdMap *getVariables(const Core::String &objectName);
		UniversalObjectInterface *getVariable(const Core::String &objectName, const Core::String &variableName);

		virtual real getRealValue(const Core::String &variableName);
		virtual s_int getIntValue(const Core::String &variableName);
		virtual Core::String getStringValue(const Core::String &variableName);

		virtual real getRealValue(const Core::String &objectName, const Core::String &variableName);
		virtual s_int getIntValue(const Core::String &objectName, const Core::String &variableName);
		virtual Core::String getStringValue(const Core::String &objectName, const Core::String &variableName);

		UniversalObjectInterface *getTags() const override;
		UniversalObjectInterface *getTags(s_int objectId) const;
		bool tagIsActive(s_int objectId, const Core::String &tagToCheck) const;

		bool tagIsActive(const Core::String &tagToCheck) const override;
		UniversalObjectInterface *getTags(const Core::String &objectName) const;
		bool tagIsActive(const Core::String &objectName, const Core::String &tagToCheck) const;

		UniversalObjectInterface *getTriggerObject(s_int triggerId);
		UniversalObjectInterface *getTriggerObject(const Core::String &triggerName);

		UniversalObjectInterface *getSoundObject(s_int soundId);
		UniversalObjectInterface *getSoundObject(const Core::String &soundName);

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;
		void setSpin(s_int newSpin) override;

		void setCurrentEntity(s_int newEntityIndex) override;
		void setCurrentEntity(EntityInstanceData *newCurrentEntity) override;
		void setCurrentEntity(const Core::String & newEntityName, const Core::String & newAnimationName = "", SpriterModel * modelForAutoAppend = 0);
		void setCurrentAnimation(s_int newAnimationIndex) override;
		void setCurrentAnimation(const Core::String &animationName);
		void setCurrentAnimation(const Core::String &animationName, real blendTime);
		void setCurrentAnimation(AnimationInstance *newCurrentAnimation) override;
		void setCurrentTime(real newCurrentTime);
		void setTimeRatio(real newCurrentTimeRatio) override;

		void setPlaybackSpeedRatio(real newPlaybackSpeedRatio);

		void setCurrentTimeToPreviousKeyFrame();
		void setCurrentTimeToNextKeyFrame();
		void setCurrentTimeToKeyAtIndex(s_int newKeyIndex);

		UniversalObjectInterface *objectIfExistsOnCurrentFrame(const Core::String & objectName);

		void applyCharacterMap(const Core::String &mapName);
		void removeCharacterMap(const Core::String &mapName);
		void removeAllCharacterMaps();

		void render() override;

		void playAllTriggers();
		void playSoundTriggers();
		void playEventTriggers();

		ObjectInterfaceVector *getZOrder() override;

		void appendEntity(SpriterModel *model, Entity *entity, ObjectFactory *objectFactory);
		void appendEntity(SpriterModel * model, Core::String entityName);

		EntityInstanceData *getEntity(s_int entityId) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

		//Inherited via UniversalObjectInterface
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		EntityInstanceDataMap entities;

		FileReferenceVector files;

		ObjectInterfaceVector *zOrder;

		point position;
		AngleInfo angle;
		point scale;
		real alpha;

		EntityInstanceData *currentEntity;
		AnimationInstance *currentAnimation;

		bool isPlaying;

		bool justFinished;

		AnimationInstance *blendedAnimation;
		real blendTotalTime;
		real blendCurrentTime;

		CharacterMapInterface *characterMapInterface;

		StringList appliedCharacterMaps;

		real playbackSpeedRatio;
	};
}

#endif // ENTITYINSTANCE_H
