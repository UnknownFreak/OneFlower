#include "Zone.hpp"
#include <AssetManager\AssetManagerCore.hpp>
#include <AssetManager\Database\DBZone.hpp>
#include <Core\Component\GameObject.h>

Zone::Zone(Core::String n, size_t id, BackgroundSprite bg, std::vector<BackgroundSprite> tiles, std::vector<GameObject*> ob) : name(n), ID(id), background(bg)
{
	//add the foregrounds from tiles vector
	for (size_t i = 0; i < tiles.size(); i++)
		foregrounds.push_back(tiles[i]);
	//add the gameobjects from GameObject vector
	/*for(size_t i = 0; i < ob.size(); i++)
	{
		//	GameObject go = ob[i];
		objects.push_back(ob[i]);
	}*/
}
// Copy constructor
Zone::Zone(Zone &z) : name(z.name), ID(z.ID), background(z.background), loadScreen(z.loadScreen), loadingScreenMessage(z.loadingScreenMessage)
{
	for (size_t i = 0; i < z.foregrounds.size(); i++)
		foregrounds.push_back(z.foregrounds[i]);
	for (size_t i = 0; i < z.objects.size(); i++)
		this->objects.push_back(z.objects[i]);
}

Zone::Zone(DBZone& zone) : name(zone.name), ID(zone.ID), background(zone.background), loadScreen(zone.loadingScreen), loadingScreenMessage(zone.loadingScreenMessage)
{
}
//default constructor
Zone::Zone() : name(""), ID(0)
{
}
// deconstructor
Zone::~Zone()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i].second;
		objects[i].second = nullptr;
	}
	objects.empty();
	foregrounds.empty();
}
// operator =
Zone& Zone::operator=(const Zone &z)
{
	name = z.name;
	ID = z.ID;
	background = z.background;
	loadScreen = z.loadScreen;
	loadingScreenMessage = z.loadingScreenMessage;
	for (size_t i = 0; i < z.foregrounds.size(); i++)
		foregrounds.push_back(z.foregrounds[i]);
	for (size_t i = 0; i < z.objects.size(); i++)
		objects.push_back(z.objects[i]);

	return *this;
}

std::vector<BackgroundSprite> Zone::getForegrounds()
{
	return foregrounds;
}

int Zone::getID()
{
	return ID;
}
Core::String Zone::getName()
{
	return name;
}
BackgroundSprite* Zone::getBackground()
{
	return &background;
}

BackgroundSprite* Zone::getLoadingScreen()
{
	return &loadScreen;
}

Core::String& Zone::getLoadingScreenMessage()
{
	return loadingScreenMessage;
}

void Zone::addForeground(BackgroundSprite fg)
{
	foregrounds.push_back(fg);
}

#ifdef _DEBUG

void Zone::setBackground(Core::String name)
{
	background.name = name;
	background.sprite.setTexture(Engine::Get<AssetManager>().textureloader.requestTexture(name));
}

#endif