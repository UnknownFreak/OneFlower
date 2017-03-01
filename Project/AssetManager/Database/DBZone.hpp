#ifndef DBZONE_HPP
#define DBZONE_HPP
#include <map>
#include <Core\String.hpp>
#include <Core\Vector.h>
#include "..\ObjectSaveMode.hpp"
class DBZonePrefabStruct
{
public:

	//ID of the prefab
	size_t ID;
	//position of the prefab
	Core::Vector2 position;
	//old position of the prefab, used when removing so we remove the correct object.
	Core::Vector2 oldPosition;
	// which mod to load the prefab from;
	Core::String fromMod = "OneFlower.main";
	Core::String prefabName;
	//type, contains a value from the DBZonePrefabStructType enum
	ObjectSaveMode mode = ObjectSaveMode::ADD;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(fromMod);
		ar(ID);
		ar(position.x);
		ar(oldPosition.x);
		ar(position.y);
		ar(oldPosition.y);
		ar(mode);
		ar(prefabName);
	}
	template<class Archive>
	void load(Archive& ar)
	{
		ar(fromMod);
		ar(ID);
		ar(position.x);
		ar(oldPosition.x);
		ar(position.y);
		ar(oldPosition.y);
		ar(mode);
		ar(prefabName);
	}
};

class DBBackgroundSprite
{
public:
	Core::String name;
	Core::Vector2 position;
	Core::Vector2i size;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(name);
		ar(position.x);
		ar(position.y);
		ar(size.x);
		ar(size.y);
	}
	template<class Archive>
	void load(Archive& ar)
	{
		ar(name);
		ar(position.x);
		ar(position.y);
		ar(size.x);
		ar(size.y);
	}

};

class DBZone
{
public:
	unsigned int ID;
	Core::String fromMod = "OneFlower.main";
	Core::String name;
	DBBackgroundSprite background;
	DBBackgroundSprite loadingScreen;
	Core::String loadingScreenMessage;
	std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct> prefabList;
	ObjectSaveMode mode = ObjectSaveMode::ADD;


	template<class Archive>
	void save(Archive &ar) const
	{
		ar(name);
		ar(ID);
		ar(background);
		ar(loadingScreen);
		ar(loadingScreenMessage);

		std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct> theStuffWeWillActuallySave;

		for (std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::const_iterator i = prefabList.begin(); i != prefabList.end(); i++)
		{
			if (i->second.mode == ObjectSaveMode::DEFAULT)
			{
				if (fromMod == AssetManagerCore::openedMod)
				{
					DBZonePrefabStruct dbzps = i->second;
					dbzps.oldPosition.x = dbzps.position.x;
					dbzps.oldPosition.y = dbzps.position.y;
					theStuffWeWillActuallySave.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(i->first, dbzps));
				}
			}
			else if (i->second.mode == ObjectSaveMode::REMOVE)
			{
				if (fromMod != AssetManagerCore::openedMod)
				{
					theStuffWeWillActuallySave.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(i->first, i->second));
				}
			}
			else if (i->second.mode == ObjectSaveMode::EDIT)
			{
				DBZonePrefabStruct dbzps = i->second;
				if (fromMod == AssetManagerCore::openedMod || AssetManagerCore::openedMod == i->second.fromMod)
				{
					dbzps.mode = EditorObjectSaveMode::DEFAULT;
					dbzps.oldPosition.x = dbzps.position.x;
					dbzps.oldPosition.y = dbzps.position.y;
				}
				theStuffWeWillActuallySave.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(i->first, dbzps));
			}
			else if (i->second.mode == ObjectSaveMode::ADD)
			{
				DBZonePrefabStruct dbzps = i->second;
				if (fromMod == AssetManagerCore::openedMod)
				{
					dbzps.mode = EditorObjectSaveMode::DEFAULT;
					dbzps.oldPosition.x = dbzps.position.x;
					dbzps.oldPosition.y = dbzps.position.y;
				}
				theStuffWeWillActuallySave.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(i->first, dbzps));
			}
		}
		ar(theStuffWeWillActuallySave.size());
		for (std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::iterator i = theStuffWeWillActuallySave.begin(); i != theStuffWeWillActuallySave.end(); i++)
		{
			ar(i->first.first);
			ar(i->first.second);
			ar(i->second);
		}
		ar(mode);
		ar(fromMod);
	}
	template<class Archive>
	void load(Archive &ar)
	{
		size_t size = 0;
		DBBackgroundSprite t;
		ar(name);
		ar(ID);
		ar(t);
		background = t;
		ar(t);
		loadingScreen = t;
		ar(loadingScreenMessage);
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			Core::String name = "OneFlower.main";
			size_t ID;
			DBZonePrefabStruct dbzps;
			ar(name);
			ar(ID);
			ar(dbzps);
			if (dbzps.mode == ObjectSaveMode::REMOVE)
			{
				if (prefabList.find(std::pair<Core::String, size_t>(name, ID)) != prefabList.end())
					prefabList.erase(prefabList.find(std::pair<Core::String, size_t>(name, ID)));
			}
			else if (dbzps.mode == ObjectSaveMode::EDIT)
			{
				if (prefabList.find(std::pair<Core::String, size_t>(name, ID)) != prefabList.end())
					prefabList[std::pair<Core::String, size_t>(name, ID)].position = dbzps.position;
			}
			else
				prefabList.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(std::pair<Core::String, size_t>(name, ID), dbzps));
		}
		ar(mode);
		ar(fromMod);
	}
};

#endif