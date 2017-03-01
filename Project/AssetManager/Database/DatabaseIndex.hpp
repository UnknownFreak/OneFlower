#ifndef DATABASE_INDEX_HPP
#define DATABASE_INDEX_HPP
#include <Core/String.hpp>
class DatabaseIndex
{
public:
	long long row = 0;
	unsigned int ID = 0;
	/*
	Type of object to load:
	Zone - load a zonefile
	Prefab - load a prefab
	Gameobject - load a Gameobject
	Quest - load a quest
	Item - load a item
	//*/
	Core::String type = "";
	/*
	Flag types:
	EoF - says it is the endof the file - Do not use, it is automatic.
	Override - SourceID - Overrides object with a new one
	AddTo - SourceID - Adds object to source
	RemoveFrom - SourceID - removes object from source.
	Modify - SourceID - Modify flag tells to modifiy that object
	"-" - No flag
	//*/
	Core::String flags = "";
	/*
	ModFile tells from what mod that object comes from
	//*/
	Core::String modFile = "";

protected:
	//template<class Archive>
	//friend void save(Archive & ar, const DatabaseIndex &index);
	//template<class Archive>
	//friend void load(Archive & ar, DatabaseIndex &index);

public:
#pragma region DatabaseIndex
	template<class Archive>
	void load(Archive& ar)
	{
		ar(row);
		ar(ID);
		ar(type);
		ar(flags);
		ar(modFile);
	}
	template<class Archive>
	void save(Archive& ar) const
	{
		ar(row);
		ar(ID);
		ar(type);
		ar(flags);
		ar(modFile);
	}
#pragma endregion
};

#endif