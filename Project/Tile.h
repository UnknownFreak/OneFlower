#ifndef Tile_H
#define Tile_H
#include <Windows.h>
#include "Vector.h"
#include <SFML\Graphics\Sprite.hpp>
#include <string>
class Tile
{
public:
	Tile();
	Tile(Vector2<int> pos);
	Tile(int x,int y);
	Tile(std::string n);
	Tile(std::string n,Vector2<int> pos);
	Tile(std::string n,int x, int y);
	Vector2<int> position;
	sf::Sprite sprite;
};



#endif