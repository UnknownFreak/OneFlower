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

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(TexturePoints.size());
		for each (std::pair<std::string, TextureMapPoint> var in TexturePoints)
		{
			ar(var.first);
			ar(var.second.pos.x);
			ar(var.second.pos.y);
			ar(var.second.size.x);
			ar(var.second.size.y);
			ar(var.second.rotated);
			ar(var.second.color.r);
			ar(var.second.color.g);
			ar(var.second.color.b);
		}
		ar(mode);
		ar(modName);
	}
	template <class Archive>
	void load(Archive& ar)
	{
		size_t size;
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			std::string a;
			TextureMapPoint b;
			ar(a);
			ar(b.pos.x);
			ar(b.pos.y);
			ar(b.size.x);
			ar(b.size.y);
			ar(b.rotated);
			ar(b.color.r);
			ar(b.color.g);
			ar(b.color.b);
			TexturePoints.insert(std::pair<std::string, TextureMapPoint>(a, b));
		}
		ar(mode);
		ar(modName);
	}
};
#endif