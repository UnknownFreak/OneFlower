#include "WorldManagement.hpp"
#include "Zone.hpp"
#include "ZoneMaker.hpp"
#include <string>
#include <fstream>
#include "../LoadAndSave/LoadAndSave.hpp"
#include "../../Engine.hpp"
#include "../Component/RenderComponent.h"
#include "../Component/GameObject.h"
#include "../Gfx.h"
// load zone with ID
void WorldManagement::loadZone(unsigned int zoneID)
{
	if (worldmap.find(zoneID) != worldmap.end())
	{
		std::string info = "Zone structure with ID: [" + std::to_string(zoneID) + "] is already loaded into memory.\nContinues to load zone...";
#ifdef _DEBUG
		Engine::Window.debug.print(info, __LINE__, __FILE__);
#endif
		// load the Zone with the zone id
		// loadZoneFromMap(zoneID);
		zoneToLoadID = zoneID;
		startLoad();
		//worldFromZone(zoneID);
	}
	else
	{
#ifdef _DEBUG
		std::map<size_t, DBZone>::iterator it = EditorAllZones.find(zoneID);
		if (it != EditorAllZones.end())
		{
			worldmap.insert(std::pair<unsigned int, Zone*>(zoneID, new Zone(it->second)));
			zoneToLoadID = zoneID;
			startLoad();
		}
#else

		loadZoneFromDB(zoneToLoad,zoneID);
		Zone* zoneToAdd = new Zone();
		if(loadZoneFromSaveFile("savefile",*zoneToAdd,zoneID))
		{
			if (zoneToLoad.prefabList.size() == zoneToAdd->objects.size() + zoneToAdd->rc.respawnTable.size())
			{
				worldmap.insert(std::pair<unsigned int, Zone*>(zoneID, zoneToAdd));
			}
			else
			{
				//reload zone cause it's not the same anymore
			}
		}
		else
		{
			delete zoneToAdd;
			worldmap.insert(std::pair<unsigned int, Zone*>(zoneID, new Zone(zoneToLoad)));
			zoneToLoadID = zoneID;
			startLoad();
		}
#endif
	}
}
// default constructor
WorldManagement::WorldManagement() : lastLoadedZone(0), currentZone(0), modLoadOrder(), loadingScreenProgress(0, 100, 0, Vector2(200, 520), Vector2(400, 20), false)
{
	//testSave();
	if (loadModOrderFile(modLoadOrder) == false)
	{
		MessageBox(Engine::Window.hWnd, "Error loading ModLoadOrder, Using default", "Error", NULL);
		modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>("OneFlower", 0));
	}
#ifdef _DEBUG
	LoadAllZones(EditorAllZones);
	LoadAllPrefabs(editorPrefabContainer);
	LoadAllItems(EditorAllItems);
#endif
}
// deconstructor
WorldManagement::~WorldManagement()
{
	for (std::map<size_t, Item*>::iterator it = EditorAllItems.begin(); it != EditorAllItems.end(); it ++)
	{
		delete it->second;
	}
	//remove loaded zones
	for(size_t i = 0; i < worldmap.size(); i++)
		// if a zone have been unloaded/deleted already
		if(worldmap[i])
			for(size_t j = 0; j < worldmap[i]->objects.size(); j++)
			{
				// request removal of GameObjects /to fix
				Engine::game.requestRemoveal(worldmap[i]->objects[j].second);
				worldmap[i]->objects[j].second = nullptr;
			}
}

