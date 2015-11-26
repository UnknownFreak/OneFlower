#ifndef WorldManagement_HPP
#define WorldManagement_HPP
#include <map>
#include "ModLoader.hpp"
#include "../LoadAndSave/PrefabContainer.hpp"
#include "../LoadAndSave/DatabaseIndex.hpp"
#include "DBZone.hpp"
class Zone;
class GameObject;
class WorldManagement
{
public:

#ifdef _DEBUG
	//Probably move this to editor
	PrefabContainer editorPrefabContainer;
	std::map<unsigned int, DBZone> EditorAllZones;
	//std::vector<std::pair<size_t, Vector2&>> prefabListEditorReference;
#endif
	//to be able to remove gameobjects when unloading;
	std::vector<GameObject*> listOfZoneObjects;
	ModLoader modLoadOrder;

	unsigned int lastLoadedZone;
	WorldManagement();
	~WorldManagement();
	void loadZone(unsigned int zoneID);
	std::map <unsigned int,Zone*> worldmap;

	Zone* getCurrentZone();
#ifdef _DEBUG
	void EditorAddNewZone(std::string zoneName,unsigned int ID);
	void EditorLoadZone(std::string zoneName,unsigned int ID);
	void EditorRemoveZone();
	void EditorSaveZone();
	void EditorSetBackground(std::string textureName);
	void EditorSetBackgroundSize(int x,int y);

	void RemoveGameObjectFromZone(GameObject* go);

	friend void LoadAllZones(std::map<unsigned int, DBZone>& nameOfAllZones);
	friend void LoadAllPrefabs(PrefabContainer& editorPrefabContainer);

#endif
private:

	friend bool loadZoneFromSaveFile(std::string saveFile, Zone& zoneToLoad, size_t zoneID);
	friend void loadZoneFromDB(DBZone& zoneToLoad, size_t zoneID);
	Zone* currentZone;

	// loads a zone from a specified file
	friend bool loadModOrderFile(ModLoader &mod);
	friend void loadZoneFile(std::string fileName, const DatabaseIndex& index,DBZone &z);
	void worldFromZone(unsigned int zoneID);
	friend void loadPrefab(std::string modName, Prefab& prefab, const DatabaseIndex &index);
	friend DatabaseIndex loadIndex(std::string modname, size_t objectID, std::string loadType);
};
#endif