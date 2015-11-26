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
	if(worldmap.find(zoneID) != worldmap.end())
	{
		std::string info = "Zone structure with ID: [" + std::to_string(zoneID) + "] is already loaded into memory.\nContinues to load zone...";
		Engine::Window.debug.print(info, __LINE__, __FILE__);
		//MessageBox(Engine::Window.hWnd,(LPCSTR)info.c_str(),"INFO",MB_ICONINFORMATION);
		// load the Zone with the zone id
		// loadZoneFromMap(zoneID);
		worldFromZone(zoneID);
	}
	else
	{
#ifdef _DEBUG
		std::map<size_t, DBZone>::iterator it = EditorAllZones.find(zoneID);
		if (it != EditorAllZones.end())
		{
			worldmap.insert(std::pair<unsigned int, Zone*>(zoneID, new Zone(it->second)));
			worldFromZone(zoneID);
		}
#else

		DBZone zone;
		loadZoneFromDB(zone,zoneID);
		Zone* zoneToAdd = new Zone();
		if(loadZoneFromSaveFile("savefile",*zoneToAdd,zoneID))
		{
			if(zoneID.prefabList.size() == zoneToAdd.objects.size() + zoneToAdd.rc.respawnTable.size())
			{
				worldmap.insert(std::pair<unsigned in, Zone*>(zoneID, zoneToAdd));
				worldFromZone(zoneID);
			}
			else
			{
				//reload zone cause it's not the same anymore
			}
		}
		else
		{
			delete zoneToAdd;
			worldmap.insert(std::pair<unsigned in, Zone*>(zoneID, new Zone(zone));
			worldFromZone(zoneID);
		}
#endif
	}
}
// default constructor
WorldManagement::WorldManagement() : lastLoadedZone(0), currentZone(0), modLoadOrder()
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
#endif
}
// deconstructor
WorldManagement::~WorldManagement()
{
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

// TODO remake the load structure
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

Zone* WorldManagement::getCurrentZone()
{
	return currentZone;
}
#ifdef _DEBUG
void WorldManagement::EditorAddNewZone(std::string name,unsigned int ID)
{
	Engine::Window.debug.print("Rework in progress", __LINE__, __FILE__);
	/*
	bool exist = false;
	std::map<unsigned int,std::string>::iterator it = zoneInfo.find(ID);
	if(it != zoneInfo.end())
		exist = true;
	if(exist)
		MessageBox(Engine::Window.hWnd,"ID already taken","ERROR",NULL);
	else
	{
		ZoneMap* tmp = new ZoneMap();
		tmp->name = name;
		tmp->ID = ID;
		saveZone(*tmp);
		zoneInfo.insert(std::pair<unsigned int,std::string>(ID,name + ".zone"));
		loadZone(ID);
		saveInfo(zoneInfo);
	}*/
}

void WorldManagement::EditorLoadZone(std::string name,unsigned int ID)
{
	//*change this with listview instead?//*/
	if (EditorAllZones.find(ID) != EditorAllZones.end())
		loadZone(ID);
	MessageBox(Engine::Window.hWnd, "Load for name only is not added yet", "Info", MB_ICONWARNING);
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
void WorldManagement::EditorSaveZone()
{
	Engine::Window.debug.print("To be replaced with \"Save\"", __LINE__, __FILE__);
	/*ZoneMap zm;

	zm.background = *currentZone->getBackground();
	zm.foregrounds = currentZone->getForegrounds();
	zm.objects = currentZone->objects;
	zm.ID = currentZone->getID();
	zm.name = currentZone->getName();

	saveZone(zm);
	*/
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
			currentZone->objects.erase(currentZone->objects.begin()+i);
	}
}
#endif