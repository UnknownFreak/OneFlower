#ifndef SPRITERMODELCONTAINER_HPP
#define SPRITERMODELCONTAINER_HPP

#include <map>
#include "SpriterEngine\spriterengine.h"
#include "SpriterTextureMapper.hpp"
#include "SpriterEntityInstance.hpp"
#include <future>
class GameObject;
class SpriterModelContainer
{
public:
	SpriterModelContainer(sf::RenderWindow& renderWindow);
	~SpriterModelContainer();
	SpriterEntityInstance requestEntityInstance(std::string SpriterSceneFile, std::string SptiterEntityName);
	std::future<SpriterEntityInstance> requestEntityInstanceAsync(std::string SpriterSceneFile, std::string SptiterEntityName);
	SpriterTextureMapper* requestTextureMapper(std::string textureMapper);
	std::map<std::string, SpriterEngine::SpriterModel*> modelFiles;
	std::map<std::string, SpriterTextureMapper*> modelTextureMapper;

	SpriterEngine::SpriterModel& getModel(std::string modelName);
	std::vector<std::string> getEntities(SpriterEngine::SpriterModel& model);
	std::map<std::pair<std::string, std::string>, TextureMap> getTextureMaps(std::string modelFiles);

	std::map<std::string, TextureMapPoint> getTextureMapPoints(std::string modelname, std::string modOrigin, std::string textureMap);
	void addTextureMap(std::string modelName, std::string modOrigin, std::string newTextureMap);
	void removeTextureMap(std::string modelName, std::string modOrigin, std::string textureMapToRemove);

	void setTextureMapPoint(std::string modelName, std::string modOrigin, std::string textureMap, std::string pointName, TextureMapPoint point);

	void removeModel(std::string modelName);
	void removeTextureMapper(std::string modelName);

	std::vector<std::string> getAnimationNames(std::string modelName, std::string entityName);
private:
	sf::RenderWindow& render;
	template<class Archive>
	friend void load(Archive&ar, SpriterModelContainer &SMC);
	template<class Archive>
	friend void save(Archive&ar, const SpriterModelContainer &SMC);
};

#endif