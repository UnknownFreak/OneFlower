#ifdef _EDITOR_
#ifndef _UNITTESTS_
#include "TextureMapAddon.hpp"
#include <Core\IEngineResource\EngineResourceManager.hpp>

SpriterModelContainerAddon::SpriterModelContainerAddon() : myActualContainer(Engine::Get<SpriterModelContainer>())
{
}

void SpriterModelContainerAddon::addTextureMap(Core::String modelName, Core::String modOrigin, Core::String newTextureMap)
{
	std::map<Core::String, SpriterTextureMapper*>& modelTextureMapper = myActualContainer.modelTextureMapper;
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		if (modelTextureMapper[modelName]->textureMaps.find(std::pair<Core::String, Core::String>(modOrigin, newTextureMap)) == modelTextureMapper[modelName]->textureMaps.end())
		{
			modelTextureMapper[modelName]->textureMaps.insert(std::pair<std::pair<Core::String, Core::String>, TextureMap>({ modOrigin, newTextureMap }, TextureMap(modelTextureMapper[modelName]->textureMaps[{ "DEFAULT", "Default" }])));
			modelTextureMapper[modelName]->textureMaps[{ modOrigin, newTextureMap }].modName = modOrigin;
		}
}

void SpriterModelContainerAddon::removeTextureMap(Core::String modelName, Core::String modOrigin, Core::String textureMapToRemove)
{
	std::map<Core::String, SpriterTextureMapper*>& modelTextureMapper = myActualContainer.modelTextureMapper;
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		if (modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMapToRemove }) != modelTextureMapper[modelName]->textureMaps.end())
			modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMapToRemove })->second.mode = ObjectSaveMode::REMOVE;
}

#endif
#endif