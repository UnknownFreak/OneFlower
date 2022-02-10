#ifndef SPRITERFILEDOCUMENTWRAPPER_H
#define SPRITERFILEDOCUMENTWRAPPER_H

#include <Helpers/String.hpp>
#include <vector>

namespace SpriterEngine
{
	class SpriterFileElementWrapper;

	typedef std::vector<SpriterFileElementWrapper*> ElementVector;

	class SpriterFileDocumentWrapper
	{
	public:
		SpriterFileDocumentWrapper();

		virtual ~SpriterFileDocumentWrapper();

		virtual void loadFile(Core::String fileName) = 0;

		SpriterFileElementWrapper *getFirstChildElement();
		SpriterFileElementWrapper *getFirstChildElement(Core::String elementName);

	private:
		virtual SpriterFileElementWrapper *newElementWrapperFromFirstElement() = 0;
		virtual SpriterFileElementWrapper *newElementWrapperFromFirstElement(const Core::String & elementName) = 0;

		ElementVector childElements;
	};
}

#endif // SPRITERFILEDOCUMENTWRAPPER_H