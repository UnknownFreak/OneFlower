#ifndef REQUESTOR_HPP
#define REQUESTOR_HPP

#include <fstream>

#ifndef _EDITOR_
#include <future>
#endif

#include <map>

#include <cereal\access.hpp>
#include <cereal\archives\binary.hpp>
#include <cereal\types\memory.hpp>

#include <Core\String.hpp>
#include <Logger\Logger.hpp>

#include "../Database/DatabaseIndex.hpp"
#include "../IRequestable.hpp"

#include "Reference.hpp"

template <class T>
class Requestor
{

	// ##################################################
	// # VARIABLE SECTION								#
	// ##################################################

protected:
	typedef std::map<std::pair<Core::String, size_t>, Reference<T>*> td_map;
	typedef std::pair<Core::String, size_t> td_key;

	td_map requestedMap;

	Core::String loadDirectory;
	const DatabaseIndex::ObjectTypeEnum objectType;
	Core::String pointerPrefixString;

private:
	
	friend class Reference<T>;
	
	// ##################################################
	// # ENABLE IF SECTION PRIVATE						#
	// # Enables different functions for pointer type	#
	// # and non pointer type.							#
	// # These functions should be as short as possible.#
	// ##################################################

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < std::is_base_of<IRequestable, In>::value>::type check() const
	{
		Engine::Get<OneLogger>().Info("Requester <" + getObjectTypeAsString() + "> had all requirements to be created - OK!");
	}

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < !std::is_base_of<IRequestable, In>::value>::type check() const
	{
		static_assert(false, "Class T is not a base class of IRequestable - this object will not be requestable!");
	}

	template <class In = T>
	inline typename std::enable_if<!std::is_pointer<In>::value, T>::type
		defaultValue() const
	{
		return T();
	}

	template <class In = T>
	inline typename std::enable_if<std::is_pointer<In>::value, T>::type
		defaultValue() const
	{
		return nullptr;
	}

	template <class In = T>
	inline const typename std::enable_if<!std::is_pointer<In>::value, Core::String>::type
		getFromMod(const T& _t) const
	{
		return _t.fromMod;
	}

	template <class In = T>
	inline const typename std::enable_if<std::is_pointer<In>::value, Core::String>::type
		getFromMod(const T& _t) const
	{
		return _t->fromMod;
	}

	template <class In = T>
	inline const typename std::enable_if<!std::is_pointer<In>::value, size_t>::type
		getId(const T& _t) const
	{
		return _t.ID;
	}

	template <class In = T>
	inline const typename std::enable_if<std::is_pointer<In>::value, size_t>::type
		getId(const T& _t) const
	{
		return _t->ID;
	}

	template <class In = T>
	inline typename std::enable_if < std::is_pointer<In>::value, void>::type pointerStr()
	{
		pointerPrefixString = "*";
	}

	template <class In = T>
	inline typename std::enable_if < !std::is_pointer<In>::value, void>::type pointerStr()
	{
		pointerPrefixString = "";
	}

	template <class In = T>
	inline const typename std::enable_if<!std::is_pointer<In>::value, bool>::type
		saveIfMode(T& pref) const
	{
		const AssetManager& manager = Engine::Get<AssetManager>();

		if (pref.mode != ObjectSaveMode::REMOVE)
		{
			bool b = true;
			if (pref.fromMod == manager.openedMod && pref.mode == ObjectSaveMode::EDIT)
				pref.mode = ObjectSaveMode::DEFAULT;
			else if (pref.fromMod == manager.openedMod && pref.mode == ObjectSaveMode::ADD)
				pref.mode = ObjectSaveMode::DEFAULT;
			else if (pref.fromMod != manager.openedMod && pref.mode == ObjectSaveMode::DEFAULT)
				b = false;
			else if (pref.mode > ObjectSaveMode::ADD)
				pref.mode = ObjectSaveMode::DEFAULT;
			return b;
		}
		return false;
	}

	template <class In = T>
	inline const typename std::enable_if<std::is_pointer<In>::value, bool >::type
		saveIfMode(T& pref) const
	{
		const AssetManager& manager = Engine::Get<AssetManager>();

		if (pref->mode != ObjectSaveMode::REMOVE)
		{
			bool b = true;
			if (pref->fromMod == manager.openedMod && pref->mode == ObjectSaveMode::EDIT)
				pref->mode = ObjectSaveMode::DEFAULT;
			else if (pref->fromMod == manager.openedMod && pref->mode == ObjectSaveMode::ADD)
				pref->mode = ObjectSaveMode::DEFAULT;
			else if (pref->fromMod != manager.openedMod && pref->mode == ObjectSaveMode::DEFAULT)
				b = false;
			else if (pref->mode > ObjectSaveMode::ADD)
				pref->mode = ObjectSaveMode::DEFAULT;
			return b;
		}
		return false;
	}

