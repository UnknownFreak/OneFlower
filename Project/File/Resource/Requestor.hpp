#ifndef REQUESTOR_HPP
#define REQUESTOR_HPP

#include <fstream>

#ifndef _EDITOR_
#include <future>
#endif

#include <map>

#pragma warning(push)
#pragma warning(disable: 4003)
#include <cereal\archives\binary.hpp>
#include <cereal\types\memory.hpp>
#pragma warning(pop)

#include <Interfaces/IPatch.hpp>
#include <Interfaces/IRequestable.hpp>

#include <Helpers\String.hpp>
#include <Module/Logger/OneLogger.hpp>

#include <Module/EngineModuleManager.hpp>

#include <File/DatabaseIndex.hpp>
#include <File/Mod/ModLoader.hpp>
#include <File/Mod/ModFileUUIDHelper.hpp>


template <class T>
class Requestor
{
	// ##################################################
	// # VARIABLE SECTION								#
	// ##################################################

	struct myhash
	{
		size_t operator() (const std::pair<Core::String, Core::uuid>& key) const noexcept
		{
			return (size_t)std::hash<Core::String>()(key.first) ^ (std::hash<Core::uuid>()(key.second) < 1);
		}
	};

protected:
	typedef std::unordered_map<std::pair<Core::String, Core::uuid>, T, myhash> td_map;
	typedef std::pair<Core::String, Core::uuid> td_key;

	td_map requestedMap;

	Core::String loadDirectory;
	Enums::ObjectType objectType;
	Core::String pointerPrefixString;

private:
	
	// ##################################################
	// # ENABLE IF SECTION PRIVATE						#
	// # Enables different functions for pointer type	#
	// # and non pointer type.							#
	// # These functions should be as short as possible.#
	// ##################################################
	

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < std::is_base_of<Interfaces::IRequestable, In>::value>::type check() const
	{
		Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Requestor <" + getObjectTypeAsString() + "> had all requirements to be created - OK!");
	}

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < !std::is_base_of<Interfaces::IRequestable, In>::value>::type check() const
	{
		static_assert(false, "Class T is not a base class of IRequestable - this object will not be requestable!");
	}

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < std::is_base_of<Interfaces::IPatch, In>::value>::type patch(T& toPatch, const T& patchObject) const
	{
		toPatch.Patch(patchObject);
		deleteIfNeeded(patchObject);
	}

