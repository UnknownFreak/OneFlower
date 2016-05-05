#ifndef	TEXTUREMAP_HPP
#define TEXTUREMAP_HPP

#include "../../Vector.h"
#include <SFML\Graphics\Sprite.hpp>
#include <map>
#include "../LoadAndSave/EditorObjectSaveMode.hpp"
#include "TextureMapPoint.hpp"
struct TextureMap
{
	TextureMapPoint& getTextureMapPoint(std::string pointName);
	std::map<std::string, TextureMapPoint> TexturePoints;

	std::string modName;
	EditorObjectSaveMode mode = EditorObjectSaveMode::ADD;

private:
	template<class Archive>
	friend void save(Archive& ar, const TextureMap& map);
	template<class Archive>
	friend void load(Archive& ar, TextureMap& map);
};
#endif