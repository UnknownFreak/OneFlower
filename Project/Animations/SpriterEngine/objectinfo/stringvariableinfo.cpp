#include "stringvariableinfo.h"

namespace SpriterEngine
{
	StringVariableInfo::StringVariableInfo()
	{
	}

	Core::String StringVariableInfo::getStringValue()
	{
		return value;
	}

	void StringVariableInfo::setStringValue(const Core::String &newValue)
	{
		value = newValue;
	}

	void StringVariableInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setStringValue(&value);
	}
}