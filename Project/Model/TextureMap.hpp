#ifndef	TEXTUREMAP_HPP
#define TEXTUREMAP_HPP

#include <map>

#include <Asset\IRequestable.hpp>
#include <Asset\ObjectSaveMode.hpp>
#include <Core\String.hpp>

#include "TextureMapPoint.hpp"

struct TextureMap : public IRequestable
{
	inline TextureMapPoint& getTextureMapPoint(Core::String pointName)
	{
		return TexturePoints[pointName];
	}

	std::map<Core::String, TextureMapPoint> TexturePoints;
	Core::String name;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(name);
		ar(TexturePoints.size());
		for each (std::pair<Core::String, TextureMapPoint> var in TexturePoints)
		{
			ar(var.first);
			ar(var.second);
		}
	}
	template <class Archive>
	void load(Archive& ar)
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(name);
		size_t size;
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			Core::String a;
			TextureMapPoint b;
			ar(a);
			ar(b);
			TexturePoints.insert(std::pair<Core::String, TextureMapPoint>(a, b));
		}
	}
};
#endif