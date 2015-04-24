#ifndef WorldManagement_HPP
#define WorldManagement_HPP
#include <map>

class Zone;
class GameObject;
class WorldManagement
{
public:
	Zone *zone;
	unsigned int lastLoadedZone;
	WorldManagement();
	~WorldManagement();
	void loadZone(unsigned int zoneID);
	std::map <unsigned int,Zone*> worldmap;
	std::map <unsigned int,std::string>zoneInfo;

	Zone* getCurrentZone();
#ifdef _DEBUG
	void EditorAddNewZone(std::string zoneName,unsigned int ID);
	void EditorLoadZone(std::string zoneName,unsigned int ID);
	void EditorRemoveZone();
	void EditorSaveZone();
	void EditorSetBackground(std::string textureName);
	void EditorSetBackgroundSize(int x, int y);
#endif
private:

	Zone* currentZone;

	// loads a zone from a specified file
	friend bool loadZoneFile(std::string fileName,Zone &z);
	friend bool loadZoneInfo(std::map<unsigned int,std::string> & zoneInfo);
	friend void saveInfo(std::map<unsigned int,Zone>map);
	void worldFromZone(unsigned int zoneID);
};
#endif