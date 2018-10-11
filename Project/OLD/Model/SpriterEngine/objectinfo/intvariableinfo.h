#ifndef INTVARIABLEINFO_H
#define INTVARIABLEINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{
	class IntVariableInfo : public UniversalObjectInterface
	{
	public:
		IntVariableInfo();

		s_int getIntValue() override;
		void setIntValue(s_int newValue) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

	private:
		s_int value;
	};
}

#endif // INTVARIABLEINFO_H
