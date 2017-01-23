#ifndef ZONE_HPP
#define ZONE_HPP
#include <string>
#include <vector>
#include <Graphic\BackgroundSprite\BackgroundSprite.hpp>
//#include "../../Game/LoadAndSave/Prefab.hpp"
#include "RespawnContainer.hpp"
class GameObject;
class DBZone;
class Zone
{
private:
#ifdef _DEBUG
public:
#endif
	// Background image for the zone
	BackgroundSprite background;
	// Name of the zone
	std::string name;
	// Unique id for each zone
	size_t ID;

	BackgroundSprite loadScreen;
	std::string loadingScreenMessage = "";


public:

	RespawnContainer rc;

	std::string modOrigin;

	//std::vector<std::pair<size_t,Vector2>> prefabList;
	// Vector containing tiles (backgrounds)
	std::vector<BackgroundSprite> foregrounds;

	// Vector containing pair <prefabid (name and id), object(gameobjects)>
	std::vector<std::pair<std::pair<std::string, size_t>, GameObject*>> objects;
	// Gets the background image
	BackgroundSprite* getBackground();

	BackgroundSprite* getLoadingScreen();
	std::string& getLoadingScreenMessage();

	// Gets the name of the zone
	std::string getName();

	// Add a foreground image
	void addForeground(BackgroundSprite sprite);

	//Get the ID for the zone
	int getID();

	std::vector<BackgroundSprite> getForegrounds();

	//constructor
	Zone(std::string name, size_t ID, BackgroundSprite background, std::vector<BackgroundSprite>tiles, std::vector<GameObject*>objects);
	Zone();
	Zone(DBZone& zone);
	Zone(Zone &zone);
	~Zone();
	Zone& operator=(const Zone &z);

#ifdef _DEBUG
	void setBackground(std::string name);
#endif

public:
	template<class Archive>
	void save(Archive &ar) const
	{
		ar(name);
		ar(ID);
		ar(background);
		ar(loadScreen);
		ar(loadingScreenMessage);
		ar(objects.size());
		for (std::vector<std::pair<std::pair<std::string, size_t>, GameObject*>>::const_iterator i = objects.begin(); i != objects.end(); i++)
		{
			ar(i->first.first);
			ar(i->first.second);
			ar(*i->second);
		}
		ar(modOrigin);
	}
	template<class Archive>
	void load(Archive &ar)
	{
		size_t size = 0;
		BackgroundSprite t;
		ar(name);
		ar(ID);
		ar(t);
		background = t;
		ar(t);
		loadScreen = t;
		ar(loadingScreenMessage);
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			std::string name;
			size_t ID;
			GameObject* obj = new GameObject();
			ar(name);
			ar(ID);
			ar(*obj);
			objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(std::pair<std::string, size_t>(name, ID), obj));
		}
		ar(modOrigin);
	}
};

#endif ZONE_HPP