#ifndef WorldManager_HPP
#define WorldManager_HPP
#include <map>
#include <Core\IEngineResource\IEngineResource.hpp>

#include <AssetManager\Database\DBZone.hpp>
#include <AssetManager\Requestor\Reference.hpp>


class Zone;
class GameObject;
class WorldManager : public IEngineResource<WorldManager>
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


	const ResourceType& getType()
	{
		return type;
	}

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