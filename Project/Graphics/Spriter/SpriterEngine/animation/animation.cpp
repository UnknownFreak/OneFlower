#include "animation.h"

#include "../global/settings.h"

#include "../timeline/timeline.h"
#include "../timeline/timelineinstance.h"
#include "../timeline/soundtimelineinstance.h"
#include "../timeline/triggertimelineinstance.h"
#include "../timeline/variabletimelineinstance.h"
#include "../timeline/tagtimelineinstance.h"

#include "mainlinekeyinstance.h"

namespace SpriterEngine
{
	Animation::Animation(Core::String initialName, real initialAnimationLength, bool initialLooping) :
		name(initialName),
		animationLength(initialAnimationLength),
		isLooping(initialLooping)
	{
	}

	Animation::~Animation()
	{
		for (auto& it : mainlineKeys)
		{
			delete it;
		}

		for (auto& it : objectTimelines)
		{
			delete it;
		}

		for (auto& outerIt : variableTimelines)
		{
			for (auto& innerIt : outerIt.second)
			{
				delete innerIt.second;
			}
		}

		for (auto& it : tagTimelines)
		{
			delete it;
		}

		for (auto& it : soundTimelines)
		{
			delete it;
		}

		for (auto& it : triggerTimelines)
		{
			delete it;
		}
	}

	Core::String Animation::getName()
	{
		return name;
	}

	real Animation::getLength()
	{
		return animationLength;
	}

	bool Animation::getIsLooping()
	{
		return isLooping;
	}

	void Animation::setupAnimationInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, MainlineKeyInstanceVector *mainlineKeyInstances, TimelineInstanceVector *timelineInstances, real *length, bool *looping)
	{
		for (auto& it : mainlineKeys)
		{
			mainlineKeyInstances->push_back(new MainlineKeyInstance(entityInstance, entityInstanceData, it));
		}
		for (auto& it : tagTimelines)
		{
			timelineInstances->push_back(new TagTimelineInstance(entityInstanceData, it, it->getObjectId()));
		}
		for (auto& it : soundTimelines)
		{
			timelineInstances->push_back(new SoundTimelineInstance(entityInstanceData, it, it->getObjectId()));
		}
		for (auto& it : triggerTimelines)
		{
			timelineInstances->push_back(new TriggerTimelineInstance(entityInstanceData, it, it->getObjectId()));
		}
		for (auto& objectIt : variableTimelines)
		{
			for (auto& variableIt : objectIt.second)
			{
				timelineInstances->push_back(new VariableTimelineInstance(entityInstanceData, variableIt.second, objectIt.first, variableIt.first));
			}
		}
		*length = animationLength;
		*looping = isLooping;
	}

	MainlineKey *Animation::pushBackMainlineKey(TimeInfo *initialTimeInfo)
	{
		mainlineKeys.push_back(new MainlineKey(initialTimeInfo));
		return mainlineKeys.back();
	}

	Timeline *Animation::pushBackObjectTimeline(s_int objectId)
	{
		objectTimelines.push_back(new Timeline(objectId));
		return objectTimelines.back();
	}

	Timeline *Animation::setVariableTimeline(s_int objectId, s_int variableId)
	{
		TimelineMap *objectVariables = &variableTimelines[objectId];
		auto it = objectVariables->find(variableId);
		if (it == objectVariables->end())
		{
			return (*objectVariables->insert(std::make_pair(variableId, new Timeline(objectId))).first).second;
		}
		else
		{
			return 0;
		}
	}

	Timeline *Animation::pushBackTagTimeline(s_int objectId)
	{
		tagTimelines.push_back(new Timeline(objectId));
		return tagTimelines.back();
	}

	Timeline *Animation::pushBackSoundTimeline(s_int objectId)
	{
		soundTimelines.push_back(new Timeline(objectId));
		return soundTimelines.back();
	}

	Timeline *Animation::pushBackTriggerTimeline(s_int objectId)
	{
		triggerTimelines.push_back(new Timeline(objectId));
		return triggerTimelines.back();
	}

	s_int Animation::getObjectIdFromTimelineIndex(s_int timelineIndex)
	{
		if (timelineIndex < objectTimelines.size())
		{
			return objectTimelines.at(timelineIndex)->getObjectId();
		}
		else
		{
			Settings::error("Animation::getObjectIdFromTimelineIndex - timeline index " + std::to_string(timelineIndex) + " out of range");
			return OUT_OF_RANGE;
		}
	}

	TimelineKey *Animation::getObjectTimelineKey(s_int timelineIndex, s_int keyIndex)
	{
		if (timelineIndex < objectTimelines.size())
		{
			return objectTimelines.at(timelineIndex)->getKey(keyIndex);
		}
		else
		{
			Settings::error("Animation::getObjectTimelineKey - timeline index " + std::to_string(timelineIndex) + " out of range");
			return 0;
		}
	}
}