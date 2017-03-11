#ifndef WorldManager_HPP
#define WorldManager_HPP
#include <map>
#include <AssetManager\Database\DBZone.hpp>
#include <AssetManager\Mod\ModLoader.hpp>
#include <AssetManager\Mod\ModHeader.hpp>
#include <AssetManager\Database\DatabaseIndex.hpp>
#include <AssetManager\Prefab\Prefab.hpp>
#include <AssetManager\Prefab\PrefabContainer.hpp>

//#include "../../Game/LoadAndSave/PrefabContainer.hpp"
//#include "../../Game/GUI/Window/Addon/ProgressBar.hpp"
//#include "../../Game/Animations/SpriterModelContainer.hpp"
class Zone;
class GameObject;
class WorldManager
{
	friend class WorldManagerAddon;
	enum Loadstate {
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
	std::map<std::pair<Core::String, unsigned int>, DBZone> EditorAllZones;
	//std::map<std::pair<std::string, size_t>, Items::Item*> EditorAllItems;
	//std::map<std::pair<std::string, unsigned int>, Quests::Quest> EditorAllQuests;
#endif
	//to be able to remove gameobjects when unloading;
	std::map<std::pair<Core::String, size_t>, GameObject*> listOfZoneObjects;
	ModLoader modLoadOrder;

	std::pair<Core::String, unsigned int> lastLoadedZone;

	std::map <std::pair<Core::String, unsigned int>, Zone*> worldmap;
	Zone* getCurrentZone();

	WorldManager();
	~WorldManager();

	void loadZone(Core::String addedFromMod, unsigned int zoneID);
	bool getIsLoading();

	Loadstate getCurrentLoadingState();

	ModHeader myModHeader;
#ifdef _DEBUG

	//
	//
	//std::string getLoadedMod();
	//
	//std::vector<std::string> getModDependencies(std::string mod);
	//void newMod(std::string modName, std::vector<std::string> dependencies);
	//std::vector<std::string> loadMod(std::string modName);
	//std::string loadMods(std::string modName);
	//void EditorAddNewZone(std::string zoneName, std::string background, std::string loadingScreen, std::string loadingScreenMessage, size_t ID, double x, double y);
	//void EditorEditZone(std::string zoneName, std::string background, std::string loadingScreen, std::string loadingScreenMessage, size_t ID, double x, double y);
	//void EditorLoadZone(std::string zoneName, unsigned int ID);
	//void EditorRemoveZone();
	//std::string EditorSave();
	//void EditorSetBackground(std::string textureName);
	//void EditorSetBackgroundSize(int x, int y);
	//std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct> EditorAddGameObjectToZone(Prefab& prefab, GameObject* go);
	//void RemoveGameObjectFromZone(GameObject* go);
	//
	//void EditorFlagGameObjectForEdit(GameObject* go);
	//
	////void AddQuest(Quests::Quest quest);
	////void AddItem(Items::Item* item);
	//
	//friend void LoadAllZones(std::map<std::pair<std::string, unsigned int>, DBZone>& nameOfAllZones);
	//friend void LoadAllPrefabs(PrefabContainer& editorPrefabContainer);
	//friend void LoadAllTextureMaps(SpriterModelContainer& container);
	//size_t EditorGetValidID();
	//size_t ID = 1;
#endif

	void drawLoadingScreen();
	void loadSome();
private:

	void addMainMenu();

	void unload();

	void prepareLoad();
	void unloadObjects();
	void reloadObjects();

	//void LoadAllEditorVariables();

	void startLoad();

	Loadstate loadState = STATE_NOT_SET;
	bool isLoading = false;
	std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::iterator currentObjIterator;
	std::map<std::pair<Core::String, size_t>, GameObject*>::iterator currentObjIteratorUnload;

	size_t currentObj = 0;
	size_t totalLoaded = 0;
	size_t totalToLoad = 0;
	std::pair<Core::String, size_t> zoneToLoadID;

	//friend bool loadZoneFromSaveFile(std::string saveFile, Zone& zoneToLoad, size_t zoneID);
	//friend void loadZoneFromDB(DBZone& zoneToLoad, size_t zoneID);
	Zone* currentZone;
	DBZone zoneToLoad;
	// loads a zone from a specified file
	//friend bool loadModOrderFile(ModLoader &mod);
	//friend void loadZoneFile(std::string fileName, const DatabaseIndex& index, DBZone &z);
	//friend bool loadPrefab(std::string fromMod, unsigned int index, Prefab& prefab);
	//friend void loadPrefab(std::string modName, Prefab& prefab, const DatabaseIndex &index);
	//friend DatabaseIndex loadIndex(std::string modname, size_t objectID, std::string loadType);
};
#endif