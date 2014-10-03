#ifndef Tile_H
#define Tile_H
#include "Vector.h"
#include <SFML\Graphics\Sprite.hpp>

class Tile
{
public:
	Tile();
	Tile(Vector2<int> pos);
	Tile(int x,int y);
	Vector2<int> position;
	sf::Sprite sprite;

};



#endif