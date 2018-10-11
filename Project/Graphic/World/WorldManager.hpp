#ifndef WorldManager_HPP
#define WorldManager_HPP
#include <map>
#include <Asset/Database/DatabaseObjects.hpp>
#include <Asset/Prefab.hpp>
#include <Asset/Reference.hpp>
#include <Core/EngineModule/IEngineModule.hpp>

#include "Chunk.hpp"

class Zone;
class GameObject;
class WorldManager : public IEngineResource<WorldManager>
{
#ifdef _EDITOR_
	friend class WorldManagerAddon;
#endif
#ifdef _UNITTESTS_
public:
#endif

	enum Loadstate {
		NOT_SET,

		CHECK_IF_LOADED,

		SWAP_WITH_LOADED,
		LOAD_FROM_FILE,
		
		LOAD_OBJECTS,
		INITIALIZE_CHUNKS,
		BUILD_CHUNKS,
		PLACE_TILES,
		POPULATE_CHUNKS,
		UNLOAD_OBJECTS,
		DONE,
		ERR_LOADING,

	};
public:

	const ResourceType& getType()
	{
		return type;
	}

	//to be able to remove gameobjects when unloading;
	std::map<std::pair<Core::String, size_t>, GameObject*> listOfZoneObjects;

	std::pair<Core::String, size_t> lastLoadedZone;

	std::map <std::pair<Core::String, size_t>, Zone> worldmap;

	Zone& getCurrentZone();

	WorldManager();
	~WorldManager();

	void loadZone(Core::String addedFromMod, size_t zoneID);
	const bool isLoading() const;

	const Loadstate getCurrentLoadingState() const;

	void drawLoadingScreen();
	void loadSome();
private:
#ifdef _EDITOR_
	void unload();
#endif

	void checkIfLoaded();
	
	void swapWithLoaded();
	void loadFromFile();
	
	void loadObjects();
	void initializeChunks();
	void buildChunks();
	void placeTiles();
	void populateChunks();
	void unloadObjects();


	void prepareLoad();
//	void unloadObjects();
	void reloadObjects();
	void requestZoneToLoad();
	void unrequestZoneToLoad();

	void startLoad();

	Loadstate loadState = NOT_SET;

	bool _isLoading = false;
	//std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::iterator currentObjIterator;
	std::vector<Chunk>::iterator zoneChunkIterator;
	std::vector<Database::Chunk>::iterator databaseChunkIterator;

	size_t current_chunk = 0;

	std::vector<std::pair<Core::String, size_t>>::iterator prefabIdIterator;

	std::map<std::pair<Core::String, size_t>, Asset::Prefab> loadedPrefabs;
	std::map<std::pair<Core::String, size_t>, GameObject*>::iterator currentObjIteratorUnload;

	size_t currentObj = 0;
	size_t totalLoaded = 0;
	size_t totalToLoad = 0;
	std::pair<Core::String, size_t> zoneToLoadID;

	Zone* currentZone;
	//DBZone zoneToLoad;
	Database::Zone* refZoneToLoad;

};
#endif