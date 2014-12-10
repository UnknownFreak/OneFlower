#ifndef ZONE_HPP
#define ZONE_HPP
#include <string>
#include <vector>
#include "Tile.h"
class GameObject;
class Zone
{
private:

	// Background image for the zone
	Tile background;
	
	// Name of the zone
	std::string name;

	// Unique id for each zone
	unsigned int ID;

	//Load function
	template<class Archive>
	friend void load(Archive&ar, Zone &zone);
public:
	
	

	// Vector containing tiles (backgrounds)
	std::vector<Tile> foregrounds;

	// Vector containing objects (gameobjects)
	std::vector<GameObject*> objects;
	// Gets the background image
	Tile getBackground();

	// Gets the name of the zone
	std::string getName();

	// Add a foreground image
	void addForeground(Tile sprite);

	//Get the ID for the zone
	int getID();

	//constructor
	Zone(std::string name, unsigned int ID, Tile background, std::vector<Tile>tiles, std::vector<GameObject*>objects);
	Zone();
	Zone(Zone &zone);
	~Zone();
	Zone& operator=(const Zone &z);
};

#endif ZONE_HPP