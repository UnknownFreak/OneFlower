#ifndef DBZONE_HPP
#define DBZONE_HPP
#include <vector>
#include "../Tile.h"
#include "../LoadAndSave/EditorObjectSaveMode.hpp"
class DBZonePrefabStruct
{
public:
	
	//ID of the prefab
	size_t ID;
	//position of the prefab
	Vector2 position;
	//old position of the prefab, used when removing so we remove the correct object. 
	Vector2 oldPosition;
	// which mod to load the prefab from;
	std::string fromMod = "OneFlower.main";
	std::string prefabName;
	//type, contains a value from the DBZonePrefabStructType enum
	EditorObjectSaveMode mode = EditorObjectSaveMode::ADD;
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
	EditorObjectSaveMode mode = EditorObjectSaveMode::ADD;
protected:
#ifdef _DEBUG
	template<class T>
	friend void save(T& ar, const DBZone& dbz);
#endif
	template<class T>
	friend void load(T& ar, DBZone& dbz);

};


#endif