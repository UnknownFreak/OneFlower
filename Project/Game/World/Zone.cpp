#include "Zone.hpp"
#include <string>
#include "../../Engine.hpp"

Zone::Zone(std::string n,unsigned int i,Tile bg,std::vector<Tile> tiles,std::vector<GameObject*> ob):
name(n),ID(i),background(bg)
{
	//add the foregrounds from tiles vector
	for(size_t i = 0; i < tiles.size(); i++)
		foregrounds.push_back(tiles[i]);
	//add the gameobjects from GameObject vector
	for(size_t i = 0; i < ob.size(); i++)
	{
		//	GameObject go = ob[i];
		objects.push_back(ob[i]);
	}
}
// Copy constructor
Zone::Zone(Zone &z):
name(z.name),ID(z.ID),background(z.background)
{
	for(size_t i = 0; i < z.foregrounds.size(); i++)
		foregrounds.push_back(z.foregrounds[i]);
	for(size_t i = 0; i < z.objects.size(); i++)
		this->objects.push_back(z.objects[i]);
}
//default constructor
Zone::Zone():
name(""),ID(0)
{
}
// deconstructor
Zone::~Zone()
{
	for(size_t i = 0; i < objects.size(); i++)
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
	name = z.name;
	ID = z.ID;
	background = z.background;
	for(size_t i = 0; i < z.foregrounds.size(); i++)
		foregrounds.push_back(z.foregrounds[i]);
	for(size_t i = 0; i < z.objects.size(); i++)
		objects.push_back(z.objects[i]);

	return *this;
}

std::vector<Tile> Zone::getForegrounds()
{
	return foregrounds;
}

int Zone::getID()
{
	return ID;
}
std::string Zone::getName()
{
	return name;
}
Tile* Zone::getBackground()
{
	return &background;
}
void Zone::addForeground(Tile fg)
{
	foregrounds.push_back(fg);
}

#ifdef _DEBUG

void Zone::setBackground(std::string name)
{
	background.name = name;
	background.sprite.setTexture(*Engine::Graphic.requestTexture(name));
}

#endif