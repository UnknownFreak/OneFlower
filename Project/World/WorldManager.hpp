#ifndef WorldManager_HPP
#define WorldManager_HPP
#include <map>
#include <AssetManager\Database\DBZone.hpp>
#include <AssetManager\Mod\ModLoader.hpp>
#include <AssetManager\Mod\ModHeader.hpp>
#include <AssetManager\Database\DatabaseIndex.hpp>
#include <AssetManager\Prefab\Prefab.hpp>
#include <AssetManager\Requestor\Reference.hpp>

//#include "../../Game/LoadAndSave/PrefabContainer.hpp"
//#include "../../Game/GUI/Window/Addon/ProgressBar.hpp"
//#include "../../Game/Animations/SpriterModelContainer.hpp"

class Zone;
class GameObject;
class WorldManager
{
#ifdef _EDITOR_
	friend class WorldManagerAddon;
#endif
	enum Loadstate {
		STATE_NOT_SET,
		STATE_REQUEST_DBZONE,
		STATE_UNREQUEST_DBZONE,
		STATE_PREPARE_LOAD,
		STATE_UNLOAD_OBJECTS,
		STATE_RELOAD_OBJECTS,
		STATE_DONE,
		STATE_ERR_LOADING,
	};
public:

#ifdef _DEBUG
	//Probably move this to editor
	// std::map<std::pair<Core::String, size_t>, DBZone> EditorAllZones;
#endif
	//to be able to remove gameobjects when unloading;
	std::map<std::pair<Core::String, size_t>, GameObject*> listOfZoneObjects;

	std::pair<Core::String, size_t> lastLoadedZone;

	std::map <std::pair<Core::String, size_t>, Zone*> worldmap;

	Zone* getCurrentZone();

	WorldManager();
	~WorldManager();

	void loadZone(Core::String addedFromMod, size_t zoneID);
	const bool getIsLoading() const;

	const Loadstate getCurrentLoadingState() const;

	void drawLoadingScreen();
	void loadSome();
private:
#ifdef _EDITOR_
	void addMainMenu();
	void unload();
#endif

	void prepareLoad();
	void unloadObjects();
	void reloadObjects();
	void requestZoneToLoad();
	void unrequestZoneToLoad();

	void startLoad();

	Loadstate loadState = STATE_NOT_SET;

	bool isLoading = false;
	std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::iterator currentObjIterator;
	std::map<std::pair<Core::String, size_t>, GameObject*>::iterator currentObjIteratorUnload;

	size_t currentObj = 0;
	size_t totalLoaded = 0;
	size_t totalToLoad = 0;
	std::pair<Core::String, size_t> zoneToLoadID;

	Zone* currentZone;
	DBZone zoneToLoad;
	Reference<DBZone>* refZoneToLoad;

};
#endif