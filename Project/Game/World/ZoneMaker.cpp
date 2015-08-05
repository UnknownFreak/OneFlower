#include "ZoneMaker.hpp"

ZoneMap::ZoneMap(): name(""),ID(1)
{
}

void ZoneMap::setBackground(Tile &t)
{
	background = t;
}
void ZoneMap::addGameObject(GameObject* go)
{
	objects.push_back(go);
}

void ZoneMap::readForegroundsVector(std::vector<Tile> tiles)
{
	for(size_t i = 0; i < tiles.size(); i++)
	{
		foregrounds.push_back(tiles[i]);
	}
}

void ZoneMap::setID(unsigned int _ID)
{
	ID = _ID;
}