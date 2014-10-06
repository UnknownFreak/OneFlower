#include "Tile.h"
#include "Gfx.h"
#include <string>


Tile::Tile()
{
	sprite.setTexture(*SetGfx()->requestTexture("test.png"));
//	sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
}
Tile::Tile(Vector2<int> pos)
{
	sprite.setTexture(*SetGfx()->requestTexture("test.png"));
	//sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
	position = pos;
}
Tile::Tile(int x,int y)
{
	sprite.setTexture(*SetGfx()->requestTexture("test.png"));
	//prite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);

	position.x = x;
	position.y = y;
}
Tile::Tile(std::string name)
{
	sprite.setTexture(*SetGfx()->requestTexture(name));
	//	sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
}
Tile::Tile(std::string name, Vector2<int> pos)
{
	sprite.setTexture(*SetGfx()->requestTexture(name));
	//sprite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);
	position = pos;
}
Tile::Tile(std::string name, int x, int y)
{
	sprite.setTexture(*SetGfx()->requestTexture(name));
	//prite.setOrigin(sprite.getTextureRect().width / 2,sprite.getTextureRect().height / 2);

	position.x = x;
	position.y = y;
}