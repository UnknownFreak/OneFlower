#include "SpriterInstanceContainer.hpp"

#include <Graphics/Spriter/SpriterOverride\SFMLObjectFactory.h>
#include <Graphics/Spriter/SpriterOverride\SFMLFileFactory.h>

#include <Module\EngineModuleManager.hpp>
#include <File/AssetManagerCore.hpp>


Enums::EngineResourceType Interfaces::IEngineResource<SpriterInstanceContainer>::type = Enums::EngineResourceType::SpriterContainer;

SpriterInstanceContainer::SpriterInstanceContainer() : modelFiles()
{
}

SpriterInstanceContainer::~SpriterInstanceContainer()
{
	auto requestorv2 = Engine::GetModule<Asset::AssetManager>().requestor;
	std::map<std::pair<Core::String, std::pair<Core::String, Core::uuid>>, SpriterEngine::SpriterModel*>::iterator it = modelFiles.begin();
	std::map<std::pair<Core::String, std::pair<Core::String, Core::uuid>>, SpriterEngine::SpriterModel*>::iterator eit = modelFiles.end();

	for (; it != eit; it++)
	{
		delete it->second;
		requestorv2.requestRemoval(it->first.second.first, it->first.second.second);
	}
}

SpriterEngine::EntityInstance* SpriterInstanceContainer::requestModel(Core::String _modelFile, Core::String _modelName, std::pair<Core::String, Core::uuid> _textureMapId, std::shared_ptr<sf::Sprite>& sprite)
{
	key _key = { _modelFile, _textureMapId };

	std::map<std::pair<Core::String, std::pair<Core::String, Core::uuid>>, SpriterEngine::SpriterModel*>::iterator it = modelFiles.find(_key);

	if (it != modelFiles.end())
	{
		return it->second->getNewEntityInstance(_modelName, sprite);
	}
	else
	{
		TextureMap r = Engine::GetModule<Asset::AssetManager>().requestor.requestUniqueInstance<TextureMap>({ _textureMapId.first, _textureMapId.second });

		modelFiles.insert(std::pair<std::pair<Core::String, std::pair<Core::String, Core::uuid>>, SpriterEngine::SpriterModel*>(
			_key,
			new SpriterEngine::SpriterModel(
				"Spriter/" + _modelFile,
				new SpriterEngine::SFMLFileFactory(&r),
				new SpriterEngine::SFMLObjectFactory(), ref)));

		return modelFiles[{_modelFile, _textureMapId}]->getNewEntityInstance(_modelName, sprite);

	}
	return nullptr;
}

Enums::EngineResourceType& SpriterInstanceContainer::getType() const
{
	return type;
}
