#include "SFMLObjectFactory.h"

#include "sfmlpointinstanceinfo.h"
#include "sfmlboxinstanceinfo.h"
#include "sfmlboneinstanceinfo.h"
#include "sfmlsoundobjectinforeference.h"

namespace SpriterEngine
{
	SFMLObjectFactory::SFMLObjectFactory()
	{
	}

	PointInstanceInfo * SFMLObjectFactory::newPointInstanceInfo()
	{
		return new SfmlPointInstanceInfo();
	}

	BoxInstanceInfo * SFMLObjectFactory::newBoxInstanceInfo(point size)
	{
		return new SfmlBoxInstanceInfo(size);
	}

	BoneInstanceInfo * SFMLObjectFactory::newBoneInstanceInfo(point size)
	{
		return new SfmlBoneInstanceInfo(size);
	}
}