#include "intvariableinfo.h"

namespace SpriterEngine
{
	IntVariableInfo::IntVariableInfo() :
		value(0)
	{
	}

	s_int IntVariableInfo::getIntValue()
	{
		return value;
	}

	void IntVariableInfo::setIntValue(s_int newValue)
	{
		value = newValue;
	}

	void IntVariableInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setIntValue(s_int(linear(real(value), real(bObject->getIntValue()), t)));
	}

	void IntVariableInfo::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *)
	{
		real tempValue = real(value);

		aObject->setObjectToLinear(bObject, t, this);

		setIntValue(s_int(linear(tempValue, real(value), blendRatio)));
	}
}