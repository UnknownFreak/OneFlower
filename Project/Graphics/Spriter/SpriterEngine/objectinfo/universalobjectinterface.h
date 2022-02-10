#ifndef UNIVERSALOBJECTINTERFACE_H
#define UNIVERSALOBJECTINTERFACE_H

#include <Helpers/String.hpp>
#include <vector>

#include "../global/global.h"

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace SpriterEngine
{
	class UniversalObjectInterface;
	class ImageFile;
	class SoundFile;
	class EntityInstanceData;
	class AnimationInstance;
	class TagList;
	class VariableInstanceNameAndIdMap;
	class TagObjectInfoReference;
	class TimelineKey;
	class ObjectRefInstance;

	typedef std::vector<UniversalObjectInterface*> ObjectInterfaceVector;

	class UniversalObjectInterface : public sf::Drawable
	{
	public:
		UniversalObjectInterface();
		virtual ~UniversalObjectInterface() = 0;

		virtual point getPosition() const;
		virtual real getAngle() const;
		virtual point getScale() const;
		virtual point getPivot() const;
		virtual real getAlpha() const;

		virtual point getSize() const;

		virtual ImageFile *getImage();

		virtual EntityInstanceData *getEntity(s_int entityId);
		virtual real getCurrentTime();
		virtual real getTimeRatio();

		virtual void reprocessCurrentTime();

		virtual ObjectInterfaceVector *getZOrder();

		virtual real getRealValue();
		virtual s_int getIntValue();
		virtual Core::String getStringValue();

		virtual s_int getTriggerCount();

		virtual real getVolume();
		virtual real getPanning();

		virtual VariableInstanceNameAndIdMap *getVariables();
		virtual UniversalObjectInterface *getTags() const;

		virtual bool tagIsActive(const Core::String &tagToCheck) const;

		virtual void setPosition(const point &newPosition);
		virtual void setAngle(real newAngle);
		virtual void setScale(const point &newScale);
		virtual void setPivot(const point &newPivot);
		virtual void setAlpha(real newAlpha);
		virtual void setSpin(s_int newSpin);

		virtual void setImage(ImageFile *newImageFile);

		virtual void setCurrentEntity(s_int newEntityIndex);
		virtual void setCurrentEntity(EntityInstanceData *newCurrentEntity);
		virtual void setCurrentAnimation(s_int newAnimationIndex);
		virtual void setCurrentAnimation(AnimationInstance *newCurrentAnimation);
		virtual void setTimeRatio(real newCurrentTimeRatio);

		virtual void setRealValue(real newValue);
		virtual void setIntValue(s_int newValue);
		virtual void setStringValue(const Core::String &newValue);
		virtual void setStringValue(Core::String *newValue);

		virtual void setTriggerCount(s_int newTriggerCount);

		virtual void setVolume(real newVolume);
		virtual void setPanning(real newPanning);

		virtual void setSound(SoundFile *newSoundFile);

		virtual void setTagList(TagList *newTagList);

		virtual void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject);
		virtual void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0);

		virtual void render();

		virtual void playTrigger();

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	};
}

#endif // UNIVERSALOBJECTINTERFACE_H
