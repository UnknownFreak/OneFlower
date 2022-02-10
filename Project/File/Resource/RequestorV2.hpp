#ifndef REQUESTORV2_HPP
#define REQUESTORV2_HPP

#include "RegisterRTTI.hpp"

#include <fstream>
#include <unordered_map>

#include <Interfaces/IPatch.hpp>
#include <Interfaces/IRequestable.hpp>

#include <Helpers\String.hpp>
#include <Module/Logger/OneLogger.hpp>

#include <Module/EngineModuleManager.hpp>

#include <File/DatabaseIndex.hpp>
#include <File/ModLoader.hpp>
#include <File/ModFileUUIDHelper.hpp>

//#pragma warning(push)
//#pragma warning(disable: 4003)
#include <cereal\archives\binary.hpp>
//#pragma warning(pop)

class RequestorV2
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
	typedef std::unordered_map<std::pair<Core::String, Core::uuid>, std::unique_ptr<Interfaces::IRequestable>, myhash> td_map;
	typedef std::pair<Core::String, Core::uuid> td_key;

	td_map requestedMap;

	Core::String loadDirectory;
	Core::String pointerPrefixString;

private:
	
	// ##################################################
	// # ENABLE IF SECTION PRIVATE						#
	// # Enables different functions for pointer type	#
	// # and non pointer type.							#
	// # These functions should be as short as possible.#
	// ##################################################
	

	template <class In>
	inline typename std::enable_if < std::is_base_of<Interfaces::IPatch, In>::value>::type patch(In& toPatch, const In& patchObject) const
	{
		toPatch.Patch(patchObject);
	}

	template <class In>
	inline typename std::enable_if < !std::is_base_of<Interfaces::IPatch, In>::value>::type patch(In&, In&) const
	{
		//Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Requestor <" + getObjectTypeAsString(Interfaces::Trait<In>::type) + "> is not patchable, skipping patching when loading!");
	}

	bool saveIfMode(const std::unique_ptr<Interfaces::IRequestable>& ) const
	{
		//const Asset::AssetManager& manager = Engine::GetModule<Asset::AssetManager>();
		//
		//if (pref->mode != Enums::ObjectSaveMode::REMOVE)
		//{
		//	bool b = true;
		//	if (pref->fromMod == manager.openedMod && pref->mode == Enums::ObjectSaveMode::EDIT)
		//		pref->mode = Enums::ObjectSaveMode::DEFAULT;
		//	else if (pref->fromMod == manager.openedMod && pref->mode == Enums::ObjectSaveMode::ADD)
		//		pref->mode = Enums::ObjectSaveMode::DEFAULT;
		//	else if (pref->fromMod != manager.openedMod && pref->mode == Enums::ObjectSaveMode::DEFAULT)
		//		b = false;
		//	else if (pref->mode > Enums::ObjectSaveMode::ADD)
		//		pref->mode = Enums::ObjectSaveMode::DEFAULT;
		//	return b;
		//}
		return true;
	}

	// ##################################################
	// # METHOD NOT IN NEED OF ENABLE IF				#
	// # Methods that can be used for both pointer		#
	// # and non pointer type.							#
	// ##################################################

	Core::String getObjectTypeAsString(const Enums::ObjectType& objectType) const
	{
		return Enums::to_string(objectType) + pointerPrefixString;
	}

	template<class T>
	bool load(const Core::String & name, const Core::uuid& uuid)
	{
		td_key key(name, uuid);
		requestedMap[key] = loadInternal<T>(name, uuid);
		return true;
	}

	template<class T>
	std::unique_ptr<Interfaces::IRequestable> loadInternal(const Core::String & name, const Core::uuid& uuid)
	{
		std::unique_ptr<Interfaces::IRequestable> t;
		if (name == "EMPTY" && uuid.is_nil() || name == Core::Builtin && uuid.is_nil())
			return t;
		if (!requestFromDatabase<T>(t, name, uuid))
			Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Requestor was unable to request [" + name + ", " + uuid.to_string() + "] from database.", __FILE__, __LINE__);
		return t;
	}

	template<class T>
	inline bool requestFromDatabase(std::unique_ptr<Interfaces::IRequestable>& _t, const Core::String& modName, const Core::uuid & uuid) const
	{
		bool found = false;
		bool init = true;
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
				cereal::BinaryInputArchive loadArchive(database);
				{
					while (!eof)
					{
						ar(ind);
						Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loaded object from index file: " + ind.ID.to_string());

						if (ind.typeId == Interfaces::Trait<T>::typeId && init && ind.ID != uuid)
						{
							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading first found object to initialize polymorphic type. file.tellp " + std::to_string(ind.row));
							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading first found object to initialize polymorphic type. objectType " + getObjectTypeAsString(ind.type));
							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading first found object to initialize polymorphic type. objectTypeId " + ind.typeId.to_string());
							database.seekg(ind.row);
							loadArchive(_t);
							_t.reset();
							init = false;

						}
						else if (ind.modFile == modName && ind.ID == uuid)
						{
							Engine::GetModule<EngineModule::Logger::OneLogger>().Fine("Loading object: fileidx: " + std::to_string(ind.row));
							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading object: type: " + getObjectTypeAsString(ind.type));
							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading object: derived typename: " + Core::String(typeid(T).name()));
							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading object: derived typehash: " + std::to_string(typeid(T).hash_code()));

							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading object: before file.seekg(ind.row): file.tellg: " + std::to_string(database.tellg()));
							database.seekg(ind.row);
							
							if (std::is_base_of<Interfaces::IPatch, T>::value)
								patching = true;
							if (patching && !first_loaded)
							{
								std::unique_ptr<T> _tmp = nullptr;
								loadArchive(_tmp);
								//patch<T>(_t, _tmp);
							}
							else
							{
								try
								{
									loadArchive(_t);
									const auto& base = typeid(_t.get());
									const auto& derived = typeid(*_t.get());
									Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Finished loading object: base typename: " + Core::String(base.name()));
									Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Finished loading object: base typehash: " + std::to_string(base.hash_code()));
									Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Finished loading object: derived typename: " + Core::String(derived.name()));
									Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Finished loading object: derived typehash: " + std::to_string(derived.hash_code()));
								}
								catch (std::exception x)
								{
									Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading object failed: file.tellg: " + std::to_string(database.tellg()));
									Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Loading object failed: " + Core::String(x.what()));
								}
							}
							eof = true;
							found = true;
						}
						else if (ind.flags == Enums::ObjectFlag::EoF)
							eof = true;
						else
							Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Loading object ID didnt match the requssted ID: " + ind.ID.to_string() + " != " + uuid.to_string());

					}
				}
			}
			else
				Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Requestor was unable to open archive [" + modName + "]!", __FILE__, __LINE__);
			if (found && !patching)
				return found;
		}
		return found;
	}

	std::map<Core::String, size_t> getLoadOrder() const
	{
		if (fileLoadOrder.size() == 0)
			return Engine::GetModule<ModLoader>().loadOrder;
		return fileLoadOrder;
	}

