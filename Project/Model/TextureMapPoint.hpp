#ifndef TEXTUREMAPPOINT_HPP
#define TEXTUREMAPPOINT_HPP

#include <Core/Vector.h>
#include <SFML\Graphics\Color.hpp>
struct TextureMapPoint
{
	inline TextureMapPoint() : pos(0, 0), size(0, 0), rotated(false), color(255, 255, 255) {};
	Core::Vector2i pos;
	Core::Vector2i size;
	bool rotated;
	sf::Color color;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(pos);
		ar(size);
		ar(rotated);
		ar(color.r, color.g, color.b);
	}

	template <class Archive>
	void load(Archive& ar) 
	{
		ar(pos);
		ar(size);
		ar(rotated);
		ar(color.r, color.g, color.b);
	}

};

#endif