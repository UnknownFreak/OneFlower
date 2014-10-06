#ifndef WorldManagement_HPP
#define WorldManagement_HPP
#include <map>

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