public:

	std::map<Core::String, size_t> fileLoadOrder;

	// ##################################################
	// # INITIALIZERS									#
	// ##################################################

	RequestorV2(const Core::String& loadDirectory = "Data\\", const std::map<Core::String, size_t>& loadOrder = {}) :
		loadDirectory(loadDirectory), fileLoadOrder(loadOrder)
	{
	}

	~RequestorV2()
	{
		clear();
	}

	RequestorV2(const RequestorV2& copy) : RequestorV2(copy.loadDirectory,  copy.fileLoadOrder)
	{
		//requestedMap = copy.requestedMap;
	}

	RequestorV2& RequestorV2::operator=(const RequestorV2& right)
	{
		if (this == &right)
			return *this;
		loadDirectory = right.loadDirectory;
		fileLoadOrder = right.fileLoadOrder;
		//requestedMap = right.requestedMap;
		return *this;
	}

	// ##################################################
	// # PUBLIC METHODS									#
	// ##################################################

#if defined(_EDITOR_) || defined(_UNITTESTS_) || TRUE
	template<class T>
	inline bool add(T* ptr)
	{
		const Core::String name = ptr->fromMod;
		const Core::uuid uuid = ptr->ID;
		td_key key(name, uuid);

		if (requestedMap.find(key) != requestedMap.end())
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Requestor<" + getObjectTypeAsString(ptr->objectType) + "> - Object from mod " + name + " and ID " + uuid.to_string() + " already exists!", __FILE__, __LINE__);
			return false;
		}
		Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Requestor<" + getObjectTypeAsString(ptr->objectType) + "> - Object from mod " + name + " and ID " + uuid.to_string() + " added.", __FILE__, __LINE__);
		requestedMap[key] = std::unique_ptr<Interfaces::IRequestable>(ptr);
		return true;
	}

