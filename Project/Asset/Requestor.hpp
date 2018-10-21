#ifndef REQUESTOR_HPP
#define REQUESTOR_HPP

#include <fstream>

#ifndef _EDITOR_
#include <future>
#endif

#include <map>

#include <cereal\archives\binary.hpp>

#include <Asset/IPatch.hpp>

#include <Core\String.hpp>
#include <Core\Logger.hpp>

#include "DatabaseIndex.hpp"
#include "IRequestable.hpp"

template <class T>
class Requestor
{
	// ##################################################
	// # VARIABLE SECTION								#
	// ##################################################

protected:
	typedef std::map<std::pair<Core::String, size_t>, T> td_map;
	typedef std::pair<Core::String, size_t> td_key;

	td_map requestedMap;

	Core::String loadDirectory;
	const DatabaseIndex::ObjectTypeEnum objectType;
	Core::String pointerPrefixString;

private:
	
	// ##################################################
	// # ENABLE IF SECTION PRIVATE						#
	// # Enables different functions for pointer type	#
	// # and non pointer type.							#
	// # These functions should be as short as possible.#
	// ##################################################

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < std::is_base_of<IRequestable, In>::value>::type check() const
	{
		Engine::GetModule<OneLogger>().Info("Requestor <" + getObjectTypeAsString() + "> had all requirements to be created - OK!");
	}

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < !std::is_base_of<IRequestable, In>::value>::type check() const
	{
		static_assert(false, "Class T is not a base class of IRequestable - this object will not be requestable!");
	}

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < std::is_base_of<IPatch, In>::value>::type patch(T& toPatch, T& patchObject)
	{
		toPatch.Patch(patchObject);
		deleteIfNeeded(patchObject);
	}

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < !std::is_base_of<IPatch, In>::value>::type patch(T& toPatch, T& patchObject)
	{
		Engine::GetModule<OneLogger>().Info("Requestor <" + getObjectTypeAsString() + "> is not patchable, skipping patching when loading!");
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
	inline const typename std::enable_if<!std::is_pointer<In>::value>::type
		deleteIfNeeded(const T&) const
	{
	}

	template <class In = T>
	inline const typename std::enable_if<std::is_pointer<In>::value>::type
		deleteIfNeeded(const T& _t) const
	{
		if (_t)
			delete _t;
	}


	template <class In = T>
	inline const typename std::enable_if<!std::is_pointer<In>::value, typename std::remove_pointer<In>::type*>::type getAsPtr(T& _t)
	{
		return &_t;
	}

	template <class In = T>
	inline const typename std::enable_if<std::is_pointer<In>::value, typename std::remove_pointer<In>::type*>::type getAsPtr(T& _t)
	{
		return _t;
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
		const Asset::AssetManager& manager = Engine::GetModule<Asset::AssetManager>();

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
		const Asset::AssetManager& manager = Engine::GetModule<Asset::AssetManager>();

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
		case DatabaseIndex::ObjectTypeEnum::TextureMap:
			return "TextureMap" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::PrimitiveInt:
			return "Primitive<int>" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::PrimitiveDouble:
			return "Primitive<double>" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::PrimitiveString:
			return "Primitive<string>" + pointerPrefixString;
		case DatabaseIndex::ObjectTypeEnum::StringList:
			return "Primitive<vector<string>>" + pointerPrefixString;
		default:
			return "Unknown" + pointerPrefixString;
		}
	}

	const bool load(const Core::String & name, const size_t uuid)
	{
		td_key key(name, uuid);
		requestedMap.insert(std::make_pair(key, loadInternal(name, uuid)));
		return true;
	}

	T loadInternal(const Core::String & name, const size_t uuid)
	{
		T t = defaultValue();
		if (name == "EMPTY" && uuid == 0)
			return t;
		if (!requestFromDatabase(t, name, uuid))
			Engine::GetModule<OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to request [" + name + ", " + std::to_string(uuid) + "] from database.", __FILE__, __LINE__);
		return t;
	}

	inline bool requestFromDatabase(T& _t, const Core::String& modName, const size_t & uuid) const
	{
		bool found = false;
		bool first_loaded = false;
		bool patching = false;
		for each (std::pair<std::string, size_t> var in Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder)
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
							
							if (std::is_base_of<IPatch, T>::value)
								patching = true;
							if (patching && !first_loaded)
							{
								T _tmp = defaultValue();
								serialize(loadArchive, _tmp);
								patch(_t, _tmp);
							}
							else
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
				Engine::GetModule<OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to open archive [" + modName + "]!", __FILE__, __LINE__);
			if (found && !patching)
				return found;
		}
		return found;
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
		auto ptr = getAsPtr(obj);

