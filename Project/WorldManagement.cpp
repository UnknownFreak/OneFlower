#include "WorldManagement.hpp"
#include "Zone.hpp"
#include "ZoneMaker.hpp"
#include <string>
#include <fstream>
#include "LoadAndSave/LoadAndSave.hpp"
#include "Engine.hpp"
#include "Component\RenderComponent.h"
#include "Component\GameObject.h"
#include "Gfx.h"

// load zone with ID
void WorldManagement::loadZone(unsigned int zoneID)
{
	if(worldmap.find(zoneID) != worldmap.end())
	{
		std::string info = "zone with ID: [" + std::to_string(zoneID) + "] is already loaded\ncontinues to load zone...";
		MessageBox(Engine::Window.hWnd,(LPCSTR)info.c_str(),"Stuff",NULL);
		// load the Zone with the zone id
		// loadZoneFromMap(zoneID);
		//worldFromZone(zoneID);
	}
	else
	{
		zone = new Zone();
		if(loadZoneFile(zoneInfo.find(zoneID)->second,*zone))
		{
			worldmap.insert(std::pair<unsigned int,Zone*>(zone->getID(),zone));
			worldFromZone(zoneID);
		}
		else
		{
			//Todo return to menu if failed to load zone.
		}
	}
}
// default constructor
WorldManagement::WorldManagement(): lastLoadedZone(0)
{
	if(loadZoneInfo(zoneInfo) == false)
	{
		MessageBox(Engine::Window.hWnd,"Error loading zoneinfo","Error",NULL);
		zoneInfo.insert(std::pair<int,std::string>(1,"test.zone"));
	}
}
// deconstructor
WorldManagement::~WorldManagement()
{
	//rmeove the last loaded zone
	for(int i = 0; i < worldmap.size(); i++)
		// if a zone have been unloaded/deleted already
		if(worldmap[i])
			for(int j = 0; j < worldmap[i]->objects.size(); j++)
			{
				// request removal of GameObjects /to fix
				Engine::game.requestRemoveal(worldmap[i]->objects[j]);
				worldmap[i]->objects[j] = nullptr;
			}

	delete zone;
	zone = nullptr;
}

// TODO remake the load structure
// load a zone from the world, removes the old one
void WorldManagement::worldFromZone(unsigned int zoneID)
{
	Engine::View.camera.reset(sf::FloatRect(0,0,800,600));
	for(size_t i = 0; i < worldmap[zoneID]->objects.size(); i++)
	{
		Engine::game.addGameObject(worldmap[zoneID]->objects[i]);
	}
	//add background;
	Engine::game.addSprite(&worldmap[zoneID]->getBackground(),true);
	//add foregrounds;
	for(size_t i = 0; i < worldmap[zoneID]->foregrounds.size(); i++)
	{
		Engine::game.addSprite(&worldmap[zoneID]->foregrounds[i]);
	}
	// when loading first zone
	if(lastLoadedZone == 0)
		lastLoadedZone = zoneID;
	else
	{
		for(size_t i = 0; i < worldmap[lastLoadedZone]->foregrounds.size(); i++)
		{
			Engine::game.requestRemovealForeground(&worldmap[lastLoadedZone]->foregrounds[i]);
		}
		for(size_t i = 0; i < worldmap[lastLoadedZone]->objects.size(); i++)
		{
			// request removal of GameObjects /to fix
			Engine::game.requestRemoveal(worldmap[lastLoadedZone]->objects[i]);
			worldmap[lastLoadedZone]->objects[i] = nullptr;
		}
		delete worldmap[lastLoadedZone];
		worldmap[lastLoadedZone] = nullptr;
		worldmap.erase(lastLoadedZone);
		lastLoadedZone = zoneID;
	}
	currentZone = worldmap[lastLoadedZone];
}

Zone* WorldManagement::getCurrentZone()
{
	return currentZone;
}
#ifdef _DEBUG
void WorldManagement::EditorAddNewZone(std::string name,unsigned int ID)
{
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
	}
}

void WorldManagement::EditorLoadZone(std::string name,unsigned int ID)
{
	std::map<unsigned int,std::string>::iterator it = zoneInfo.find(ID);
	if(it != zoneInfo.end())
		loadZone(ID);
	else
		for(it = zoneInfo.begin(); it != zoneInfo.end(); ++it)
			if(it->second == name + ".zone")
			{
				loadZone(it->first);
				break;
			}
}

void WorldManagement::EditorRemoveZone()
{
	std::map<unsigned int,std::string>::iterator it = zoneInfo.find(currentZone->getID());
	if(it != zoneInfo.end())
	{
		if(std::remove(it->second.c_str()) != 0)
		{
			MessageBox(Engine::Window.hWnd,"File does not exist.","Error",NULL);
			zoneInfo.erase(it);
			saveInfo(zoneInfo);
		}
		else
		{
			zoneInfo.erase(it);
			saveInfo(zoneInfo);
			MessageBox(Engine::Window.hWnd,"TODO","INFO",NULL);
		}
	}
}
void WorldManagement::EditorSaveZone()
{
	ZoneMap zm;

	zm.background = currentZone->getBackground();
	zm.foregrounds = currentZone->getForegrounds();
	zm.objects = currentZone->objects;
	zm.ID = currentZone->getID();
	zm.name = currentZone->getName();

	saveZone(zm);
}

void WorldManagement::EditorSetBackground(std::string name)
{
	currentZone->setBackground(name);
	Engine::game.addSprite(&currentZone->getBackground(),true);
}
#endif