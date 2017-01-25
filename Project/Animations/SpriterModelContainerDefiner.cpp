#include "SpriterModelContainer.hpp"
#include "SpriterOverride\SFMLObjectFactory.h"
#include "SpriterOverride\SFMLFileFactory.h"

SpriterEntityInstance SpriterModelContainer::requestEntityInstance(std::string sceneFile, std::string entityName)
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
		modelFiles.insert(std::pair<std::string, SpriterEngine::SpriterModel*>(
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

SpriterTextureMapper* SpriterModelContainer::requestTextureMapper(std::string sceneFile)
{
	if (modelTextureMapper.find(sceneFile) != modelTextureMapper.end())
	{
		return modelTextureMapper[sceneFile];
	}
	else
	{
		modelTextureMapper.insert(std::pair<std::string, SpriterTextureMapper*>(sceneFile, new SpriterTextureMapper(render)));
	}
	return modelTextureMapper[sceneFile];
}

SpriterModelContainer::SpriterModelContainer(sf::RenderWindow & renderWindow) :render(renderWindow)
{
}

SpriterModelContainer::~SpriterModelContainer()
{
	for each (std::pair<std::string, SpriterEngine::SpriterModel*> var in modelFiles)
	{
		delete var.second;
	}
	modelFiles.clear();
	for each (std::pair<std::string, SpriterTextureMapper*> var in modelTextureMapper)
	{
		delete var.second;
	}
	modelTextureMapper.clear();
}
std::vector<std::string> SpriterModelContainer::getEntities(SpriterEngine::SpriterModel& model)
{
	return model.getEntityNames();
}
SpriterEngine::SpriterModel& SpriterModelContainer::getModel(std::string fileName)
{
	if (modelFiles.find(fileName) != modelFiles.end())
	{
		return *modelFiles[fileName];
	}
	else
	{
		modelFiles.insert(std::pair<std::string, SpriterEngine::SpriterModel*>(
			fileName,
			new SpriterEngine::SpriterModel(
				fileName,
				new SpriterEngine::SFMLFileFactory(requestTextureMapper(fileName)),
				new SpriterEngine::SFMLObjectFactory(requestTextureMapper(fileName)))));
	}
	return *modelFiles[fileName];
}

void SpriterModelContainer::removeModel(std::string modelName)
{
	std::map<std::string, SpriterEngine::SpriterModel*>::iterator it = modelFiles.find(modelName);
	if (it != modelFiles.end())
	{
		delete it->second;
		modelFiles.erase(it);
	}
	removeTextureMapper(modelName);
}
void SpriterModelContainer::removeTextureMapper(std::string modelName)
{
	//AddField with editorsavemode instead of remove, and flag it for delete (so that it can be undo)
	std::map<std::string, SpriterTextureMapper*>::iterator it = modelTextureMapper.find(modelName);
	if (it != modelTextureMapper.end())
	{
		delete it->second;
		modelTextureMapper.erase(it);
	}
}
std::map<std::pair<std::string, std::string>, TextureMap> SpriterModelContainer::getTextureMaps(std::string modelName)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		return modelTextureMapper[modelName]->textureMaps;
	else
		getModel(modelName);
	return modelTextureMapper[modelName]->textureMaps;
}
std::map<std::string, TextureMapPoint> SpriterModelContainer::getTextureMapPoints(std::string modelName, std::string modOrigin, std::string textureMap)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
	{
		if (modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMap }) != modelTextureMapper[modelName]->textureMaps.end())
			return modelTextureMapper[modelName]->textureMaps[{ modOrigin, textureMap }].TexturePoints;
	}
	return std::map<std::string, TextureMapPoint>();
}
void SpriterModelContainer::addTextureMap(std::string modelName, std::string modOrigin, std::string newTextureMap)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		if (modelTextureMapper[modelName]->textureMaps.find(std::pair<std::string, std::string>(modOrigin, newTextureMap)) == modelTextureMapper[modelName]->textureMaps.end())
		{
			modelTextureMapper[modelName]->textureMaps.insert(std::pair<std::pair<std::string, std::string>, TextureMap>({ modOrigin, newTextureMap }, TextureMap(modelTextureMapper[modelName]->textureMaps[{ "DEFAULT", "Default" }])));
			modelTextureMapper[modelName]->textureMaps[{ modOrigin, newTextureMap }].modName = modOrigin;
		}
}
void SpriterModelContainer::removeTextureMap(std::string modelName, std::string modOrigin, std::string textureMapToRemove)
{
	if (modelTextureMapper.find(modelName) != modelTextureMapper.end())
		if (modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMapToRemove }) != modelTextureMapper[modelName]->textureMaps.end())
			modelTextureMapper[modelName]->textureMaps.find({ modOrigin, textureMapToRemove })->second.mode = ObjectSaveMode::REMOVE;
}

void SpriterModelContainer::setTextureMapPoint(std::string modelName, std::string modOrigin, std::string textureMap, std::string pointName, TextureMapPoint point)
{
	modelTextureMapper[modelName]->textureMaps.at({ modOrigin, textureMap }).TexturePoints[pointName] = point;
	modelTextureMapper[modelName]->textureMaps.at({ modOrigin, textureMap }).mode = ObjectSaveMode::EDIT;
}
std::vector<std::string> SpriterModelContainer::getAnimationNames(std::string modelName, std::string entityName)
{
	std::vector<std::string> animations;

	SpriterEntityInstance inst = requestEntityInstance(modelName, entityName);
	int animationCount = inst.MyEntityInstance->animationCount();
	for (int i = 0; i < animationCount; i++)
	{
		inst.MyEntityInstance->setCurrentAnimation(i);
		animations.push_back(inst.MyEntityInstance->currentAnimationName());
	}
	return animations;
}