#ifndef ANIMATIONINSTANCE_H
#define ANIMATIONINSTANCE_H

#include <vector>

#include "mainlinekeyinstance.h"

namespace SpriterEngine
{
	class MainlineKeyInstance;
	class EntityInstanceData;
	class Animation;
	class TimelineInstance;

	typedef std::vector<MainlineKeyInstance*> MainlineKeyInstanceVector;
	typedef MainlineKeyInstanceVector::iterator MainlineKeyInstanceVectorIterator;
	typedef std::vector<TimelineInstance*>TimelineInstanceVector;

	class AnimationInstance
	{
	public:
		AnimationInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, Animation *animation);
		~AnimationInstance();

		void findAndProcessKeys(real newTime, bool forward, ObjectInterfaceVector ** instanceZOrder);

		void findCurrentKeys(real newTime, bool forward);
		void processCurrentKeys(real newTime, ObjectInterfaceVector **instanceZOrder);

		Core::String getName();

		bool looping();

		real length();

		real currentTime();

		s_int currentMainlineKeyIndex();

		void setCurrentTimeToPreviousKeyFrame(ObjectInterfaceVector **instanceZOrder);
		void setCurrentTimeToNextKeyFrame(ObjectInterfaceVector **instanceZOrder);
		void setCurrentTimeToKeyAtIndex(s_int newIndex, ObjectInterfaceVector **instanceZOrder);

		real processRefKeys(real newTime);
		void blendRefKeys(real newTime, real blendRatio);
		void setZOrder(ObjectInterfaceVector ** instanceZOrder);
		void processRefTransforms();

		void processCurrentTimelineKeys(real newTime);

		void blendCurrentTimelineKeys(real newTime, real blendRatio);

		s_int mainlineKeyCount();

	private:
		void findCurrentTimelineKeys(real newTime, bool forward);

		void findCurrentMainlineKey(real newTime, bool forward);
		real processCurrentMainlineKey(real newTime, ObjectInterfaceVector **instanceZOrder);

		void findMainlineKeyTimeForward(real newTime);
		void findMainlineKeyTimeBackward(real newTime);

		real time;

		MainlineKeyInstanceVector mainlineKeys;
		MainlineKeyInstanceVectorIterator mainlineKeyIterator;

		MainlineKeyInstance *mainlineKeyAtIndex(s_int index);

		TimelineInstanceVector timelines;

		Core::String name;

		real animationLength;
		bool isLooping;
	};
}

#endif // ANIMATIONINSTANCE_H
