#ifndef TEXTURE_MAP_ADDON_HPP
#define TEXTURE_MAP_ADDON_HPP
#include <Model\AnimationCore.hpp>

#ifdef _EDITOR_

class SpriterModelContainerAddon
{
	friend class SpriterModelContainer;

	SpriterModelContainer& myActualContainer;

public:
	SpriterModelContainerAddon();



	void addTextureMap(Core::String modelName, Core::String modOrigin, Core::String newTextureMap);
	void removeTextureMap(Core::String modelName, Core::String modOrigin, Core::String textureMapToRemove);


};

#endif
#endif
