#ifndef STRINGVARIABLEINFOREFERENCE_H
#define STRINGVARIABLEINFOREFERENCE_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{
	class StringVariableInfoReference : public UniversalObjectInterface
	{
	public:
		StringVariableInfoReference();

		Core::String getStringValue() override;
		void setStringValue(Core::String *newValue) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

	private:
		Core::String *value;
	};
}

#endif // STRINGVARIABLEINFOREFERENCE_H
