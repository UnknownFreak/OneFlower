#ifndef	TEXTUREMAP_HPP
#define TEXTUREMAP_HPP

#include <map>

#include <Interfaces\IRequestable.hpp>
#include <Helpers/Enum/ObjectSaveMode.hpp>
#include <Helpers\String.hpp>

#include "TextureMapPoint.hpp"

struct TextureMap : public Interfaces::IRequestable
{
	TextureMapPoint& getTextureMapPoint(Core::String pointName);

	std::map<Core::String, TextureMapPoint> TexturePoints;
	Core::String name;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(fromMod, ID, mode, objectVersion);
		ar(name);
		ar(TexturePoints.size());
		for(std::pair<Core::String, TextureMapPoint> var : TexturePoints)
		{
			ar(var.first);
			ar(var.second);
		}
	}
	template <class Archive>
	void load(Archive& ar)
	{
		ar(fromMod, ID, mode, objectVersion);
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

	// Inherited via IRequestable
	virtual Interfaces::TypeInfo getTrait() const override;
};
#endif