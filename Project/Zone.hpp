#ifndef ZONE_HPP
#define ZONE_HPP
#include <string>
#include <vector>
#include "Tile.h"
#include "Component\GameObject.h"
class Zone
{
private:
	//template load function
	template<class Archive>
	friend void load(Archive&ar, Zone &zone);
public:
	// name of the zone
	std::string name;
	// unique id for each zone
	int id;
	// vector containing tiles (backgrounds)
	std::vector<Tile> backgrounds;
	// vector containing objects (gameobjects)
	std::vector<GameObject> objects;

	//constructor
	Zone(std::string name,int id, std::vector<Tile>, std::vector<GameObject>);
	Zone();
	
};

#endif ZONE_HPP