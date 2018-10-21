#include "tagobjectinfo.h"

namespace SpriterEngine
{
	TagObjectInfo::TagObjectInfo()
	{
	}

	void TagObjectInfo::setObjectToLinear(UniversalObjectInterface *, real , UniversalObjectInterface *resultObject)
	{
		resultObject->setTagList(&tagList);
	}

	void TagObjectInfo::pushBackTag(const Core::String * tag)
	{
		tagList.pushBackTag(tag);
	}
}