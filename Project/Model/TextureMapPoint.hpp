#ifndef TEXTUREMAPPOINT_HPP
#define TEXTUREMAPPOINT_HPP

#include <Core/Vector.h>
#include <SFML\Graphics\Color.hpp>
struct TextureMapPoint
{
	TextureMapPoint();
	Core::Vector2i pos;
	Core::Vector2i size;
	bool rotated;
	sf::Color color;
};

#endif