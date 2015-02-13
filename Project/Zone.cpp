#include "Zone.hpp"
#include <string>

int Zone::getID()
{
	return ID;
}
std::string Zone::getName() 
{
	return name;
}
Tile Zone::getBackground() 
{
	return background;
}
void Zone::addForeground(Tile fg) 
{
	foregrounds.push_back(fg);
}
Zone::Zone(std::string n,unsigned int i, Tile bg,std::vector<Tile> tiles,std::vector<GameObject*> ob)
{
	//Name of the zone created
	name = n;
	//Unique id for the zone created
	ID = i;
	//adds a background
	background = bg;
	//add the foregrounds from tiles vector
	for (int i = 0; i < tiles.size(); i++)
		foregrounds.push_back(tiles[i]);
	//add the gameobjects from GameObject vector
	for (int i = 0; i < ob.size(); i++) {
	//	GameObject go = ob[i];
		objects.push_back(ob[i]);
	}
}
// Copy constructor
Zone::Zone(Zone &z)
{
	ID = z.ID;
	name = z.name;
	background = z.background;
	for (int i = 0; i < z.foregrounds.size(); i++)
		foregrounds.push_back(z.foregrounds[i]);
	for (int i = 0; i < z.objects.size(); i++)
		this->objects.push_back(z.objects[i]);
}
//default constructor
Zone::Zone()
{
	name = "";
	ID = 0;
}
// deconstructor
Zone::~Zone()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects[i] = nullptr;
	}
	objects.empty();
	foregrounds.empty();
}
// operator =
Zone& Zone::operator=(const Zone &z) 
{

	this->name = z.name;
	this->ID = z.ID;
	background = z.background;
	for (int i = 0; i < z.foregrounds.size(); i++)
		this->foregrounds.push_back(z.foregrounds[i]);
	for (int i = 0; i < z.objects.size(); i++)
		this->objects.push_back(z.objects[i]);

	return *this;
}

std::vector<Tile> Zone::getForegrounds()
{
	return foregrounds;
}