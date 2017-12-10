#ifndef	TEXTUREMAP_HPP
#define TEXTUREMAP_HPP

#include "TextureMapPoint.hpp"
#include <AssetManager/ObjectSaveMode.hpp>
#include <Core\String.hpp>
#include <map>
struct TextureMap
{
	inline TextureMapPoint& getTextureMapPoint(Core::String pointName)
	{
		return TexturePoints[pointName];
	}

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
			ar(var.second);
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
			ar(b);
			TexturePoints.insert(std::pair<std::string, TextureMapPoint>(a, b));
		}
		ar(mode);
		ar(modName);
	}
};
#endif