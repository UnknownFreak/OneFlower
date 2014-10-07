#ifndef WorldManagement_HPP
#define WorldManagement_HPP
#include <map>
#include "Zone.hpp"
class Zone;
class GameObject;
class WorldManagement
{
public:
	void loadZone (int zoneID);
	std::map <int,Zone> worldmap;
private:

	
};


#endif