	template <class Archive, class In = T>
	inline typename std::enable_if<!std::is_pointer<In>::value, void>::type
		serialize(Archive& archive, In& _t) const
	{
		archive(_t);
	}

	template <class Archive, class In = T>
	inline typename std::enable_if<std::is_pointer<In>::value, void>::type
		serialize(Archive& archive, In& _t) const
	{
		std::unique_ptr<std::remove_pointer<In>::type> _ptr(_t);
		archive(_ptr);
		_t = _ptr.release();
	}

	// ##################################################
	// # METHOD NOT IN NEED OF ENABLE IF				#
	// # Methods that can be used for both pointer		#
	// # and non pointer type.							#
	// ##################################################

	const Core::String getObjectTypeAsString() const
	{
		switch (objectType)
		{
		case DatabaseIndex::ObjectTypeEnum::Header:
			return "Header" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::Zone:
			return "Zone" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::DBZone:
			return "DBZone" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::Prefab:
			return "Prefab" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::GameObject:
			return "GameObject" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::Quest:
			return "Quest" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::Item:
			return "Item" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::Model:
			return "IModel" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::SpriteSheetMap:
			return "SpriteSheetMap" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::EoF:
			return "EoF" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::Undefined:
			return "Undefined" + pointerPrefixString;
		default:
			return "Unknown" + pointerPrefixString;
		}
	}

	const bool load(const Core::String & name, const size_t uuid)
	{
		td_key key(name, uuid);
		requestedMap.insert(std::make_pair(key, new Reference<T>(name, uuid, this)));
		return true;
	}

#ifdef _EDITOR_
	inline T loadAsync(const Core::String& name, const size_t& uuid)
	{
		T t = loadInternal(name, uuid);
		return t;
	}
#else
	std::shared_future<T> loadAsync(const Core::String& name, const size_t uuid)
	{
		std::shared_future<T> tp = std::async(std::launch::async, [this](const std::string name, const size_t uuid) -> T {return loadInternal(name, uuid); }, name, uuid);
		return tp;
	}
#endif

	T loadInternal(const Core::String & name, const size_t uuid)
	{
		T t = defaultValue();
		if (name == "EMPTY" && uuid == 0)
			return t;
		if (!requestFromDatabase(t, name, uuid))
			Engine::Get<OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> - Unable to request [" + name + ", " + std::to_string(uuid) + "] from database.", __FILE__, __LINE__);
		return t;
	}

	inline bool requestFromDatabase(T& _t, const Core::String& modName, const size_t & uuid) const
	{
		bool found = false;
		for each (std::pair<std::string, size_t> var in Engine::Get<AssetManager>().getModLoader().loadOrder)
		{
			bool eof = false;
			DatabaseIndex ind;
			std::ifstream index(loadDirectory + var.first + ".index", std::ios::binary);
			std::ifstream database(loadDirectory + var.first, std::ios::binary);
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
							cereal::BinaryInputArchive loadArchive(database);
							serialize(loadArchive, _t);
							eof = true;
							found = true;
						}
						else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			else
				Engine::Get<OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> unable to open archive [" + modName + "]!", __FILE__, __LINE__);
			if (found)
				return found;
		}
		return found;
	}

	inline void unload(const Core::String & modName, const size_t& uuid)
	{
		td_map::iterator it = requestedMap.find({ modName, uuid });
		if (it != requestedMap.end())
		{
			delete it->second;
			it->second = nullptr;
			requestedMap.erase(it);
		}
	}

public:

	// ##################################################
	// # INITIALIZERS									#
	// ##################################################

	Requestor(DatabaseIndex::ObjectTypeEnum objectType, Core::String loadDirectory = "Data\\") : objectType(objectType), loadDirectory(loadDirectory)
	{
		pointerStr();
		check();
	}
	~Requestor()
	{
		clear();
	}

	// ##################################################
	// # PUBLIC METHODS									#
	// ##################################################

