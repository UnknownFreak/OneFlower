#ifndef SFMLObjectFactory_H
#define SFMLObjectFactory_H

#include "../spriterengine/override/objectfactory.h"

namespace SpriterEngine
{
	class SFMLObjectFactory : public ObjectFactory
	{
	public:
		SFMLObjectFactory();

		PointInstanceInfo *newPointInstanceInfo() override;

		BoxInstanceInfo *newBoxInstanceInfo(point size) override;

		BoneInstanceInfo *newBoneInstanceInfo(point size) override;

	private:
	};
}

#endif // SFMLObjectFactory_H