#endif

	inline void clear()
	{
		Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Unloading object using clear from Requestor it is still possible it has uses,"
			"this is dangerous and can lead to undefined behaviour if any references or pointers are used.", __FILE__, __LINE__);
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

	inline std::vector<std::pair<Core::String, Core::uuid>> listAllObjectKeys(const Enums::ObjectType& objectType) const
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
				Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Requestor was unable to open index file [" + var.first + ".index]!", __FILE__, __LINE__);
		}
		return listofall;
	}
	
	template<class T>
	inline T* requestUniqueInstancePtr(const ModFileUUIDHelper& modFile)
	{
		return (T*) loadInternal<T>(modFile.name, modFile.uuid).release();
	}

	template<class T>
	inline std::shared_ptr<T> requestShared(const ModFileUUIDHelper& modFile)
	{
		return std::shared_ptr<T>((T*)loadInternal<T>(modFile.name, modFile.uuid).release());
	}

	template<class T>
	inline T requestUniqueInstance(const ModFileUUIDHelper& modFile)
	{
		T* t = request<T>(modFile);
		if(t)
			return T(*t);
		Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Unable to request object from data file: [" + modFile.name + ", " + modFile.uuid.to_string() + "], returning default", __FILE__, __LINE__);
		return T();
	}

	template<class Ty>
	inline Ty* request(const ModFileUUIDHelper& modfile)
	{
		Interfaces::IRequestable* requested = request<Ty>(modfile.name, modfile.uuid);
		if (requested && requested->getTrait().hasTypeId(Interfaces::Trait<Ty>::typeId))
			return (Ty*)requested;
		return nullptr;
	}

	template <class T>
	inline Interfaces::IRequestable* request(const Core::String & name, const Core::uuid& uuid)
	{
		td_key empty = { "EMPTY", Core::uuid::nil() };
		td_map::iterator it;
		bool found = false;
		if (!name.empty())
		{
			it = requestedMap.find({ name, uuid });

			if (it != requestedMap.end())
				found = true;
			else if (!found && load<T>(name, uuid))
			{
				it = requestedMap.find({ name, uuid });
				found = true;
			}
		}

		if (!found)
		{
			return nullptr;
		}
		return it->second.get();
	}

	inline void requestRemoval(const Core::String & name, const Core::uuid& uuid)
	{
		td_map::iterator it = requestedMap.find({ name, uuid });
		if (it != requestedMap.end())
		{
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
			ind.type = it->second->objectType;
			ind.typeId = it->second->getTrait().typeId;
			ind.modFile = it->second->fromMod;
			ind.row = file.tellp();
	
			if (saveIfMode(it->second))
			{
				Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Saving object: uuid: " + ind.ID.to_string());
				Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Saving object: fileidx: " + std::to_string(ind.row));
				Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Saving object: type: " + getObjectTypeAsString(ind.type));
				Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Saving object: typeId: " + ind.typeId.to_string());
				indexAr(ind);
				try
				{
					mainAr(it->second);
					Engine::GetModule<EngineModule::Logger::OneLogger>().Debug("Saving object finished: fileidx: " + std::to_string(file.tellp()));
				}
				catch (std::exception x)
				{
					Engine::GetModule<EngineModule::Logger::OneLogger>().Error(x.what());
				}
			}
		}
	}

};

#endif