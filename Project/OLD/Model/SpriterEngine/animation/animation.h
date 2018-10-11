#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "../timeline/timeline.h"

#include "mainlinekey.h"
#include "mainlinekeyinstance.h"

namespace SpriterEngine
{
	class TimelineInstance;
	class VariableTimeline;
	class TimelineKey;

	typedef std::vector<MainlineKey*> MainlineKeyVector;
	typedef std::vector<Timeline*> TimelineVector;
	typedef std::map<s_int, Timeline*> TimelineMap;
	typedef std::map<s_int, TimelineMap> Timeline2DMap;
	typedef std::vector<MainlineKeyInstance*> MainlineKeyInstanceVector;
	typedef std::vector<TimelineInstance*> TimelineInstanceVector;

	class Animation
	{
	public:
		Animation(Core::String initialName, real initialAnimationLength, bool initialLooping);
		~Animation();

		Core::String getName();
		real getLength();
		bool getIsLooping();

		void setupAnimationInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, MainlineKeyInstanceVector *mainlineKeyInstances, TimelineInstanceVector *timelineInstances, real *length, bool *looping);

		MainlineKey *pushBackMainlineKey(TimeInfo *initialTimeInfo);

		Timeline *pushBackObjectTimeline(s_int objectId);

		Timeline *setVariableTimeline(s_int objectId, s_int variableId);
		Timeline *pushBackTagTimeline(s_int objectId);
		Timeline *pushBackSoundTimeline(s_int objectId);
		Timeline *pushBackTriggerTimeline(s_int objectId);

		s_int getObjectIdFromTimelineIndex(s_int timelineIndex);
		TimelineKey *getObjectTimelineKey(s_int timelineIndex, s_int keyIndex);

	private:
		Core::String name;

		MainlineKeyVector mainlineKeys;

		TimelineVector objectTimelines;

		Timeline2DMap variableTimelines;
		TimelineVector tagTimelines;
		TimelineVector soundTimelines;
		TimelineVector triggerTimelines;

		real animationLength;
		bool isLooping;
	};
}

#endif // ANIMATION_H
