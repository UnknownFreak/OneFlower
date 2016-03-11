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
void WorldManagement::loadZone(std::string addedFromMod,unsigned int zoneID)
{
	if (worldmap.find(std::pair<std::string,size_t>(addedFromMod,zoneID)) != worldmap.end())
	{
		std::string info = "Zone structure with ID: [" + std::to_string(zoneID) + "] is already loaded into memory.\nContinues to load zone...";
#ifdef _DEBUG
		Engine::Window.debug.print(info, __LINE__, __FILE__);
#endif
		// load the Zone with the zone id
		// loadZoneFromMap(zoneID);
		zoneToLoadID = std::pair<std::string, size_t>(addedFromMod, zoneID);
		startLoad();
		//worldFromZone(zoneID);
	}
	else
	{
#ifdef _DEBUG
		std::map<std::pair<std::string, size_t>, DBZone>::iterator it = EditorAllZones.find(std::pair<std::string, size_t>(addedFromMod, zoneID));
		if (it != EditorAllZones.end())
		{
			worldmap.insert(std::pair<std::pair<std::string, size_t>, Zone*>(std::pair<std::string, size_t>(addedFromMod, zoneID), new Zone(it->second)));
			zoneToLoadID = std::pair<std::string, size_t>(addedFromMod, zoneID);
			startLoad();
		}
#else

		loadZoneFromDB(zoneToLoad,zoneID);
		Zone* zoneToAdd = new Zone();
		if(loadZoneFromSaveFile("savefile",*zoneToAdd,zoneID))
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

void WorldManagement::newMod(std::string modName, std::vector<std::string> dependencies)
{
	modLoadOrder.loadOrder.clear();
	myModHeader.name = modName;
	myModHeader.dependencies = dependencies;
	for each (std::string var in myModHeader.dependencies)
	{
		loadMods(var);
	}
	openedMod = modName;
	modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>(modName, modLoadOrder.loadOrder.size()));
	LoadAllZones(EditorAllZones);
	LoadAllPrefabs(editorPrefabContainer);
	LoadAllItems(EditorAllItems);
}
std::vector<std::string> WorldManagement::loadMod(std::string myMod)
{
	std::vector<std::string> myFailed;
	openedMod = myMod;
	modLoadOrder.loadOrder.clear();
	if (!loadModHeader(myMod, myModHeader))
	{
		myFailed.push_back("Error loading "+myMod+"!");
		openedMod = "<Not Set>";
	}
	else
	{
		for each (std::string var in myModHeader.dependencies)
		{
			std::string myReturn = loadMods(var);
			if (myReturn != "<Fine>")
				myFailed.push_back(myReturn);
		}
	}
	modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>(myMod, modLoadOrder.loadOrder.size()));
	LoadAllZones(EditorAllZones);
	LoadAllPrefabs(editorPrefabContainer);
	LoadAllItems(EditorAllItems);
	return myFailed;
}
std::vector<std::string> WorldManagement::getModDependencies(std::string mod)
{
	ModHeader modHdr;
	if (!loadModHeader(mod, modHdr))
	{
		return{};
	}
	else
	{
		return  modHdr.dependencies;
	}
}
std::string WorldManagement::loadMods(std::string myMod)
{
	ModHeader modHdr;
	if (!loadModHeader(myMod, modHdr))
	{
		return "Failed to load dependency mod: " + myMod;
	}
	else
	{
		for each (std::string var in modHdr.dependencies)
		{
			loadMods(var);
		}
		if (modLoadOrder.loadOrder.find(myMod) == modLoadOrder.loadOrder.end())
		{
			modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>(myMod, modLoadOrder.loadOrder.size()));
		}
	}
	return "<Fine>";
}
// default constructor
WorldManagement::WorldManagement() : lastLoadedZone("",0), currentZone(0), modLoadOrder(), loadingScreenProgress(0, 100, 0, Vector2(200, 520), Vector2(400, 20), false)
{
	//testSave();
	if (loadModOrderFile(modLoadOrder) == false)
	{
		MessageBox(Engine::Window.hWnd, "Error loading ModLoadOrder, Using default", "Error", NULL);
		modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>("OneFlower", 0));
	}

}
// deconstructor
WorldManagement::~WorldManagement()
{
	for (std::map<size_t, Item*>::iterator it = EditorAllItems.begin(); it != EditorAllItems.end(); it ++)
	{
		delete it->second;
	}
	//remove loaded zones
	for (std::map<std::pair<std::string, size_t>, Zone*>::iterator it = worldmap.begin(); it != worldmap.end(); it++)
		// if a zone have been unloaded/deleted already
		for(size_t j = 0; j < it->second->objects.size(); j++)
		{
			// request removal of GameObjects /to fix
			Engine::game.requestRemoveal(it->second->objects[j].second);
			it->second->objects[j].second = nullptr;
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
		if (lastLoadedZone.second != 0)
		{
			totalToLoad = EditorAllZones[lastLoadedZone].prefabList.size();
			currentObjIterator = EditorAllZones[lastLoadedZone].prefabList.begin();
		}
		totalToLoad += EditorAllZones[zoneToLoadID].prefabList.size();
#else
		totalToLoad = listOfZoneObjects.size();
		currentObjIteratorUnload = listOfZoneObjects.begin();
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
		if (lastLoadedZone.second != 0)
		{
			if (currentObj == listOfZoneObjects.size())
			{
				loadState = STATE_RELOAD_OBJECTS;
				listOfZoneObjects.clear();
				currentObj = 0;
				currentObjIterator = zoneToLoad.prefabList.begin();
				break;
			}
#ifdef _DEBUG
			currentObjIterator->second.position = listOfZoneObjects[currentObjIterator->first]->GetComponent<TransformComponent>()->position;
#endif
			Engine::game.requestRemoveal(listOfZoneObjects[currentObjIteratorUnload->first]);
			currentObj++;
			totalLoaded++;
			currentObjIteratorUnload++;
			loadingScreenProgress.setValue(totalLoaded);
		}
		else
		{
			loadState = STATE_RELOAD_OBJECTS;
#ifdef _DEBUG
			currentObjIterator = EditorAllZones[zoneToLoadID].prefabList.begin();
#else
			currentObjIterator = zoneToLoad.prefabList.begin();
#endif
		}
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
			{
				std::map<std::pair<std::string, size_t>, Prefab>::iterator it = editorPrefabContainer.find(currentObjIterator->second.fromMod, currentObjIterator->second.ID);
				if (it != editorPrefabContainer.end())
				{
					GameObject* go = it->second.createFromPrefab();
					go->GetComponent<TransformComponent>()->position = currentObjIterator->second.position;

					worldmap[zoneToLoadID]->objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
					listOfZoneObjects.insert(std::pair<std::pair<std::string,size_t>, GameObject*>(currentObjIterator->first, go));
					Engine::game.addGameObject(go);
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
				if (loadPrefab(prefabID.fromMod,prefabID.ID, toLoad))
				{
					GameObject* go = toLoad.createFromPrefab();
					go->GetComponent<TransformComponent>()->position = prefabID.position;

					worldmap[zoneToLoadID]->objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
					listOfZoneObjects.insert(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
					Engine::game.addGameObject(go);
				}
			}
			currentObj++;
			totalLoaded++;
			currentObjIterator++;
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
	if (EditorAllZones.find(std::pair<std::string, size_t>(name, ID)) != EditorAllZones.end())
		loadZone(name,ID);
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
	if (EditorAllZones[lastLoadedZone].mode == EditorObjectSaveMode::REMOVE)
		EditorAllZones[lastLoadedZone].mode = EditorObjectSaveMode::EDIT;
	else
		EditorAllZones[lastLoadedZone].mode = EditorObjectSaveMode::REMOVE;
}
void WorldManagement::EditorSaveZones()
{
	for (std::map<std::pair<std::string, size_t>, DBZonePrefabStruct>::iterator
		i = EditorAllZones[lastLoadedZone].prefabList.begin(); i != EditorAllZones[lastLoadedZone].prefabList.end(); i++)
	{
		i->second.position = listOfZoneObjects[i->first]->GetComponent<TransformComponent>()->position;
	}
	saveGameDatabase(getLoadedMod(),myModHeader, editorPrefabContainer, EditorAllZones, EditorAllItems);
}
void WorldManagement::EditorAddGameObjectToZone(Prefab& prefab, GameObject* go)
{
	DBZonePrefabStruct dbzps;
	dbzps.ID = prefab.ID;
	dbzps.fromMod = prefab.fromMod;
	dbzps.position = go->GetComponent<TransformComponent>()->position;
	dbzps.oldPosition = dbzps.position;
	dbzps.prefabName = prefab.name;
	size_t ValidID = EditorGetValidID();
	EditorAllZones[lastLoadedZone].prefabList.insert(std::pair<std::pair<std::string,size_t>,DBZonePrefabStruct>(std::pair<std::string,size_t>(openedMod,ValidID),dbzps));
	currentZone->objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(std::pair<std::string, size_t>(openedMod, ValidID), go));
	listOfZoneObjects.insert(std::pair<std::pair<std::string, size_t>, GameObject*>(std::pair<std::string, size_t>(openedMod, ValidID), go));
}
size_t WorldManagement::EditorGetValidID()
{
	while (listOfZoneObjects.find(std::pair<std::string,size_t>(openedMod,ID)) != listOfZoneObjects.end())
	{
		ID++;
	}
	return ID;
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
	for (std::map<std::pair<std::string, size_t>,DBZonePrefabStruct>::iterator i = EditorAllZones[lastLoadedZone].prefabList.begin(); 
		i != EditorAllZones[lastLoadedZone].prefabList.end(); i++)
	{
		for (std::vector<std::pair<std::pair<std::string, size_t>, GameObject*>>::iterator it = currentZone->objects.begin();
			it != currentZone->objects.end(); it++)
		{
			if (it->second == go && it->first == i->first)
			{
				//currentZone->objects.erase(currentZone->objects.begin() + i);
				listOfZoneObjects.erase(listOfZoneObjects.find(i->first));
				EditorAllZones[lastLoadedZone].prefabList.erase(i);
				return;
			}
		}
	}
}

std::string WorldManagement::getLoadedMod()
{
	return openedMod;
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