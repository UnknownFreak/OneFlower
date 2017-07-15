#ifndef TEMPLATEDREQUESTOR_HPP
#define TEMPLATEDREQUESTOR_HPP

#include <map>
#include <Core\String.hpp>
#include "../Database/DatabaseIndex.hpp"

#include "TemplatedRef.hpp"

#include <cereal\archives\binary.hpp>


// Any requestable T must have these attributes:
//Core::String modName;
//ObjectSaveMode mode;
// without these, the object will not be save/load - able
template<class T>
class Requester
{
	friend class Reference<T>;

	typedef std::map<std::pair<Core::String, size_t>, Reference<T>> _requestedMap;
	_requestedMap requestedMap;

	DatabaseIndex::ObjectTypeEnum objectType;

	bool requestFromDatabase(T& _t, Core::String modName, size_t uuid)
	{
		bool found = false;
		for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
		{
			bool eof = false;
			DatabaseIndex ind;
			std::ifstream index(var.first + ".index", std::ios::binary);
			std::ifstream database(var.first, std::ios::binary);
			if (index.is_open())
			{
				cereal::BinaryInputArchive ar(index);
				{
					while (!eof)
					{
						ar(ind);
						if (ind.type == objectType && ind.modFile == modName && ind.ID == uuid)
						{
							database.seekg(ind.row);
							cereal::BinaryInputArchive ModelLoad(database);
							ModelLoad(_t);
							eof = true;
							found = true;
						}
						else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			if (found)
				return found;
		}
		return found;
	}

	Core::String getObjectTypeAsString()
	{
		switch (objectType)
		{
		case DatabaseIndex::ObjectTypeEnum::Header:
			return "Header";
		case DatabaseIndex::ObjectTypeEnum::Zone:
			return "Zone";
		case DatabaseIndex::ObjectTypeEnum::Prefab:
			return "Prefab";
		case DatabaseIndex::ObjectTypeEnum::GameObject:
			return "GameObject";
		case DatabaseIndex::ObjectTypeEnum::Quest:
			return "Quest";
		case DatabaseIndex::ObjectTypeEnum::Item:
			return "Item";
		case DatabaseIndex::ObjectTypeEnum::ModelContainer:
			return "ModelContainer";
		case DatabaseIndex::ObjectTypeEnum::SpriteSheetMap:
			return "SpriteSheetMap";
		case DatabaseIndex::ObjectTypeEnum::EoF:
			return "EoF";
		case DatabaseIndex::ObjectTypeEnum::Undefined:
			return "Undefined";
		default:
			return "Unknown"
		}
	}

	void unload(Core::String modName, size_t uuid)
	{
		_requestedMap::iterator it = requestedMap.find({ modName, uuid });
		if (it != requestedMap.end())
			requestedMap.erase(it);
	}

	bool load(const Core::String& name, size_t uuid)
	{
		requestedMap.insert(requestedMap.end(), std::make_pair({ name, uuid }, Reference<T>(name, uuid, this)));
		return true;
	}

	T load_internal(const Core::String& name, size_t uuid)
	{
		T t();
		if (name == "EMPTY" && uuid == 0)
			return t;
		if (!requestFromDatabase(t, name, uuid))
			Logger::Error("Requestor<" + getObjectTypeAsString() + "> - Unable to request [" + name ", " + std::to_string(uuid) + "] from database.", __FILE__, __LINE__);
		return t;
	}

public:

#ifdef _EDITOR_
	void add(Core::String name, size_t uuid, T obj)
	{
		requestedMap.insert(requestedMap.end(), std::make_pair({ name, uuid }, Reference<T>(name, uuid, this, obj)));
	}
#endif

#ifdef _EDITOR_
	T loadAsync(const Core::String& name, size_t uuid)
	{
		return load_internal(name, uuid);
	}
#else
	std::shared_future<T> loadAsync(Core::String& name, size_t uuid)
	{
		std::shared_future<T>tp = std::async(std::launch::async, [this](std::string name, size_t uuid) -> T {return load_internal(name, uuid); }, name, uuid);
		return tp;
	}
#endif
	const Reference<T>& request(const Core::String& name, size_t uuid)
	{
		if (!name.empty())
		{
			std::map<std::pair<Core::String, size_t>, Reference<T>>::iterator it;
			it = requestedMap.find({ name, uuid });

			if (it != loadedTextureMap.end())
				return &it->second;

			if (load({ name, uuid }))
				return &loadedTextureMap.find({ name, uuid })->second;


			it = requestedMap.find({ "EMPTY", 0});
			if (it != requestedMap.end())
				return &it->second;
			load("EMPTY",0);
			return &requestedMap.find({"EMPTY", 0})->second;
		}
		return nullptr;
	}

public:

	Requester(DatabaseIndex::ObjectTypeEnum objectType) : objectType(objectType)
	{

	}

	Requester(const Requester& copy) = delete;

	void editorLoadAll()
	{
		for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
		{
			bool eof = false;
			DatabaseIndex ind;
			std::ifstream index(var.first + ".index", std::ios::binary);
			std::ifstream database(var.first, std::ios::binary);
			if (index.is_open())
			{
				cereal::BinaryInputArchive ar(index);
				{
					while (!eof)
					{
						ar(ind);
						if (ind.type == objectType)
						{
							database.seekg(ind.row);
							cereal::BinaryInputArchive loader(database);
							std::map<std::pair<std::string, size_t>, Reference<T>>::iterator it = requestedMap.find(std::pair<std::string, size_t>(ind.modFile, ind.ID));
							if (it != requestedMap.end())
							{
								// stuff exist add extra things to object.
								loader(it->second.getReferenced());
							}
							else
							{
								T tmp;
								loader(tmp);
								worldmap.insert(std::pair<std::pair<std::string, size_t>, Reference<T>>
									(std::pair<std::string, size_t>(ind.modFile, ind.ID), Reference<T>(ind.modFile, ind.ID, this, tmp)));
							}
						}
						else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			else
				Logger::Error("Unable to open Index file [" + var.first +
					".index] in Requestor <"+ getObjectTypeAsString() +">", __FILE__, __LINE__);
		}
	}

	void save(DatabaseIndex& ind,
		std::ostream& file,
		cereal::BinaryOutputArchive& indexAr,
		cereal::BinaryOutputArchive& mainAr)
	{
		_requestedMap::iterator it = requestedMap.begin();
		_requestedMap::iterator eit = requestedMap.end();
		for (it; it != eit; it++)
		{
			Prefab& pref = it->second.getReferenced();
			ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
			ind.ID = it->first.second;
			ind.type = objectType;
			ind.modFile = pref.fromMod;
			ind.row = file.tellp();
			if (it->second.mode != ObjectSaveMode::REMOVE)
			{
				bool b = true;
				if (pref.fromMod == AssetManagerCore::openedMod && pref.mode == ObjectSaveMode::EDIT)
					pref.mode = ObjectSaveMode::DEFAULT;
				else if (pref.fromMod == AssetManagerCore::openedMod && pref.mode == ObjectSaveMode::ADD)
					pref.mode = ObjectSaveMode::DEFAULT;
				else if (pref.fromMod != AssetManagerCore::openedMod && pref.mode == ObjectSaveMode::DEFAULT)
					b = false;
				else if (pref.mode > ObjectSaveMode::ADD)
					pref.mode = ObjectSaveMode::DEFAULT;
				if (b)
				{
					indexAr(ind);
					mainAr(pref);
				}
			}
		}
	}

};


#endif