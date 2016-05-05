#ifndef SFMLObjectFactory_H
#define SFMLObjectFactory_H

#include "../spriterengine/override/objectfactory.h"

#include "../SpriterTextureMapper.hpp"

namespace SpriterEngine
{

	class SFMLObjectFactory : public ObjectFactory
	{
	public:
		SFMLObjectFactory(SpriterTextureMapper *textureMapper);
		
		PointInstanceInfo *newPointInstanceInfo() override;

		BoxInstanceInfo *newBoxInstanceInfo(point size) override;

		BoneInstanceInfo *newBoneInstanceInfo(point size) override;

	private:
		SpriterTextureMapper *textureMapper;
	};

}

#endif // SFMLObjectFactory_H
