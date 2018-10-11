#ifndef TINYXMLSPRITERFILEDOCUMENTWRAPPER_H
#define TINYXMLSPRITERFILEDOCUMENTWRAPPER_H

#include "../tinyxml2/tinyxml2.h"

#include "../spriterengine/override/spriterfiledocumentwrapper.h"

namespace SpriterEngine
{
	class TinyXmlSpriterFileDocumentWrapper : public SpriterFileDocumentWrapper
	{
	public:
		TinyXmlSpriterFileDocumentWrapper();

		void loadFile(Core::String fileName) override;

	private:
		SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
		SpriterFileElementWrapper *newElementWrapperFromFirstElement(const Core::String & elementName) override;

		tinyxml2::XMLDocument doc;
	};
}

#endif // TINYXMLSPRITERFILEDOCUMENTWRAPPER_H