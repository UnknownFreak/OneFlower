#include "triggerobjectinfo.h"

namespace SpriterEngine
{
	TriggerObjectInfo::TriggerObjectInfo() :
		triggerCount(0)
	{
	}

	s_int TriggerObjectInfo::getTriggerCount()
	{
		return triggerCount;
	}

	void TriggerObjectInfo::setTriggerCount(s_int newTriggerCount)
	{
		triggerCount = newTriggerCount;
	}

	void TriggerObjectInfo::setToBlendedLinear(UniversalObjectInterface *, UniversalObjectInterface *, real , real , ObjectRefInstance *)
	{
	}
}