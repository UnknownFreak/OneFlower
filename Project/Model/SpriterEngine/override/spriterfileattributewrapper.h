#ifndef SPRITERFILEATTRIBUTEWRAPPER_H
#define SPRITERFILEATTRIBUTEWRAPPER_H

#include "../global/global.h"

namespace SpriterEngine
{
	class SpriterFileAttributeWrapper
	{
	public:
		SpriterFileAttributeWrapper();
		virtual ~SpriterFileAttributeWrapper();

		virtual Core::String getName() = 0;

		virtual bool isValid() = 0;

		virtual real getRealValue() = 0;
		virtual s_int getIntValue() = 0;
		virtual Core::String getStringValue() = 0;

		virtual void advanceToNextAttribute() = 0;
	};
}

#endif // SPRITERFILEATTRIBUTEWRAPPER_H