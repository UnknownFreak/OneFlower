#ifndef TINYXMLSPRITERFILEELEMENTWRAPPER_H
#define TINYXMLSPRITERFILEELEMENTWRAPPER_H

#include <Core\String.hpp>

#include "../tinyxml2/tinyxml2.h"

#include "../spriterengine/override/spriterfileelementwrapper.h"

namespace SpriterEngine
{
	class TinyXmlSpriterFileElementWrapper : public SpriterFileElementWrapper
	{
	public:
		TinyXmlSpriterFileElementWrapper(tinyxml2::XMLElement *initialElement);

		Core::String getName() override;

		bool isValid() override;

		void advanceToNextSiblingElement() override;
		void advanceToNextSiblingElementOfSameName() override;

	private:
		SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute() override;
		SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute(const Core::String & attributeName) override;

		SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
		SpriterFileElementWrapper *newElementWrapperFromFirstElement(const Core::String & elementName) override;

		SpriterFileElementWrapper *newElementWrapperFromNextSiblingElement() override;

		SpriterFileElementWrapper *newElementClone() override;

		const tinyxml2::XMLAttribute * findAttributeInElement(const Core::String & name);

		tinyxml2::XMLElement *element;
	};
}

#endif // TINYXMLSPRITERFILEELEMENTWRAPPER_H