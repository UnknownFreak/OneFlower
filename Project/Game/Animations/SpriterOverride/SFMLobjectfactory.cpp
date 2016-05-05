#include "SFMLObjectFactory.h"

#include "sfmlpointinstanceinfo.h"
#include "sfmlboxinstanceinfo.h"
#include "sfmlboneinstanceinfo.h"
#include "sfmlsoundobjectinforeference.h"

namespace SpriterEngine
{

	SFMLObjectFactory::SFMLObjectFactory(SpriterTextureMapper *validTextureMapper) :
		textureMapper(validTextureMapper)
	{
	}

	PointInstanceInfo * SFMLObjectFactory::newPointInstanceInfo()
	{
		return new SfmlPointInstanceInfo(textureMapper->renderWindow);
	}

	BoxInstanceInfo * SFMLObjectFactory::newBoxInstanceInfo(point size)
	{
		return new SfmlBoxInstanceInfo(size, textureMapper->renderWindow);
	}

	BoneInstanceInfo * SFMLObjectFactory::newBoneInstanceInfo(point size)
	{
		return new SfmlBoneInstanceInfo(size, textureMapper->renderWindow);
	}

}