#if defined(_EDITOR_) || defined(_UNITTESTS_)
	inline bool add(T obj)
	{
		const Core::String name = getFromMod(obj);
		const size_t uuid = getId(obj);
		td_key key(name, uuid);

		if (requestedMap.find(key) != requestedMap.end())
		{
			Engine::Get<OneLogger>().Warning("Requestor<" + getObjectTypeAsString() + "> - Object from mod " + name + " and ID " + std::to_string(uuid) + " already exists!", __FILE__, __LINE__);
			return false;
		}
		Engine::Get<OneLogger>().Info("Requestor<" + getObjectTypeAsString() + "> - Object from mod " + name + " and ID " + std::to_string(uuid) + " added.", __FILE__, __LINE__);

		Reference<T>* ref = new Reference<T>(name, uuid, this, obj);
		requestedMap.insert(std::make_pair(key, ref));
		return true;
	}

#endif

	inline void clear()
	{
		td_map::iterator it = requestedMap.begin();
		td_map::iterator eit = requestedMap.end();

		for (; it != eit; it++)
		{
			if (it->second->useCount > 0)
				Engine::Get<OneLogger>().Warning("Unloading object from Requestor<" + getObjectTypeAsString() + "> while it still has uses, this is dangerous and can lead to undefined behaviour", __FILE__, __LINE__);
			delete it->second;
			it->second = nullptr;
		}
		requestedMap.clear();
	}

#ifdef _EDITOR_

	inline void editorLoadAll()
	{
		clear();
		for each (std::pair<std::string, size_t> var in Engine::Get<AssetManager>().getModLoader().loadOrder)
		{
			bool eof = false;
			DatabaseIndex ind;
			std::ifstream index(loadDirectory + var.first + ".index", std::ios::binary);
			std::ifstream database(loadDirectory + var.first, std::ios::binary);
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
							td_map::iterator it = requestedMap.find(std::pair<std::string, size_t>(ind.modFile, ind.ID));


							if (it != requestedMap.end())
							{
								// stuff exist add extra things to object.
								serialize(loader, it->second->getReferenced());
							}
							else
							{
								T tmp = defaultValue();
								serialize(loader, tmp);
								requestedMap.emplace(std::make_pair(td_key(ind.modFile, ind.ID), new Reference<T>(ind.modFile, ind.ID, this, tmp)));
							}
						}
						else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
						{
							eof = true;
							Engine::Get<OneLogger>().Info("Loaded " + std::to_string(requestedMap.size()) + " objects for Requestor<" + getObjectTypeAsString() + ">");
						}
					}
				}
			}
			else
				Engine::Get<OneLogger>().Error("Unable to open Index file [" + var.first +
					".index] in Requestor <" + getObjectTypeAsString() + ">", __FILE__, __LINE__);
			index.close();
			database.close();
		}
	}

	inline std::vector<std::pair<Core::String, size_t>> listAllCurrentLoadedObjects() const
	{
		std::vector<std::pair<Core::String, size_t>> listofall;
		td_map::const_iterator it = requestedMap.begin();
		td_map::const_iterator eit = requestedMap.end();
		for (it; it != eit; it++)
		{
			listofall.push_back(it->first);
		}
		return listofall;
	}
#endif

	inline Reference<T>*& request(const Core::String & name, const size_t uuid)
	{
		td_map::iterator it;
		bool found = false;
		if (!name.empty())
		{
			it = requestedMap.find({ name, uuid });

			if (it != requestedMap.end())
				found = true;
			else if (!found && load(name, uuid))
			{
				it = requestedMap.find({ name, uuid });
				found = true;
			}
		}

		if (!found)
		{
			it = requestedMap.find({ "EMPTY", 0 });
			if (it != requestedMap.end())
				found = true;
			{
				load("EMPTY", 0);
				it = requestedMap.find({ "EMPTY", 0 });
			}
		}

		it->second->useCount++;
		return requestedMap.at({ name, uuid });
	}

	inline bool requestRemoval(const Core::String & name, const size_t uuid)
	{
		td_map::iterator it = requestedMap.find({ name, uuid });
		if (it == requestedMap.end())
			return true;

		bool rv = --it->second->useCount == 0;
		if (rv)
			it->second->unload();
		return rv;
	}

	inline void save(DatabaseIndex & ind, std::ostream & file, cereal::BinaryOutputArchive & indexAr, cereal::BinaryOutputArchive & mainAr) const
	{
		td_map::const_iterator it = requestedMap.begin();
		td_map::const_iterator eit = requestedMap.end();
		for (it; it != eit; it++)
		{
			T& pref = (T&)it->second->getReferenced();
			ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
			ind.ID = it->first.second;
			ind.type = objectType;
			ind.modFile = getFromMod(pref);
			ind.row = file.tellp();

			if (saveIfMode(pref))
			{
				indexAr(ind);
				serialize(mainAr, pref);
			}
		}
	}

};

#endif