Zone* WorldManagement::getCurrentZone()
{
	return currentZone;
}
GUI::Window::Addon::ProgressBar& WorldManagement::getLoadingScreenProgressBar()
{
	return loadingScreenProgress;
}
bool WorldManagement::getIsLoading()
{
	return isLoading;
}
int WorldManagement::getCurrentLoadingState()
{
	return loadState;
}
void WorldManagement::drawLoadingScreen()
{
	if (currentZone)
	{
		Engine::Graphic.DrawLoadingScreen(*currentZone->getLoadingScreen(), currentZone->getLoadingScreenMessage());
	}
}
void WorldManagement::loadSome()
{
	switch (loadState)
	{
	case STATE_NOT_SET:
#ifdef _DEBUG
		Engine::Window.debug.print("Err! Loadstate not set!", __LINE__, __FILE__);
#endif
		break;
	case STATE_PREPARE_LOAD:
#ifdef _DEBUG
		Engine::Window.prefabList.Disable();
		if (lastLoadedZone != 0)
		{
			totalToLoad = EditorAllZones[lastLoadedZone].prefabList.size();
		}
		totalToLoad += EditorAllZones[zoneToLoadID].prefabList.size();
#else
		totalToLoad = listOfZoneObjects.size();
		totalToLoad += zoneToLoad.prefabList.size();
#endif
		Engine::game.addSprite(worldmap[zoneToLoadID]->getBackground(), true);
		currentZone = worldmap[zoneToLoadID];
		loadingScreenProgress.setMax(totalToLoad);
		totalLoaded = 0;
		currentObj = 0;
		loadState = STATE_UNLOAD_OBJECTS;
		break;
	case STATE_UNLOAD_OBJECTS:
		if (lastLoadedZone != 0)
		{
			if (currentObj == listOfZoneObjects.size())
			{
				loadState = STATE_RELOAD_OBJECTS;
				listOfZoneObjects.clear();
				currentObj = 0;
				break;
			}
#ifdef _DEBUG
			EditorAllZones[lastLoadedZone].prefabList[currentObj].position = listOfZoneObjects[currentObj]->GetComponent<TransformComponent>()->position;
#endif
			Engine::game.requestRemoveal(listOfZoneObjects[currentObj]);
			currentObj++;
			totalLoaded++;
			loadingScreenProgress.setValue(totalLoaded);
		}
		else
			loadState = STATE_RELOAD_OBJECTS;
		break;
	case STATE_RELOAD_OBJECTS:
#ifdef _DEBUG
		if (currentObj == EditorAllZones[zoneToLoadID].prefabList.size())
		{
			loadState = STATE_DONE;
			//loadState = 1337;
			break;
		}
		else
		{
			DBZonePrefabStruct prefabID = EditorAllZones[zoneToLoadID].prefabList[currentObj];
			{
				std::map<std::pair<std::string,size_t>, Prefab>::iterator it = editorPrefabContainer.find(prefabID.fromMod,prefabID.ID);
				if (it != editorPrefabContainer.end())
				{
					GameObject* go = it->second.createFromPrefab();
					go->GetComponent<TransformComponent>()->position = prefabID.position;

					worldmap[zoneToLoadID]->objects.push_back(std::pair<size_t, GameObject*>(it->second.ID, go));
					listOfZoneObjects.push_back(go);
					Engine::game.addGameObject(go);
				}
			}
			currentObj++;
			totalLoaded++;
#else
		if (currentObj == zoneToLoad.prefabList.size())
		{
			loadState = STATE_DONE;
		}
		else
		{
			DBZonePrefabStruct prefabID = zoneToLoad.prefabList[currentObj];
			{
				Prefab toLoad;
				toLoad.name = "NotInit";
				if (loadPrefab(prefabID.fromMod,prefabID.ID, toLoad))
				{
					GameObject* go = toLoad.createFromPrefab();
					go->GetComponent<TransformComponent>()->position = prefabID.position;

					worldmap[zoneToLoadID]->objects.push_back(std::pair<size_t, GameObject*>(toLoad.ID, go));
					listOfZoneObjects.push_back(go);
					Engine::game.addGameObject(go);
				}
			}
			currentObj++;
			totalLoaded++;
#endif
			loadingScreenProgress.setValue(totalLoaded);
		}
		break;
	case STATE_DONE:
#ifdef _DEBUG
		Engine::Window.prefabList.Enable();
#endif
		lastLoadedZone = zoneToLoadID;
		isLoading = false;
		break;
#ifdef _DEBUG
	case 1337:
		loadingScreenProgress.setMax(1337);
		totalLoaded++;
		loadingScreenProgress.setValue(totalLoaded);
		if (totalLoaded == 1337)
			loadState = STATE_DONE;
#endif
	default:
		break;
	}
}
void WorldManagement::startLoad()
{
	isLoading = true;
	loadState = STATE_PREPARE_LOAD;
}

#ifdef _DEBUG
void WorldManagement::EditorAddNewZone(std::string name,unsigned int ID)
{
	Engine::Window.debug.print("Rework in progress", __LINE__, __FILE__);
}

void WorldManagement::EditorLoadZone(std::string name,unsigned int ID)
{
	//*change this with listview instead?//*/
	if (EditorAllZones.find(ID) != EditorAllZones.end())
		loadZone(ID);
	else
	{
		MessageBox(Engine::Window.hWnd, "Could not load Zone", "Err", NULL);
	}
	/*std::map<unsigned int,std::string>::iterator it = zoneInfo.find(ID);
	if(it != zoneInfo.end())
		loadZone(ID);
	else
		for(it = zoneInfo.begin(); it != zoneInfo.end(); ++it)
			if(it->second == name + ".zone")
			{
				loadZone(it->first);
				break;
			}*/
}

void WorldManagement::EditorRemoveZone()
{
	if (EditorAllZones[lastLoadedZone].isRemoved)
		EditorAllZones[lastLoadedZone].isRemoved = false;
	else
		EditorAllZones[lastLoadedZone].isRemoved = true;
	Engine::Window.debug.print("Zone with ID " + std::to_string(EditorAllZones[lastLoadedZone].ID)
		+ " have the DeleteFlag set to: " + std::to_string(EditorAllZones[lastLoadedZone].isRemoved), __LINE__, __FILE__);
}
void WorldManagement::EditorSaveZones()
{
	for (size_t i = 0; i < EditorAllZones[lastLoadedZone].prefabList.size(); i++)
	{
		EditorAllZones[lastLoadedZone].prefabList[i].position = listOfZoneObjects[i]->GetComponent<TransformComponent>()->position;
	}
	saveGameDatabase("OneFlower.main", editorPrefabContainer, EditorAllZones, EditorAllItems);
}
void WorldManagement::EditorAddGameObjectToZone(Prefab& prefab, GameObject* go)
{
	DBZonePrefabStruct dbzps;
	dbzps.ID = prefab.ID;
	dbzps.fromMod = prefab.modOrigin;
	dbzps.position = go->GetComponent<TransformComponent>()->position;
	dbzps.oldPosition = dbzps.position;
	EditorAllZones[lastLoadedZone].prefabList.push_back(dbzps);
	currentZone->objects.push_back(std::pair<size_t, GameObject*>(prefab.ID, go));
	listOfZoneObjects.push_back(go);
}
void WorldManagement::EditorSetBackground(std::string name)
{
	currentZone->setBackground(name);
	Engine::game.addSprite(currentZone->getBackground(),true);
}
void WorldManagement::EditorSetBackgroundSize(int x,int y)
{
	currentZone->getBackground()->size.x = x;
	currentZone->getBackground()->size.y = y;
	Engine::game.addSprite(currentZone->getBackground(),true);
}
void WorldManagement::RemoveGameObjectFromZone(GameObject* go)
{
	for (size_t i = 0; i < EditorAllZones[lastLoadedZone].prefabList.size(); i++)
	{
		if (currentZone->objects[i].second == go)
		{
			EditorAllZones[lastLoadedZone].prefabList.erase(EditorAllZones[lastLoadedZone].prefabList.begin() + i);
			//currentZone->objects.erase(currentZone->objects.begin() + i);
			listOfZoneObjects.erase(listOfZoneObjects.begin() + i);
			break;
		}
	}
}

std::string WorldManagement::getLoadedMod()
{
	return "TODO";
}

#endif
#pragma region old
// TODO remake the load structure
// deprecated
/*
void WorldManagement::worldFromZone(unsigned int zoneID)
{
if (lastLoadedZone != 0)
{
#ifdef _DEBUG
for (size_t i = 0; i < EditorAllZones[lastLoadedZone].prefabList.size(); i++)
{

EditorAllZones[lastLoadedZone].prefabList[i].second = listOfZoneObjects[i]->GetComponent<TransformComponent>()->position;
#else
for (size_t i = 0; i < worldmap[lastLoadedZone].objects.size(); i++)
{
#endif
Engine::game.requestRemoveal(listOfZoneObjects[i]);
}
listOfZoneObjects.clear();
}
Engine::game.addSprite(worldmap[zoneID]->getBackground(), true);
#ifdef _DEBUG
for each (std::pair<size_t, Vector2> prefabID in EditorAllZones[zoneID].prefabList)
{
std::map<size_t,Prefab>::iterator it = editorPrefabContainer.find(prefabID.first);
if (it != editorPrefabContainer.end())
{
GameObject* go = it->second.createFromPrefab();
go->GetComponent<TransformComponent>()->position = prefabID.second;

worldmap[zoneID]->objects.push_back(std::pair<size_t, GameObject*>(it->second.ID, go));
listOfZoneObjects.push_back(go);
Engine::game.addGameObject(go);
}
}
#else
// TODO
#endif
lastLoadedZone = zoneID;
currentZone = worldmap[zoneID];
}
*/
#pragma endregion