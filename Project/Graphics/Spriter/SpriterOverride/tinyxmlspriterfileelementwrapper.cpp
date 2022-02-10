#include "tinyxmlspriterfileelementwrapper.h"

#include "tinyxmlspriterfileattributewrapper.h"

namespace SpriterEngine
{
	TinyXmlSpriterFileElementWrapper::TinyXmlSpriterFileElementWrapper(tinyxml2::XMLElement *initialElement) :
		element(initialElement)
	{
	}

	Core::String TinyXmlSpriterFileElementWrapper::getName()
	{
		return element->Value();
	}

	bool TinyXmlSpriterFileElementWrapper::isValid()
	{
		return element!=NULL;
	}

	void TinyXmlSpriterFileElementWrapper::advanceToNextSiblingElement()
	{
		element = element->NextSiblingElement();
	}

	void TinyXmlSpriterFileElementWrapper::advanceToNextSiblingElementOfSameName()
	{
		element = element->NextSiblingElement(getName().c_str());
	}

	SpriterFileAttributeWrapper * TinyXmlSpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute()
	{
		return new TinyXmlSpriterFileAttributeWrapper(element->FirstAttribute());
	}

	SpriterFileAttributeWrapper * TinyXmlSpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute(const Core::String & attributeName)
	{
		return new TinyXmlSpriterFileAttributeWrapper(findAttributeInElement(attributeName));
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementWrapperFromFirstElement()
	{
		return new TinyXmlSpriterFileElementWrapper(element->FirstChildElement());
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementWrapperFromFirstElement(const Core::String & elementName)
	{
		return new TinyXmlSpriterFileElementWrapper(element->FirstChildElement(elementName.c_str()));
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementWrapperFromNextSiblingElement()
	{
		return new TinyXmlSpriterFileElementWrapper(element->NextSiblingElement(getName().c_str()));
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementClone()
	{
		return new TinyXmlSpriterFileElementWrapper(element);
	}

	const tinyxml2::XMLAttribute * TinyXmlSpriterFileElementWrapper::findAttributeInElement(const Core::String & name)
	{
		const tinyxml2::XMLAttribute *attribute = element->FirstAttribute();

		while (attribute)
		{
			if (attribute->Name() == name)
			{
				return attribute;
			}

			attribute = attribute->Next();
		}

		return 0;
	}
}