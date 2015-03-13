#ifndef WorldManagement_HPP
#define WorldManagement_HPP
#include <map>
#include <cereal\access.hpp>

class Zone;
class GameObject;
class WorldManagement
{
public:
	Zone *zone;
	unsigned int lastLoadedZone;
	WorldManagement();
	~WorldManagement();
	void loadZone (unsigned int zoneID);
	std::map <unsigned int,Zone*> worldmap;
	std::map <unsigned int, std::string>zoneInfo;
private:
	// loads a zone from a specified file
	friend bool loadZoneFile(std::string fileName, Zone &z);
	friend bool loadZoneInfo(std::map<unsigned int, std::string> & zoneInfo);
	friend void saveInfo(std::map<unsigned int, Zone>map);
	void worldFromZone(unsigned int zoneID);
	
};
#endif