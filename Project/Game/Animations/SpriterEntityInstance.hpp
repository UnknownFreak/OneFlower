#ifndef SPRITERENTITYINSTANCE_HPP
#define	SPRITERENTITYINSTANCE_HPP

#include "SpriterEngine\spriterengine.h"
#include "SpriterTextureMapper.hpp"
struct SpriterEntityInstance
{
	SpriterEntityInstance();
	SpriterEntityInstance(SpriterEngine::EntityInstance* myEntity, SpriterTextureMapper* textureMap);
	SpriterEngine::EntityInstance* MyEntityInstance = NULL;
	SpriterTextureMapper* textureMaps = NULL;

	std::pair<std::string, std::string> myTextureMap;
	std::string sceneFile;
	std::string entityName;

	void render(sf::Sprite* sprite);

private:

	template<class Archive>
	friend void save(Archive& ar, const SpriterEntityInstance& inst);
	template<class Archive>
	friend void load(Archive& ar, SpriterEntityInstance& inst);


};

#endif