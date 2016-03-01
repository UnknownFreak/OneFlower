#ifndef ZONE_HPP
#define ZONE_HPP
#include <string>
#include <vector>
#include "../Tile.h"
#include "../LoadAndSave/Prefab.hpp"
#include "RespawnContainer.hpp"
class GameObject;
class DBZone;
class Zone
{
private:
#ifdef _DEBUG
public:
#endif
	// Background image for the zone
	Tile background;
	// Name of the zone
	std::string name;
	// Unique id for each zone
	unsigned int ID;

	Tile loadScreen;
	std::string loadingScreenMessage = "";

protected:
	//Load function
	template<class Archive>
	friend void load(Archive&ar,Zone &zone);
//#ifdef _DEBUG
	template<class Archive>
	friend void save(Archive&ar, const Zone &zone);
//#endif
public:

	RespawnContainer rc;
	
	std::string modOrigin;

	//std::vector<std::pair<size_t,Vector2>> prefabList;
	// Vector containing tiles (backgrounds)
	std::vector<Tile> foregrounds;

	// Vector containing pair <prefabid, object(gameobjects)> 
	std::vector<std::pair<std::pair<std::string,size_t>,GameObject*>> objects;
	// Gets the background image
	Tile* getBackground();

	Tile* getLoadingScreen();
	std::string& getLoadingScreenMessage();

	// Gets the name of the zone
	std::string getName();

	// Add a foreground image
	void addForeground(Tile sprite);

	//Get the ID for the zone
	int getID();

	std::vector<Tile> getForegrounds();

	//constructor
	Zone(std::string name,unsigned int ID,Tile background,std::vector<Tile>tiles,std::vector<GameObject*>objects);
	Zone();
	Zone(DBZone& zone);
	Zone(Zone &zone);
	~Zone();
	Zone& operator=(const Zone &z);

#ifdef _DEBUG
	void setBackground(std::string name);
#endif
};

#endif ZONE_HPP