#ifndef TEXTUREMAPPOINT_HPP
#define TEXTUREMAPPOINT_HPP

#include "../../Vector.h"
#include <SFML\Graphics\Color.hpp>
struct TextureMapPoint
{
	TextureMapPoint();
	Vector2 pos;
	Vector2 size;
	bool rotated;;
	sf::Color color;
};

#endif