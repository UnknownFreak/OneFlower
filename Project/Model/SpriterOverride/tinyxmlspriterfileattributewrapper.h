#ifndef TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H
#define TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H

#include "../tinyxml2/tinyxml2.h"

#include "../spriterengine/override/spriterfileattributewrapper.h"

namespace SpriterEngine
{
	class TinyXmlSpriterFileAttributeWrapper : public SpriterFileAttributeWrapper
	{
	public:
		TinyXmlSpriterFileAttributeWrapper(const tinyxml2::XMLAttribute *initialAttribute);

		Core::String getName() override;

		bool isValid() override;

		real getRealValue() override;
		s_int getIntValue() override;
		Core::String getStringValue() override;

		void advanceToNextAttribute() override;

	private:
		const tinyxml2::XMLAttribute *attribute;
	};
}

#endif // TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H