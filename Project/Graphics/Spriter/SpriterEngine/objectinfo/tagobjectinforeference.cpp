#include "tagobjectinforeference.h"

#include "taglist.h"

namespace SpriterEngine
{
	TagObjectInfoReference::TagObjectInfoReference() :
		tagList(0)
	{
	}

	bool TagObjectInfoReference::tagIsActive(const Core::String &tagToCheck) const
	{
		if (tagList)
		{
			return tagList->tagIsActive(tagToCheck);
		}
		else
		{
			return false;
		}
	}

	void TagObjectInfoReference::setTagList(TagList *newTagList)
	{
		tagList = newTagList;
	}

	void TagObjectInfoReference::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *)
	{
		if (blendRatio >= 0.5)
		{
			aObject->setObjectToLinear(bObject, t, this);
		}
	}
}