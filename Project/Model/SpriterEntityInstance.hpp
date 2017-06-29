#ifndef SPRITERENTITYINSTANCE_HPP
#define	SPRITERENTITYINSTANCE_HPP

#include "SpriterEngine\spriterengine.h"
#include "SpriterTextureMapper.hpp"
struct SpriterEntityInstance
{
	SpriterEntityInstance();
	SpriterEntityInstance(const SpriterEntityInstance&copy);
	SpriterEntityInstance(SpriterEngine::EntityInstance* myEntity, SpriterTextureMapper* textureMap);
	~SpriterEntityInstance();
	SpriterEntityInstance& operator=(const SpriterEntityInstance& right);
	SpriterEngine::EntityInstance* MyEntityInstance = NULL;
	SpriterTextureMapper* textureMaps = NULL;

	std::pair<Core::String, std::string> myTextureMap;
	Core::String sceneFile;
	Core::String entityName;

	void render(SpriteRef* sprite);

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(entityName);
		ar(sceneFile);
		ar(myTextureMap.first);
		ar(myTextureMap.second);
	}
	template<class Archive>
	void load(Archive& ar)
	{
		ar(entityName);
		ar(sceneFile);
		ar(myTextureMap.first);
		ar(myTextureMap.second);
	}
};

#endif