#ifndef WorldManagement_HPP
#define WorldManagement_HPP
#include <map>
#include "ModLoader.hpp"
#include "../LoadAndSave/PrefabContainer.hpp"
#include "../LoadAndSave/DatabaseIndex.hpp"
#include "../GUI/Window/Addon/ProgressBar.hpp"
#include "DBZone.hpp"
class Zone;
class GameObject;
class WorldManagement
{
	enum loadstate {
		STATE_NOT_SET,
		STATE_PREPARE_LOAD,
		STATE_UNLOAD_OBJECTS,
		STATE_RELOAD_OBJECTS,
		STATE_DONE,
	};
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

	
	std::map <unsigned int,Zone*> worldmap;
	Zone* getCurrentZone();
	GUI::Window::Addon::ProgressBar& getLoadingScreenProgressBar();


	WorldManagement();
	~WorldManagement();

	void loadZone(unsigned int zoneID);
	bool getIsLoading();

	int getCurrentLoadingState();

#ifdef _DEBUG
	void EditorAddNewZone(std::string zoneName,unsigned int ID);
	void EditorLoadZone(std::string zoneName,unsigned int ID);
	void EditorRemoveZone();
	void EditorSaveZones();
	void EditorSetBackground(std::string textureName);
	void EditorSetBackgroundSize(int x,int y);
	void EditorAddGameObjectToZone(Prefab& prefab,GameObject* go);
	void RemoveGameObjectFromZone(GameObject* go);

	friend void LoadAllZones(std::map<unsigned int, DBZone>& nameOfAllZones);
	friend void LoadAllPrefabs(PrefabContainer& editorPrefabContainer);

#endif

	void drawLoadingScreen();
	void loadSome();
private:

	GUI::Window::Addon::ProgressBar loadingScreenProgress;

	void startLoad();

	int loadState = STATE_NOT_SET;
	bool isLoading = false;
	size_t currentObj = 0;
	size_t totalLoaded = 0;
	size_t totalToLoad = 0;
	size_t zoneToLoadID = 0;

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