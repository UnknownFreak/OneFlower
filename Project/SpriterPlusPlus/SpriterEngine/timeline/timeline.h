#ifndef TIMELINE_H
#define TIMELINE_H

#include <vector>

#include "timelinekey.h"

namespace SpriterEngine
{
	class TimelineInstance;

	typedef std::vector<TimelineKey*> TimelineKeyVector;

	class Timeline
	{
	public:
		Timeline(s_int initialObjectId);
		~Timeline();

		s_int getObjectId();

		TimelineKey *pushBackKey(TimeInfo *initialTimeInfo, UniversalObjectInterface *initialObjectInfo);

		TimelineKey * pushFrontProxyKey(real initialTime, real initialNextTime, bool isLooping);

		TimelineKey *getKey(size_t keyIndex);

		TimelineKey * getLastKey();

		void setupTimelineInstance(TimelineKeyVector **keyInstances);

	private:
		s_int objectId;

		TimelineKeyVector keys;
	};
}

#endif // TIMELINE_H
