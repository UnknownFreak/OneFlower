#include "Tile.h"
#include "Gfx.h"
#include <string>
#include "Engine.hpp"
#include <SFML\Graphics.hpp>

/*
Tile::Tile()
{
name = "test.png";
spritesetTexture(*Engine::Graphic.requestTexture("test.png"));
//sprite.setOrigin(spritegetTextureRect().width / 2,spritegetTextureRect().height / 2);
sizeX = 0;
sizeY = 0;
}
//*/
Tile::Tile(std::string n,Vector2 pos): name(n),position(pos),size(0,0)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(n));
	sprite.setPosition(position.x,position.y);
}
Tile::Tile(std::string n,float x,float y) : name(n),position(x,y),size(0,0)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(n));
	sprite.setPosition(position.x,position.y);
}
Tile::Tile(const Tile &tile) : name(tile.name),position(tile.position),size(tile.size)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(name));
	sprite.setPosition(position.x,position.y);
}
Tile& Tile::operator=(const Tile &tile)
{
	name = tile.name;
	position = tile.position;
	size = tile.size;
	sprite.setTexture(*Engine::Graphic.requestTexture(name));
	sprite.setPosition(position.x,position.y);
	return *this;
}
void Tile::setRepeated(bool b)
{
	sf::Texture *tmp = (sf::Texture*)sprite.getTexture();
	tmp->setRepeated(b);
}
void Tile::setPosition(int x,int y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position.x,position.y);
}
void Tile::setPosition(float x,float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position.x,position.y);
}