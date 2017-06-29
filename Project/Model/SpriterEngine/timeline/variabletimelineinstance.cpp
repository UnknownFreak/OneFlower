#include "variabletimelineinstance.h"

#include "../entity/entityinstancedata.h"

namespace SpriterEngine
{
	VariableTimelineInstance::VariableTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, s_int objectId, s_int initialVariableId) :
		TimelineInstance(timeline)
	{
		resultObject = entityInstanceData->getVariable(objectId, initialVariableId);
	}
}