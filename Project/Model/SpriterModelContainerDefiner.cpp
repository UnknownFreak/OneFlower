#include "SpriterModelContainer.hpp"
#include "SpriterOverride\SFMLObjectFactory.h"
#include "SpriterOverride\SFMLFileFactory.h"


ResourceType IEngineResource<SpriterModelContainer>::type = ResourceType::SpriterContainer;

SpriterEntityInstance SpriterModelContainer::requestEntityInstance(Core::String sceneFile, Core::String entityName)
{
	if (modelFiles.find(sceneFile) != modelFiles.end())
	{
		SpriterEngine::EntityInstance* instance = modelFiles[sceneFile]->getNewEntityInstance(entityName);
		SpriterEntityInstance sinstance(instance, requestTextureMapper(sceneFile));
		sinstance.entityName = entityName;
		sinstance.sceneFile = sceneFile;
		return sinstance;
	}
	else
	{
		modelFiles.insert(std::pair<Core::String, SpriterEngine::SpriterModel*>(
			sceneFile,
			new SpriterEngine::SpriterModel(
				sceneFile,
				new SpriterEngine::SFMLFileFactory(requestTextureMapper(sceneFile)),
				new SpriterEngine::SFMLObjectFactory(requestTextureMapper(sceneFile)))));
	}
	SpriterEngine::EntityInstance* instance = modelFiles[sceneFile]->getNewEntityInstance(entityName);
	SpriterEntityInstance sinstance(instance, requestTextureMapper(sceneFile));
	sinstance.entityName = entityName;
	sinstance.sceneFile = sceneFile;
	return sinstance;
}

#ifdef _EDITOR_
#else
std::future<SpriterEntityInstance> SpriterModelContainer::requestEntityInstanceAsync(std::string SpriterSceneFile, std::string SptiterEntityName)
{
	return std::async(std::launch::async, [this](std::string scenefile, std::string entityName) -> SpriterEntityInstance {return requestEntityInstance(scenefile, entityName); },SpriterSceneFile, SptiterEntityName);
}
#endif

SpriterTextureMapper* SpriterModelContainer::requestTextureMapper(Core::String sceneFile)
{
	if (modelTextureMapper.find(sceneFile) != modelTextureMapper.end())
	{
		return modelTextureMapper[sceneFile];
	}
	else
	{
		modelTextureMapper.insert(std::pair<Core::String, SpriterTextureMapper*>(sceneFile, new SpriterTextureMapper(*render)));
	}
	return modelTextureMapper[sceneFile];
}

SpriterModelContainer::SpriterModelContainer()
{
}

void SpriterModelContainer::setRenderWindow(sf::RenderWindow & renderWindow)
{
	render = &renderWindow;
}

SpriterModelContainer::~SpriterModelContainer()
{
	clearLists();
}
std::vector<Core::String> SpriterModelContainer::getEntities(SpriterEngine::SpriterModel& model)
{
	return model.getEntityNames();
}
SpriterEngine::SpriterModel& SpriterModelContainer::getModel(Core::String fileName)
{
	if (modelFiles.find(fileName) != modelFiles.end())
	{
		return *modelFiles[fileName];
	}
	else
	{
		modelFiles.insert(std::pair<Core::String, SpriterEngine::SpriterModel*>(
			fileName,
			new SpriterEngine::SpriterModel(
				fileName,
				new SpriterEngine::SFMLFileFactory(requestTextureMapper(fileName)),
				new SpriterEngine::SFMLObjectFactory(requestTextureMapper(fileName)))));
	}
	return *modelFiles[fileName];
}

void SpriterModelContainer::removeModel(Core::String modelName)
{
	std::map<Core::String, SpriterEngine::SpriterModel*>::iterator it = modelFiles.find(modelName);
	if (it != modelFiles.end())
	{
		delete it->second;
		modelFiles.erase(it);
	}
	removeTextureMapper(modelName);
}
void SpriterModelContainer::removeTextureMapper(Core::String modelName)
{
	//AddField with editorsavemode instead of remove, and flag it for delete (so that it can be undo)
	std::map<Core::String, SpriterTextureMapper*>::iterator it = modelTextureMapper.find(modelName);
	if (it != modelTextureMapper.end())
	{
		delete it->second;
		modelTextureMapper.erase(it);
	}
}
std::map<std::pair<Core::String, Core::String>, TextureMap> SpriterModelContainer::getTextureMaps(Core::String modelName)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		return modelTextureMapper[modelName]->textureMaps;
	else
		getModel(modelName);
	return modelTextureMapper[modelName]->textureMaps;
}
std::map<Core::String, TextureMapPoint> SpriterModelContainer::getTextureMapPoints(Core::String modelName, Core::String modOrigin, Core::String textureMap)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
	{
		if (modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMap }) != modelTextureMapper[modelName]->textureMaps.end())
			return modelTextureMapper[modelName]->textureMaps[{ modOrigin, textureMap }].TexturePoints;
	}
	return std::map<Core::String, TextureMapPoint>();
}
void SpriterModelContainer::addTextureMap(Core::String modelName, Core::String modOrigin, Core::String newTextureMap)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		if (modelTextureMapper[modelName]->textureMaps.find(std::pair<Core::String, Core::String>(modOrigin, newTextureMap)) == modelTextureMapper[modelName]->textureMaps.end())
		{
			modelTextureMapper[modelName]->textureMaps.insert(std::pair<std::pair<Core::String, Core::String>, TextureMap>({ modOrigin, newTextureMap }, TextureMap(modelTextureMapper[modelName]->textureMaps[{ "DEFAULT", "Default" }])));
			modelTextureMapper[modelName]->textureMaps[{ modOrigin, newTextureMap }].modName = modOrigin;
		}
}
void SpriterModelContainer::removeTextureMap(Core::String modelName, Core::String modOrigin, Core::String textureMapToRemove)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		if (modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMapToRemove }) != modelTextureMapper[modelName]->textureMaps.end())
			modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMapToRemove })->second.mode = ObjectSaveMode::REMOVE;
}

void SpriterModelContainer::setTextureMapPoint(Core::String modelName, Core::String modOrigin, Core::String textureMap, Core::String pointName, TextureMapPoint point)
{
	modelTextureMapper[modelName]->textureMaps.at({ modOrigin, textureMap }).TexturePoints[pointName] = point;
	modelTextureMapper[modelName]->textureMaps.at({ modOrigin, textureMap }).mode = ObjectSaveMode::EDIT;
}
std::vector<Core::String> SpriterModelContainer::getAnimationNames(Core::String modelName, Core::String entityName)
{
	std::vector<Core::String> animations;

	SpriterEntityInstance inst = requestEntityInstance(modelName, entityName);
	int animationCount = inst.MyEntityInstance->animationCount();
	for (int i = 0; i < animationCount; i++)
	{
		inst.MyEntityInstance->setCurrentAnimation(i);
		animations.push_back(inst.MyEntityInstance->currentAnimationName());
	}
	return animations;
}

void SpriterModelContainer::clearLists()
{
	for each (std::pair<Core::String, SpriterEngine::SpriterModel*> var in modelFiles)
	{
		delete var.second;
	}
	modelFiles.clear();
	for each (std::pair<Core::String, SpriterTextureMapper*> var in modelTextureMapper)
	{
		delete var.second;
	}
	modelTextureMapper.clear();
}

const ResourceType & SpriterModelContainer::getType()
{
	return type;
}
