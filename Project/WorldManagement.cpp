#include "WorldManagement.hpp"
#include "Zone.hpp"
#include <string>
#include <fstream>
#include "cereal\cereal.hpp"
#include "LoadAndSave.hpp"
void WorldManagement::loadZone(unsigned int zoneID)
{
	if(worldmap.find(zoneID) != worldmap.end())
	{
		// load the Zone with the zone id
		// loadZoneFromMap(zoneID);
	}
	else
	{
		Zone zone;
		std::string name = zoneInfo.find(zoneID)->second;
		loadZoneFile(name,zone);
		worldmap.insert(std::pair<unsigned int, Zone>(zone.ID, zone));
	}
}
WorldManagement::WorldManagement() {
	loadZoneInfo(zoneInfo);
}