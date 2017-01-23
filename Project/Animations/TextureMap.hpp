#ifndef	TEXTUREMAP_HPP
#define TEXTUREMAP_HPP

#include "TextureMapPoint.hpp"
#include <AssetManager/ObjectSaveMode.hpp>
#include <map>
struct TextureMap
{
	TextureMapPoint& getTextureMapPoint(std::string pointName);
	std::map<std::string, TextureMapPoint> TexturePoints;

	std::string modName;
	ObjectSaveMode mode = ObjectSaveMode::ADD;

private:
	template<class Archive>
	friend void save(Archive& ar, const TextureMap& map);
	template<class Archive>
	friend void load(Archive& ar, TextureMap& map);
};
#endif