	template <class In = std::remove_pointer<T>::type>
	inline typename std::enable_if < !std::is_base_of<Interfaces::IPatch, In>::value>::type patch(T&, T&) const
	{
		Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Requestor <" + getObjectTypeAsString() + "> is not patchable, skipping patching when loading!");
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
	inline typename std::enable_if<!std::is_pointer<In>::value, typename std::remove_pointer<In>::type*>::type getAsPtr(T& _t)
	{
		return &_t;
	}

	template <class In = T>
	inline typename std::enable_if<std::is_pointer<In>::value, typename std::remove_pointer<In>::type*>::type getAsPtr(T& _t)
	{
		return _t;
	}

	template <class In = T>
	inline typename std::enable_if<!std::is_pointer<In>::value, Core::String>::type
		getFromMod(const T& _t) const
	{
		return _t.fromMod;
	}

	template <class In = T>
	inline typename std::enable_if<std::is_pointer<In>::value, Core::String>::type
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
	inline typename std::enable_if<!std::is_pointer<In>::value, bool>::type
		saveIfMode(T& pref) const
	{
		const Asset::AssetManager& manager = Engine::GetModule<Asset::AssetManager>();
		
		if (pref.mode != Enums::ObjectSaveMode::REMOVE)
		{
			bool b = true;
			if (pref.fromMod == manager.openedMod && pref.mode == Enums::ObjectSaveMode::EDIT)
				pref.mode = Enums::ObjectSaveMode::DEFAULT;
			else if (pref.fromMod == manager.openedMod && pref.mode == Enums::ObjectSaveMode::ADD)
				pref.mode = Enums::ObjectSaveMode::DEFAULT;
			else if (pref.fromMod != manager.openedMod && pref.mode == Enums::ObjectSaveMode::DEFAULT)
				b = false;
			else if (pref.mode > Enums::ObjectSaveMode::ADD)
				pref.mode = Enums::ObjectSaveMode::DEFAULT;
			return b;
		}
		return false;
	}

	template <class In = T>
	inline typename std::enable_if<std::is_pointer<In>::value, bool >::type
		saveIfMode(T& pref) const
	{
		const Asset::AssetManager& manager = Engine::GetModule<Asset::AssetManager>();
		
		if (pref->mode != Enums::ObjectSaveMode::REMOVE)
		{
			bool b = true;
			if (pref->fromMod == manager.openedMod && pref->mode == Enums::ObjectSaveMode::EDIT)
				pref->mode = Enums::ObjectSaveMode::DEFAULT;
			else if (pref->fromMod == manager.openedMod && pref->mode == Enums::ObjectSaveMode::ADD)
				pref->mode = Enums::ObjectSaveMode::DEFAULT;
			else if (pref->fromMod != manager.openedMod && pref->mode == Enums::ObjectSaveMode::DEFAULT)
				b = false;
			else if (pref->mode > Enums::ObjectSaveMode::ADD)
				pref->mode = Enums::ObjectSaveMode::DEFAULT;
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

	Core::String getObjectTypeAsString() const
	{
		switch (objectType)
		{
		case Enums::ObjectType::Header:
			return "Header" + pointerPrefixString;
		case Enums::ObjectType::Zone:
			return "Zone" + pointerPrefixString;
		case Enums::ObjectType::DBZone:
			return "DBZone" + pointerPrefixString;
		case Enums::ObjectType::Prefab:
			return "Prefab" + pointerPrefixString;
		case Enums::ObjectType::GameObject:
			return "GameObject" + pointerPrefixString;
		case Enums::ObjectType::Quest:
			return "Quest" + pointerPrefixString;
		case Enums::ObjectType::Item:
			return "Item" + pointerPrefixString;
		case Enums::ObjectType::Model:
			return "IModel" + pointerPrefixString;
		case Enums::ObjectType::SpriteSheetMap:
			return "SpriteSheetMap" + pointerPrefixString;
		case Enums::ObjectType::EoF:
			return "EoF" + pointerPrefixString;
		case Enums::ObjectType::Undefined:
			return "Undefined" + pointerPrefixString;
		case Enums::ObjectType::TextureMap:
			return "TextureMap" + pointerPrefixString;
		case Enums::ObjectType::PrimitiveInt:
			return "Primitive<int>" + pointerPrefixString;
		case Enums::ObjectType::PrimitiveDouble:
			return "Primitive<double>" + pointerPrefixString;
		case Enums::ObjectType::PrimitiveString:
			return "Primitive<string>" + pointerPrefixString;
		case Enums::ObjectType::StringList:
			return "Primitive<vector<string>>" + pointerPrefixString;
		case Enums::ObjectType::Language:
			return "TranslationString>" + pointerPrefixString;
		case Enums::ObjectType::TileAtlas:
			return "TileAtlas" + pointerPrefixString;
		case Enums::ObjectType::TileChunk:
			return "TileChunk" + pointerPrefixString;
		case Enums::ObjectType::ColliderChunk:
			return "ColliderChunk" + pointerPrefixString;
		default:
			return "Unknown" + pointerPrefixString;
		}
	}

	bool load(const Core::String & name, const Core::uuid& uuid)
	{
		td_key key(name, uuid);
		requestedMap.insert(std::make_pair(key, loadInternal(name, uuid)));
		return true;
	}

	T loadInternal(const Core::String & name, const Core::uuid& uuid)
	{
		T t = defaultValue();
		if (name == "EMPTY" && uuid.is_nil() || name==Core::Builtin && uuid.is_nil())
			return t;
		if (!requestFromDatabase(t, name, uuid))
			Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to request [" + name + ", " + uuid.to_string() + "] from database.", __FILE__, __LINE__);
		return t;
	}

	inline bool requestFromDatabase(T& _t, const Core::String& modName, const Core::uuid & uuid) const
	{
		bool found = false;
		bool first_loaded = false;
		bool patching = false;
		for(std::pair<std::string, size_t> var : getLoadOrder())
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
							
							if (std::is_base_of<Interfaces::IPatch, T>::value)
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
						else if (ind.flags == Enums::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			else
				Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to open archive [" + modName + "]!", __FILE__, __LINE__);
			if (found && !patching)
				return found;
		}
		return found;
	}

	std::map<Core::String, size_t> getLoadOrder() const
	{
		if (fileLoadOrder.size() == 0)
			return Engine::GetModule<File::Mod::ModLoader>().loadOrder;
		return fileLoadOrder;
	}

public:
	std::map<Core::String, size_t> fileLoadOrder;

	// ##################################################
	// # INITIALIZERS									#
	// ##################################################

	Requestor(const Enums::ObjectType& objectType, const Core::String& loadDirectory = "Data\\", const std::map<Core::String, size_t>& loadOrder = {}) :
		objectType(objectType), loadDirectory(loadDirectory), fileLoadOrder(loadOrder)
	{
		pointerStr();
		check();
	}

	~Requestor()
	{
		clear();
	}

	Requestor(const Requestor& copy) :  Requestor(copy.objectType, copy.loadDirectory,  copy.fileLoadOrder)
	{
		requestedMap = copy.requestedMap;
	}

	Requestor& Requestor::operator=(const Requestor& right)
	{
		if (this == &right)
			return *this;
		objectType = right.objectType;
		loadDirectory = right.loadDirectory;
		fileLoadOrder = right.fileLoadOrder;
		requestedMap = right.requestedMap;
		return *this;
	}

	// ##################################################
	// # PUBLIC METHODS									#
	// ##################################################

#if defined(_EDITOR_) || defined(_UNITTESTS_) || TRUE
	inline bool add(T obj)
	{
		auto ptr = getAsPtr(obj);

		const Core::String name = ptr->fromMod;
		const Core::uuid uuid = ptr->ID;
		td_key key(name, uuid);

		if (requestedMap.find(key) != requestedMap.end())
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Requestor<" + getObjectTypeAsString() + "> - Object from mod " + name + " and ID " + uuid.to_string() + " already exists!", __FILE__, __LINE__);
			return false;
		}
		Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Requestor<" + getObjectTypeAsString() + "> - Object from mod " + name + " and ID " + uuid.to_string() + " added.", __FILE__, __LINE__);

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
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Unloading object using clear from Requestor<" + getObjectTypeAsString() + "> it is still possible it has uses,"
				"this is dangerous and can lead to undefined behaviour if any references or pointers are used.", __FILE__, __LINE__);
			
			deleteIfNeeded(it->second);
		}
		requestedMap.clear();
	}

#ifdef _EDITOR_

