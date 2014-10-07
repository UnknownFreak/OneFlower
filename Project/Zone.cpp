#include "Zone.hpp"


Zone::Zone(std::string n,unsigned int i, std::vector<Tile> tiles, std::vector<GameObject> ob)
{
	//Name of the zone created
	name = n;
	//Unique id for the zone created
	ID = i;
	//adds the tiles from Tiles vector
	for (int i = 0; i < tiles.size(); i++)
		backgrounds.push_back(tiles[i]);
	//add the gameobjects from GameObject vector
	for (int i = 0; i < ob.size(); i++)
		objects.push_back(ob[i]);

}
Zone::Zone()
{

}
