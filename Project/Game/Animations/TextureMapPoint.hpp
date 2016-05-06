#ifndef TEXTUREMAPPOINT_HPP
#define TEXTUREMAPPOINT_HPP

#include "../../Vector.h"
#include <SFML\Graphics\Color.hpp>
struct TextureMapPoint
{
	TextureMapPoint();
	Vector2i pos;
	Vector2i size;
	bool rotated;;
	sf::Color color;
};

#endif