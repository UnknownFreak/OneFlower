#include "ZoneMaker.hpp"
void ZoneMap::setBackground(Tile &t)
{
	background = t;
}
void ZoneMap::addGameObject(GameObject& go)
{
	objects.push_back(go);
}
ZoneMap::ZoneMap()
{
	name = "";
	ID = 1;
}