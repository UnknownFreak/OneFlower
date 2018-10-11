#include "SpriterInstanceContainer.hpp"

#include <SpriterPlusPlus/SpriterOverride\SFMLObjectFactory.h>
#include <SpriterPlusPlus/SpriterOverride\SFMLFileFactory.h>

#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Asset\AssetManagerCore.hpp>


ResourceType IEngineResource<SpriterInstanceContainer>::type = ResourceType::SpriterContainer;

SpriterInstanceContainer::SpriterInstanceContainer() : modelFiles()
{
}

SpriterInstanceContainer::~SpriterInstanceContainer()
{
	Requestor<TextureMap>& requestor = Engine::GetModule<Asset::AssetManager>().getTextureMapRequester();
	std::map<std::pair<Core::String, std::pair<Core::String, size_t>>, SpriterEngine::SpriterModel*>::iterator it = modelFiles.begin();
	std::map<std::pair<Core::String, std::pair<Core::String, size_t>>, SpriterEngine::SpriterModel*>::iterator eit = modelFiles.end();

	for (; it != eit; it++)
	{
		delete it->second;
		requestor.requestRemoval(it->first.second.first, it->first.second.second);
	}
}

SpriterEngine::EntityInstance* SpriterInstanceContainer::requestModel(Core::String _modelFile, Core::String _modelName, std::pair<Core::String, size_t> _textureMapId, SpriteRef*& sprite)
{
	key _key = { _modelFile, _textureMapId };

	std::map<std::pair<Core::String, std::pair<Core::String, size_t>>, SpriterEngine::SpriterModel*>::iterator it = modelFiles.find(_key);
	

	if (it != modelFiles.end())
	{
		return it->second->getNewEntityInstance(_modelName, sprite);
	}
	else
	{
		TextureMap& r = Engine::GetModule<Asset::AssetManager>().getTextureMapRequester().request(_textureMapId.first, _textureMapId.second);

		modelFiles.insert(std::pair<std::pair<Core::String, std::pair<Core::String, size_t>>, SpriterEngine::SpriterModel*>(
			_key,
			new SpriterEngine::SpriterModel(
				"Spriter/" + _modelFile,
				new SpriterEngine::SFMLFileFactory(&r),
				new SpriterEngine::SFMLObjectFactory(), ref)));

		return modelFiles[{_modelFile, _textureMapId}]->getNewEntityInstance(_modelName, sprite);

	}
	return nullptr;
}

const ResourceType & SpriterInstanceContainer::getType()
{
	return type;
}
