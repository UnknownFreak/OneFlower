#include "WorldManager.hpp"
#include "Zone.hpp"
#include <string>
#include <Graphic\GraphicsCore.hpp>
#include <Core/Component/GameObject.h>
#include <Core/Component/TransformComponent.hpp>
#include <AssetManager\AssetManagerCore.hpp>

WorldManager::WorldManager() : lastLoadedZone("", 0), currentZone(0), modLoadOrder()
{
	worldmap.insert({ { "MainMenu", 0 }, new Zone("MainMenu", 0, BackgroundSprite("TestBackground.png",0,0), {}, {}) });
	worldmap[{"MainMenu", 0}]->modOrigin = "MainMenu";
	worldmap[{"MainMenu", 0}]->background.size.x = 256;
	worldmap[{"MainMenu", 0}]->background.setRepeated(true);
	worldmap[{"MainMenu", 0}]->loadScreen = worldmap[{"MainMenu", 0}]->background;

#ifdef _DEBUG
	//EditorAddNewZone("Tutorial", "test.png", "test.png", "Tutorial Zone", 1, 1000, 800);
#endif

	//testSave();
	if (AssetManagerCore::loadModOrderFile(modLoadOrder) == false)
	{
		//MessageBox(Engine::Window.hWnd, "Error loading ModLoadOrder, Using default", "Error", NULL);
		modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>("OneFlower", 1));
	}
}
// deconstructor
WorldManager::~WorldManager()
{
	//remove loaded zones
	for (std::map<std::pair<std::string, size_t>, Zone*>::iterator it = worldmap.begin(); it != worldmap.end(); it++)
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
void WorldManager::loadZone(std::string addedFromMod, unsigned int zoneID)
{
	if (worldmap.find(std::pair<std::string, size_t>(addedFromMod, zoneID)) != worldmap.end())
	{
		std::string info = "Zone structure with ID: [" + addedFromMod + ", " + std::to_string(zoneID) + "] is already loaded into memory.\nContinues to load zone...";
		// load the Zone with the zone id
		// loadZoneFromMap(zoneID);
		//std::cout << info;
		zoneToLoadID = std::pair<std::string, size_t>(addedFromMod, zoneID);
		startLoad();
	}
	else
	{
#ifdef _EDITOR
		std::map<std::pair<std::string, size_t>, DBZone>::iterator it = EditorAllZones.find(std::pair<std::string, size_t>(addedFromMod, zoneID));
		if (it != EditorAllZones.end())
		{
			//std::cout << "From Mod " << addedFromMod << " ID " << zoneID << std::endl;
			worldmap.insert(std::pair<std::pair<std::string, size_t>, Zone*>(std::pair<std::string, size_t>(addedFromMod, zoneID), new Zone(it->second)));
			zoneToLoadID = std::pair<std::string, size_t>(addedFromMod, zoneID);
			startLoad();
		}
#else

		AssetManagerCore::loadZoneFromDB(zoneToLoad, zoneID);
		Zone* zoneToAdd = new Zone();
		if (AssetManagerCore::loadZoneFromSaveFile("Data\\"+addedFromMod, *zoneToAdd, zoneID))
		{
			if (zoneToLoad.prefabList.size() == zoneToAdd->objects.size() + zoneToAdd->rc.respawnTable.size())
			{
				worldmap.insert(std::pair<std::pair<std::string, size_t>, Zone*>(std::pair<std::string, size_t>(addedFromMod, zoneID), zoneToAdd));
			}
			else
			{
				//reload zone cause it's not the same anymore
			}
		}
		else
		{
			delete zoneToAdd;
			worldmap.insert(std::pair<std::pair<std::string, size_t>, Zone*>(std::pair<std::string, size_t>(addedFromMod, zoneID), new Zone(zoneToLoad)));
			zoneToLoadID = std::pair<std::string, size_t>(addedFromMod, zoneID);
			startLoad();
		}
#endif
	}
}

Zone* WorldManager::getCurrentZone()
{
	return currentZone;
}
//GUI::Window::Addon::ProgressBar& WorldManager::getLoadingScreenProgressBar()
//{
//	return loadingScreenProgress;
//}
bool WorldManager::getIsLoading()
{
	return isLoading;
}
WorldManager::loadstate WorldManager::getCurrentLoadingState()
{
	return loadState;
}
void WorldManager::drawLoadingScreen()
{
	if (currentZone)
	{
		Engine::Graphic.DrawLoadingScreen(*currentZone->getLoadingScreen(), currentZone->getLoadingScreenMessage());
	}
}
void WorldManager::loadSome()
{
	switch (loadState)
	{
	case STATE_NOT_SET:
		break;
	case STATE_PREPARE_LOAD:
#ifdef _EDITOR
		if (lastLoadedZone.second != 0)
		{
			totalToLoad = EditorAllZones[lastLoadedZone].prefabList.size();
			currentObjIterator = EditorAllZones[lastLoadedZone].prefabList.begin();
		}
		currentObjIteratorUnload = listOfZoneObjects.begin();
		totalToLoad += EditorAllZones[zoneToLoadID].prefabList.size();
#else
		totalToLoad = listOfZoneObjects.size();
		currentObjIteratorUnload = listOfZoneObjects.begin();
		totalToLoad += zoneToLoad.prefabList.size();
#endif
		//Engine::game.addSprite(worldmap[zoneToLoadID]->getBackground(), true);
		currentZone = worldmap[zoneToLoadID];
		//loadingScreenProgress.setMax(totalToLoad);
		totalLoaded = 0;
		currentObj = 0;
		loadState = STATE_UNLOAD_OBJECTS;
		break;
	case STATE_UNLOAD_OBJECTS:
		if (lastLoadedZone.second != 0)
		{
			if (currentObj == listOfZoneObjects.size())
			{
				loadState = STATE_RELOAD_OBJECTS;
				listOfZoneObjects.clear();
				currentObj = 0;
#ifdef _EDITOR
				currentObjIterator = EditorAllZones[zoneToLoadID].prefabList.begin();
#else
				currentObjIterator = zoneToLoad.prefabList.begin();
#endif
				break;
			}
#ifdef _EDITOR
			currentObjIterator->second.position = listOfZoneObjects[currentObjIteratorUnload->first]->GetComponent<Component::TransformComponent>()->position;
			currentObjIterator++;
#endif
			//Engine::game.requestRemoveal(listOfZoneObjects[currentObjIteratorUnload->first]);
			currentObj++;
			totalLoaded++;
			currentObjIteratorUnload++;
			//loadingScreenProgress.setValue(totalLoaded);
		}
		else
		{
			loadState = STATE_RELOAD_OBJECTS;
#ifdef _EDITOR
			currentObjIterator = EditorAllZones[zoneToLoadID].prefabList.begin();
#else
			currentObjIterator = zoneToLoad.prefabList.begin();
#endif
		}
		break;
	case STATE_RELOAD_OBJECTS:
#ifdef _EDITOR
		if (currentObj == EditorAllZones[zoneToLoadID].prefabList.size())
		{
			loadState = STATE_DONE;
			//loadState = 1337;
			break;
		}
		else
		{
			{
				std::map<std::pair<std::string, size_t>, Prefab>::iterator it = editorPrefabContainer.find(currentObjIterator->second.fromMod, currentObjIterator->second.ID);
				if (it != editorPrefabContainer.end())
				{
					GameObject* go = it->second.createFromPrefab();
					go->GetComponent<Component::TransformComponent>()->position = currentObjIterator->second.position;

					worldmap[zoneToLoadID]->objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
					listOfZoneObjects.insert(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
					//Engine::game.addGameObject(go);
				}
			}
			currentObj++;
			currentObjIterator++;
			totalLoaded++;
#else
		// will need rework since stuff have changed.
		if (currentObj == zoneToLoad.prefabList.size())
		{
			loadState = STATE_DONE;
		}
		else
		{
			DBZonePrefabStruct prefabID = zoneToLoad.prefabList[currentObjIterator->first];
			{
				Prefab toLoad;
				toLoad.name = "NotInit";
				//if (loadPrefab(prefabID.fromMod, prefabID.ID, toLoad))
				{
					GameObject* go = toLoad.createFromPrefab();
					go->GetComponent<Component::TransformComponent>()->position = prefabID.position;

					worldmap[zoneToLoadID]->objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
					listOfZoneObjects.insert(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
					//Engine::game.addGameObject(go);
				}
			}
			currentObj++;
			totalLoaded++;
			currentObjIterator++;
#endif
			//loadingScreenProgress.setValue(totalLoaded);
		}
		break;
	case STATE_DONE:
		lastLoadedZone = zoneToLoadID;
		isLoading = false;
		break;
#ifdef _DEBUG
	case 1337:
		//loadingScreenProgress.setMax(1337);
		totalLoaded++;
		//loadingScreenProgress.setValue(totalLoaded);
		if (totalLoaded == 1337)
			loadState = STATE_DONE;
#endif
	default:
		break;
		}
	}
void WorldManager::startLoad()
{
	isLoading = true;
	loadState = STATE_PREPARE_LOAD;
}

