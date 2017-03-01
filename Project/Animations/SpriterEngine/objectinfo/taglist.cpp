#include "taglist.h"

namespace SpriterEngine
{
	TagList::TagList()
	{
	}

	bool TagList::tagIsActive(Core::String tag) const
	{
		for (auto& it : tags)
		{
			if (*it == tag)
			{
				return true;
			}
		}
		return false;
	}

	void TagList::pushBackTag(const Core::String * tag)
	{
		tags.push_back(tag);
	}
}