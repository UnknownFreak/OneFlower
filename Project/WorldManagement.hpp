#ifndef WorldManagement_HPP
#define WorldManagement_HPP
#include <map>

class ZoneMap;
class GameObject;
class WorldManagement
{
public:
	void loadZone (int zoneID);
	std::map <int,ZoneMap> worldmap;
private:

	
};


#endif