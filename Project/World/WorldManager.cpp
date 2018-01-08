#include "WorldManager.hpp"
#include "Zone.hpp"

#include <AssetManager\AssetManagerCore.hpp>

#include <Graphic\GraphicsCore.hpp>

ResourceType IEngineResource<WorldManager>::type = ResourceType::WorldManager;

WorldManager::WorldManager() : lastLoadedZone("", 0), currentZone(0), refZoneToLoad(nullptr)
{
#ifdef _EDITOR_
	addMainMenu();
#endif

	if (Engine::Get<AssetManager>().loadModOrderFile() == false)
	{
		Engine::Get<AssetManager>().getModLoader().loadOrder.insert(std::pair<Core::String, size_t>("OneFlower", 1));
		Engine::Get<AssetManager>().saveModOrderFile();
	}
}
// deconstructor
WorldManager::~WorldManager()
{
	//remove loaded zones
	for (std::map<std::pair<Core::String, size_t>, Zone*>::iterator it = worldmap.begin(); it != worldmap.end(); it++)
	{	// if a zone have been unloaded/deleted already
		for (size_t j = 0; j < it->second->objects.size(); j++)
		{
			// request removal of GameObjects /to fix
			//Engine::game.requestRemoveal(it->second->objects[j].second);
			it->second->objects[j].second = nullptr;
		}
		delete it->second;
	}
}

// load zone with ID
void WorldManager::loadZone(Core::String addedFromMod, size_t zoneID)
{

	zoneToLoadID = std::pair<Core::String, size_t>(addedFromMod, zoneID);
	startLoad();

//	if (worldmap.find(std::pair<Core::String, size_t>(addedFromMod, zoneID)) != worldmap.end())
//	{
//		//Core::String info = "Zone structure with ID: [" + addedFromMod + ", " + std::to_string(zoneID) + "] is already loaded into memory.\nContinues to load zone...";
//		// load the Zone with the zone id
//		// loadZoneFromMap(zoneID);
//		//std::cout << info;
//		zoneToLoadID = std::pair<Core::String, size_t>(addedFromMod, zoneID);
//		startLoad();
//	}
//	else
//	{
//#ifdef _EDITOR_
//		// TODO: Use this instead of the EditorAllZones, we no longer load the asset here anymore, we request it from the asset manager
//		// The object is then held there and we get a reference towards that object, when we are done, we should request removal of that object
//		// to reduce our reference counter and unload it after x min if none else requests the same entry
//		// the probability that DBzones are requested from more than one location is low.
//		Reference<DBZone>*& dbzone = Engine::getDBZoneRequester().request(addedFromMod, zoneID);
//		if (dbzone->isValid())
//		{
//			DBZone& refzone = dbzone->getReferenced();
//			zoneToLoadID = std::pair<std::string, size_t>(addedFromMod, zoneID);
//			worldmap.insert(std::pair<std::pair<Core::String, size_t>, Zone*>(zoneToLoadID, new Zone(refzone)));
//			startLoad();
//		}
//		Engine::getDBZoneRequester().requestRemoval(addedFromMod, zoneID);
//
//		//std::map<std::pair<std::string, size_t>, DBZone>::iterator it = EditorAllZones.find(std::pair<std::string, size_t>(addedFromMod, zoneID));
//		//if (it != EditorAllZones.end())
//		//{
//		//	//std::cout << "From Mod " << addedFromMod << " ID " << zoneID << std::endl;
//		//	worldmap.insert(std::pair<std::pair<std::string, size_t>, Zone*>(std::pair<std::string, size_t>(addedFromMod, zoneID), new Zone(it->second)));
//		//	zoneToLoadID = std::pair<std::string, size_t>(addedFromMod, zoneID);
//		//	startLoad();
//		//}
//#else
//
//		AssetManagerCore::loadZoneFromDB(zoneToLoad, zoneID);
//		Zone* zoneToAdd = new Zone();
//		if (AssetManagerCore::loadZoneFromSaveFile("Data\\"+addedFromMod, *zoneToAdd, zoneID))
//		{
//			if (zoneToLoad.prefabList.size() == zoneToAdd->objects.size() + zoneToAdd->rc.respawnTable.size())
//			{
//				worldmap.insert(std::pair<std::pair<Core::String, size_t>, Zone*>(std::pair<Core::String, size_t>(addedFromMod, zoneID), zoneToAdd));
//			}
//			else
//			{
//				//reload zone cause it's not the same anymore
//			}
//		}
//		else
//		{
//			delete zoneToAdd;
//			worldmap.insert(std::pair<std::pair<Core::String, size_t>, Zone*>(std::pair<Core::String, size_t>(addedFromMod, zoneID), new Zone(zoneToLoad)));
//			zoneToLoadID = std::pair<Core::String, size_t>(addedFromMod, zoneID);
//			startLoad();
//		}
//#endif
//	}
}

Zone* WorldManager::getCurrentZone()
{
	return currentZone;
}
const bool WorldManager::getIsLoading() const
{
	return isLoading;
}
void WorldManager::drawLoadingScreen()
{
	if (currentZone)
	{
		Engine::Get<Gfx>().DrawLoadingScreen(*currentZone->getLoadingScreen(), currentZone->getLoadingScreenMessage());
	}
}
#ifdef _EDITOR_
void WorldManager::addMainMenu()
{

	DBZone dbz;
	dbz.fromMod = "MainMenu";
	dbz.background.size.x = 256;
	dbz.background.name = "TestBackground.png";
	dbz.loadingScreen.name = "TestBackground.png";
	dbz.ID = 0;
	dbz.name = "MainMenu";
	Engine::Get<AssetManager>().getDBZoneRequester().add(dbz);

}
#endif

const WorldManager::Loadstate WorldManager::getCurrentLoadingState() const
{
	return loadState;
}

