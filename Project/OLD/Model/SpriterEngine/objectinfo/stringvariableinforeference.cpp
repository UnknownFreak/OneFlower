#include "stringvariableinforeference.h"

namespace SpriterEngine
{
	StringVariableInfoReference::StringVariableInfoReference() :
		value(0)
	{
	}

	Core::String StringVariableInfoReference::getStringValue()
	{
		if (value)
		{
			return *value;
		}
		else
		{
			return "";
		}
	}

	void StringVariableInfoReference::setStringValue(Core::String *newValue)
	{
		value = newValue;
	}

	void StringVariableInfoReference::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		if (blendRatio >= 0.5)
		{
			aObject->setObjectToLinear(bObject, t, this);
		}
	}
}