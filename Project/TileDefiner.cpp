#include "Tile.h"
#include "Gfx.h"
#include <string>

Tile::Tile()
{
	name = "test.png";
	sprite.setTexture(*SetGfx()->requestTexture("test.png"));
//	sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
}
Tile::Tile(Vector2<int> pos)
{
	name = "test.png";
	sprite.setTexture(*SetGfx()->requestTexture("test.png"));
	//sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
	position = pos;
}
Tile::Tile(int x,int y)
{
	name = "test.png";
	sprite.setTexture(*SetGfx()->requestTexture("test.png"));
	//sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);

	position.x = x;
	position.y = y;
}
Tile::Tile(std::string n)
{
	name = n;
	sprite.setTexture(*SetGfx()->requestTexture(n));
	//	sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
}
Tile::Tile(std::string n, Vector2<int> pos)
{
	name = n;
	sprite.setTexture(*SetGfx()->requestTexture(n));
	//sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
	position = pos;
}
Tile::Tile(std::string n, int x, int y)
{
	name = n;
	sprite.setTexture(*SetGfx()->requestTexture(n));
	//sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);

	position.x = x;
	position.y = y;
}
