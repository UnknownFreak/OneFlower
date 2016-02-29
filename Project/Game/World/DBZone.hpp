#ifndef DBZONE_HPP
#define DBZONE_HPP
#include <vector>
#include "../Tile.h"

class DBZonePrefabStruct
{
public:
	enum DBZonePrefabStructType
	{
		/*
		Default mode for saving object,
		this will save the object IF the DBZone fromMod equals
		to the WorldManagement openedMod
		//*/
		DEFAULT,
		/*
		Remove mode for saving object,
		this will remove the object from the DBZone (when loading)
		IF the DBZone fromMod is equal to the WorldManagement openedMod, 
		it will not be saved
		//*/
		REMOVE,
		/*
		Move mode for saving object,
		this will move the object from the DBZone IF the fromMod does not
		equal to the DBZone fromMod, IF it is equal, then it will be saved
		and the flag type will be set to DEFAULT
		//*/
		MOVE,
		/*
		Add mode for saving object,
		this will save the object.
		IF the DBZone fromMod equals WorldManagement openedMod
		the flag will be set to DEFAULT
		//*/
		ADD

	};
	//ID of the prefab
	size_t ID;
	//position of the prefab
	Vector2 position;
	//old position of the prefab, used when removing so we remove the correct object. 
	Vector2 oldPosition;
	// which mod to load the prefab from;
	std::string fromMod = "OneFlower.main";
	//type, contains a value from the DBZonePrefabStructType enum
	size_t type = ADD;
protected:
	template<class T>
	friend void save(T& ar, const DBZonePrefabStruct& dbzps);
	template<class T>
	friend void load(T& ar, DBZonePrefabStruct& dbzps);
};

class DBZone
{
public:
	unsigned int ID;
	std::string fromMod = "OneFlower.main";
	std::string name;
	Tile background;
	Tile loadingScreen;
	std::string loadingScreenMessage;
	std::map<std::pair<std::string,size_t>,DBZonePrefabStruct> prefabList;
#ifdef _DEBUG
	bool isRemoved = false;
#endif
protected:
#ifdef _DEBUG
	template<class T>
	friend void save(T& ar, const DBZone& dbz);
#endif
	template<class T>
	friend void load(T& ar, DBZone& dbz);

};


#endif