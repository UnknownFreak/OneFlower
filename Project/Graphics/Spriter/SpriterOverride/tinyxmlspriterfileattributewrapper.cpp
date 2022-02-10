#include "tinyxmlspriterfileattributewrapper.h"

namespace SpriterEngine
{
	TinyXmlSpriterFileAttributeWrapper::TinyXmlSpriterFileAttributeWrapper(const tinyxml2::XMLAttribute *initialAttribute) :
		attribute(initialAttribute)
	{
	}

	Core::String TinyXmlSpriterFileAttributeWrapper::getName()
	{
		return attribute->Name();
	}

	bool TinyXmlSpriterFileAttributeWrapper::isValid()
	{
		return attribute!=NULL;
	}

	real TinyXmlSpriterFileAttributeWrapper::getRealValue()
	{
		return attribute->FloatValue();
	}

	int TinyXmlSpriterFileAttributeWrapper::getIntValue()
	{
		return attribute->IntValue();
	}

	Core::String TinyXmlSpriterFileAttributeWrapper::getStringValue()
	{
		return attribute->Value();
	}

	void TinyXmlSpriterFileAttributeWrapper::advanceToNextAttribute()
	{
		attribute = attribute->Next();
	}
}