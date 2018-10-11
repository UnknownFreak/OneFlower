#ifndef DBZONE_HPP
#define DBZONE_HPP
#include <map>
#include <Core\String.hpp>
#include <Core\Vector.h>

#include "..\ObjectSaveMode.hpp"
#include "../IRequestable.hpp"

// TODO: Remove this and intergrate the prefab and db zone into the Zone. 
// Zone should be variadic. I:e When editor mode it loads as Prefabs, but when loading in game it loads as GameObjects,
// It could also have all the prefabs loaded all the time to create new GameObjects without loading them from file. (Like a spawner).
// TECHNICAL-DEPT: Remove to reduce code duplication intergtate the separate logic. Only separate the logic with #if_defined _EDITOR_ to make special editor logic.

struct DBZonePrefabStruct
{

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

struct DBBackgroundSprite
{
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

class DBZone : public IRequestable
{
public:
	Core::String name;
	DBBackgroundSprite background;
	DBBackgroundSprite loadingScreen;
	Core::String loadingScreenMessage;
	std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct> prefabList;


	template<class Archive>
	void save(Archive &ar) const
	{

		const Core::String& openedMod = Engine::Get<AssetManager>().openedMod;

		ar(cereal::base_class<IRequestable>(this));
		ar(name);
		ar(background);
		ar(loadingScreen);
		ar(loadingScreenMessage);

		std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct> theStuffWeWillActuallySave;

		for (std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::const_iterator i = prefabList.begin(); i != prefabList.end(); i++)
		{
			if (i->second.mode == ObjectSaveMode::DEFAULT)
			{
				if (fromMod == openedMod)
				{
					DBZonePrefabStruct dbzps = i->second;
					dbzps.oldPosition.x = dbzps.position.x;
					dbzps.oldPosition.y = dbzps.position.y;
					theStuffWeWillActuallySave.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(i->first, dbzps));
				}
			}
			else if (i->second.mode == ObjectSaveMode::REMOVE)
			{
				if (fromMod != openedMod)
				{
					theStuffWeWillActuallySave.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(i->first, i->second));
				}
			}
			else if (i->second.mode == ObjectSaveMode::EDIT)
			{
				DBZonePrefabStruct dbzps = i->second;
				if (fromMod == openedMod || openedMod == i->second.fromMod)
				{
					dbzps.mode = ObjectSaveMode::DEFAULT;
					dbzps.oldPosition.x = dbzps.position.x;
					dbzps.oldPosition.y = dbzps.position.y;
				}
				theStuffWeWillActuallySave.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(i->first, dbzps));
			}
			else if (i->second.mode == ObjectSaveMode::ADD)
			{
				DBZonePrefabStruct dbzps = i->second;
				if (fromMod == openedMod)
				{
					dbzps.mode = ObjectSaveMode::DEFAULT;
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
	}
	template<class Archive>
	void load(Archive &ar)
	{
		size_t size = 0;
		DBBackgroundSprite t;
		ar(cereal::base_class<IRequestable>(this));
		ar(name);
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
	}
};

#endif