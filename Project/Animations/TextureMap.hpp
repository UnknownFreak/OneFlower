#ifndef	TEXTUREMAP_HPP
#define TEXTUREMAP_HPP

#include "TextureMapPoint.hpp"
#include <AssetManager/ObjectSaveMode.hpp>
#include <Core\String.hpp>
#include <map>
struct TextureMap
{
	TextureMapPoint& getTextureMapPoint(Core::String pointName);
	std::map<Core::String, TextureMapPoint> TexturePoints;

	Core::String modName;
	ObjectSaveMode mode = ObjectSaveMode::ADD;

private:
	template<class Archive>
	friend void save(Archive& ar, const TextureMap& map);
	template<class Archive>
	friend void load(Archive& ar, TextureMap& map);
};
#endif