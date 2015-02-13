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
	//Tile();

	// name input for texture, and coordinates for the position
	Tile(std::string n = "test.png",Vector2 pos = Vector2(0,0));
	// name input for texture, and x, y pos for position
	Tile(std::string n,float x =0.f, float y=0.f);
	Tile(const Tile &tile);

	//position of the tile
	Vector2 position;
	//the sprite that the tile uses
	sf::Sprite sprite;
	// the name of the texture
	std::string name;
	// for repeated texture
	int sizeX;
	int sizeY;

	Tile& operator=(const Tile &tile);
	void setRepeated(bool b);
	void setPosition(int x, int y);
	void setPosition(float x, float y);
private:
	// save function for the tile
	template<class Archive>
	friend void save(Archive &ar, const Tile& t);
	// load function for the tile
	template<class Archive>
	friend void load(Archive &ar, Tile &t);
};



#endif