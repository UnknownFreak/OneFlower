#include "ZoneMaker.hpp"
void ZoneMap::setBackground(Tile &t)
{
	background = t;
}
void ZoneMap::addGameObject(GameObject* go)
{
	objects.push_back(go);
}
ZoneMap::ZoneMap()
{
	name = "";
	ID = 1;
}

void ZoneMap::readForegroundsVector(std::vector<Tile> tiles)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		foregrounds.push_back(tiles[i]);
	}
}