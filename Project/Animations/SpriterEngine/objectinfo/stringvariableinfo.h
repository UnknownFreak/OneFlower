#ifndef STRINGVARIABLEINFO_H
#define STRINGVARIABLEINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{
	class StringVariableInfo : public UniversalObjectInterface
	{
	public:
		StringVariableInfo();

		Core::String getStringValue() override;
		void setStringValue(const Core::String &newValue) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		Core::String value;
	};
}

#endif // STRINGVARIABLEINFO_H