		const Core::String name = ptr->fromMod;
		const size_t uuid = ptr->ID;
		td_key key(name, uuid);

		if (requestedMap.find(key) != requestedMap.end())
		{
			Engine::GetModule<OneLogger>().Warning("Requestor<" + getObjectTypeAsString() + "> - Object from mod " + name + " and ID " + std::to_string(uuid) + " already exists!", __FILE__, __LINE__);
			return false;
		}
		Engine::GetModule<OneLogger>().Info("Requestor<" + getObjectTypeAsString() + "> - Object from mod " + name + " and ID " + std::to_string(uuid) + " added.", __FILE__, __LINE__);

		requestedMap.insert(std::make_pair(key, obj));
		return true;
	}

#endif

	inline void clear()
	{
		td_map::iterator it = requestedMap.begin();
		td_map::iterator eit = requestedMap.end();

		for (; it != eit; it++)
		{
			//if (it->second->useCount > 0)
			Engine::GetModule<OneLogger>().Warning("Unloading object using clear from Requestor<" + getObjectTypeAsString() + "> it is still possible it has uses," 
				"this is dangerous and can lead to undefined behaviour if any references or pointers are used.", __FILE__, __LINE__);
			
			deleteIfNeeded(it->second);
		}
		requestedMap.clear();
	}

#ifdef _EDITOR_

	inline void editorLoadAll(void(*onObjectLoaded)(const Core::String, const size_t, const Core::String, const ObjectSaveMode,
		const DatabaseIndex::ObjectTypeEnum, void*))
	{
		clear();
		for each (std::pair<std::string, size_t> var in Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder)
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
								serialize(loader, it->second);
							}
							else
							{
								T tmp = defaultValue();
								serialize(loader, tmp);
								requestedMap.emplace(std::make_pair(td_key(ind.modFile, ind.ID), tmp));
								auto ref = getAsPtr(tmp);
								onObjectLoaded(ind.modFile, ind.ID, ref->getName(), ref->mode, objectType, (void*)ref);
							}
						}
						else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
						{
							eof = true;
							Engine::GetModule<OneLogger>().Info("Requestor<" + getObjectTypeAsString() + "> Loaded from ["+ var.first +"]" + std::to_string(requestedMap.size()) + " objects", __FILE__, __LINE__);
						}
					}
				}
			}
			else
				Engine::GetModule<OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to open index file [" + var.first + ".index]!", __FILE__, __LINE__);
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

	inline std::vector<std::pair<Core::String, size_t>> listAllObjectKeys() const
	{
		std::vector<std::pair<Core::String, size_t>> listofall;

		for each (std::pair<std::string, size_t> var in Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder)
		{
			bool eof = false;
			DatabaseIndex ind;
			std::ifstream index(loadDirectory + var.first + ".index", std::ios::binary);
			if (index.is_open())
			{
				cereal::BinaryInputArchive ar(index);
				{
					while (!eof)
					{
						ar(ind);
						if (ind.type == objectType)
						{
							listofall.push_back({ ind.modFile, ind.ID });
						}
						else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			else
				Engine::GetModule<OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to open index file [" + var.first + ".index]!", __FILE__, __LINE__);
		}
		return listofall;
	}

	inline T& request(const Core::String & name, const size_t uuid)
	{
		td_key empty = { "EMPTY", 1 };
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
			it = requestedMap.find(empty);
			if (it == requestedMap.end())
				requestedMap[empty] = defaultValue();
			return requestedMap[empty];
		}
		return it->second;
	}

	inline void requestRemoval(const Core::String & name, const size_t uuid)
	{
		td_map::iterator it = requestedMap.find({ name, uuid });
		if (it != requestedMap.end())
		{
			deleteIfNeeded(it->second);
			requestedMap.erase(it);
		}
	}

	inline void save(DatabaseIndex & ind, std::ostream & file, cereal::BinaryOutputArchive & indexAr, cereal::BinaryOutputArchive & mainAr)
	{
		td_map::iterator it = requestedMap.begin();
		td_map::iterator eit = requestedMap.end();
		for (it; it != eit; it++)
		{
			ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
			ind.ID = it->first.second;
			ind.type = objectType;
			ind.modFile = getFromMod(it->second);
			ind.row = file.tellp();

			if (saveIfMode(it->second))
			{
				indexAr(ind);
				serialize(mainAr, it->second);
			}
		}
	}

};

#endif
