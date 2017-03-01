#ifndef SPRITERMODELCONTAINER_HPP
#define SPRITERMODELCONTAINER_HPP

#include <map>
#include <Core\String.hpp>
#include "SpriterEngine\spriterengine.h"
#include "SpriterTextureMapper.hpp"
#include "SpriterEntityInstance.hpp"
#ifndef _EDITOR_
#include <future>
#endif
class GameObject;
class SpriterModelContainer
{
public:

	void setRenderWindow(sf::RenderWindow& renderWindow);

	SpriterModelContainer();
	~SpriterModelContainer();
	SpriterEntityInstance requestEntityInstance(Core::String SpriterSceneFile, Core::String SptiterEntityName);
#ifdef _EDITOR_

#else
	std::future<SpriterEntityInstance> requestEntityInstanceAsync(std::string SpriterSceneFile, std::string SptiterEntityName);
#endif
	SpriterTextureMapper* requestTextureMapper(Core::String textureMapper);
	std::map<Core::String, SpriterEngine::SpriterModel*> modelFiles;
	std::map<Core::String, SpriterTextureMapper*> modelTextureMapper;

	SpriterEngine::SpriterModel& getModel(Core::String modelName);
	std::vector<Core::String> getEntities(SpriterEngine::SpriterModel& model);
	std::map<std::pair<Core::String, Core::String>, TextureMap> getTextureMaps(Core::String modelFiles);

	std::map<Core::String, TextureMapPoint> getTextureMapPoints(Core::String modelname, Core::String modOrigin, Core::String textureMap);
	void addTextureMap(Core::String modelName, Core::String modOrigin, Core::String newTextureMap);
	void removeTextureMap(Core::String modelName, Core::String modOrigin, Core::String textureMapToRemove);

	void setTextureMapPoint(Core::String modelName, Core::String modOrigin, Core::String textureMap, Core::String pointName, TextureMapPoint point);

	void removeModel(Core::String modelName);
	void removeTextureMapper(Core::String modelName);

	std::vector<Core::String> getAnimationNames(Core::String modelName, Core::String entityName);
private:
	sf::RenderWindow* render;
	template<class Archive>
	friend void load(Archive&ar, SpriterModelContainer &SMC);
	template<class Archive>
	friend void save(Archive&ar, const SpriterModelContainer &SMC);
};

#endif