#ifndef Tile_H
#define Tile_H
#include <Windows.h>
#include "Vector.h"
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include <cereal\access.hpp>
class Tile
{
public:
	Tile();
	// default texture
	Tile(Vector2<int> pos);
	//default texture
	Tile(int x,int y);
	//default position with a custom texture
	Tile(std::string n);
	// name input for texture, and coordinates for the position
	Tile(std::string n,Vector2<int> pos);
	// name input for texture, and x, y pos for position
	Tile(std::string n,int x, int y);
	//position of the tile
	Vector2<int> position;
	//the sprite that the tile uses
	sf::Sprite sprite;
	// the name of the texture
	std::string name;
	
private:
	// save function for the tile
	template<class Archive>
	friend void save(Archive &ar, const Tile& t);
	// load function for the tile
	template<class Archive>
	friend void load(Archive &ar, Tile &t);
};



#endif