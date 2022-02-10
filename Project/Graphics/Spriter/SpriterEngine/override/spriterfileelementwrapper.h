#ifndef SPRITERFILEELEMENTWRAPPER_H
#define SPRITERFILEELEMENTWRAPPER_H

#include <Helpers/String.hpp>
#include <vector>

namespace SpriterEngine
{
	class SpriterFileElementWrapper;
	class SpriterFileAttributeWrapper;

	typedef std::vector<SpriterFileElementWrapper*> ElementVector;
	typedef std::vector<SpriterFileAttributeWrapper*> AttributeVector;

	class SpriterFileElementWrapper
	{
	public:
		SpriterFileElementWrapper();
		virtual ~SpriterFileElementWrapper();

		virtual Core::String getName() = 0;

		virtual bool isValid() = 0;

		SpriterFileAttributeWrapper *getFirstAttribute();
		SpriterFileAttributeWrapper *getFirstAttribute(const Core::String & attributeName);

		SpriterFileElementWrapper *getFirstChildElement();
		SpriterFileElementWrapper *getFirstChildElement(const Core::String & elementName);

		virtual void advanceToNextSiblingElement() = 0;
		virtual void advanceToNextSiblingElementOfSameName() = 0;

		SpriterFileElementWrapper *getNextSiblingElement();
		SpriterFileElementWrapper *getCloneElement();

	private:
		virtual SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute() = 0;
		virtual SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute(const Core::String & attributeName) = 0;

		virtual SpriterFileElementWrapper *newElementWrapperFromFirstElement() = 0;
		virtual SpriterFileElementWrapper *newElementWrapperFromFirstElement(const Core::String & elementName) = 0;

		virtual SpriterFileElementWrapper *newElementWrapperFromNextSiblingElement() = 0; // ensure sibling has the same name
		virtual SpriterFileElementWrapper *newElementClone() = 0; // ensure sibling has the same name

		ElementVector childElements;
		AttributeVector childAttributes;
	};
}

#endif // SPRITERFILEELEMENTWRAPPER_H