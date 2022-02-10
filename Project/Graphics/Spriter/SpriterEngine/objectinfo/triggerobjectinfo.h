#ifndef TRIGGEROBJECTINFO_H
#define TRIGGEROBJECTINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{
	class TriggerObjectInfo : public UniversalObjectInterface
	{
	public:
		TriggerObjectInfo();

		s_int getTriggerCount() override;
		void setTriggerCount(s_int newTriggerCount) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance * refInstance) override;

		// TODO: override play trigger to enable triggers to perform an action based on getTriggerCount()

	private:
		s_int triggerCount;
	};
}

#endif // TRIGGEROBJECTINFO_H