	inline void editorLoadAll(void(*onObjectLoaded)(const Core::String, const Core::uuid&, const Core::String, const ObjectSaveMode,
		const DatabaseIndex::ObjectTypeEnum, void*))
	{
		clear();
		for(std::pair<std::string, size_t> var : getLoadOrder())
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
							td_map::iterator it = requestedMap.find(std::pair<std::string, Core::uuid>(ind.modFile, ind.ID));

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
						else if (ind.flags == Enums::ObjectType::EoF)
						{
							eof = true;
							Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Requestor<" + getObjectTypeAsString() + "> Loaded from ["+ var.first +"]" + std::to_string(requestedMap.size()) + " objects", __FILE__, __LINE__);
						}
					}
				}
			}
			else
				Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to open index file [" + var.first + ".index]!", __FILE__, __LINE__);
			index.close();
			database.close();
		}
	}

	inline std::vector<std::pair<Core::String, Core::uuid>> listAllCurrentLoadedObjects() const
	{
		std::vector<std::pair<Core::String, Core::uuid>> listofall;
		td_map::const_iterator it = requestedMap.begin();
		td_map::const_iterator eit = requestedMap.end();
		for (it; it != eit; it++)
		{
			listofall.push_back(it->first);
		}
		return listofall;
	}
#endif

	inline std::vector<std::pair<Core::String, Core::uuid>> listAllObjectKeys() const
	{
		std::vector<std::pair<Core::String, Core::uuid>> listofall;
		for(std::pair<std::string, size_t> var :getLoadOrder())
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
						else if (ind.flags == Enums::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			else
				Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Requestor<" + getObjectTypeAsString() + "> Unable to open index file [" + var.first + ".index]!", __FILE__, __LINE__);
		}
		return listofall;
	}
	
	inline T requestUniqueInstance(const File::Mod::ModFileUUIDHelper& modFile)
	{
		return loadInternal(modFile.name, modFile.uuid);
	}

	template<class Ty>
	inline Ty* request(const File::Mod::ModFileUUIDHelper& modfile)
	{
		T& requested = request(modfile);
		if (requested.objectType == IRequestable::Traits<Ty>::type)
			return (Ty)request(modfile);
		return nullptr;
	}

	inline T& request(const File::Mod::ModFileUUIDHelper& modfile)
	{
		return request(modfile.name, modfile.uuid);
	}

	inline T& request(const Core::String & name, const Core::uuid& uuid)
	{
		td_key empty = { "EMPTY", Core::uuid::nil() };
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

	inline void requestRemoval(const Core::String & name, const Core::uuid& uuid)
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
			ind.flags = Enums::ObjectFlag::NoFlag;
			ind.ID = it->first.second;
			ind.type = objectType;
			ind.modFile = getFromMod(it->second);
			ind.row = file.tellp();
	
			if (saveIfMode(it->second))
			{
				Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Saving object: ");
				indexAr(ind);
				serialize(mainAr, it->second);
			}
		}
	}

};

#endif
