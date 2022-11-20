#ifndef REQUESTOR_HPP
#define REQUESTOR_HPP

//#include "RegisterRTTI.hpp"

#include <concepts>
#include <fstream>
#include <functional>
#include <unordered_map>


#include <utils/common/String.hpp>
#include <module/logger/OneLogger.hpp>

#include <Module/ModuleManager.hpp>

#include <File/Archive/EntityIndex.hpp>
#include <File/Header.hpp>
#include <File/Loader.hpp>
#include <File/FileId.hpp>

//#include <Interfaces/IPatch.hpp>
#include <file/archive/Requestable.hpp>


#include <cereal\archives\binary.hpp>

namespace of::file::archive
{
	
	class Requestor
	{

		class ArchiveFactory
		{
			std::unordered_map<common::uuid, std::function<void(const EntityIndex&)>> helpers;

			Requestor* ref;

		public:

			ArchiveFactory(Requestor* ref) : ref(ref) {};

			inline void OnLoadingRequested(const EntityIndex& index)
			{
				helpers[index.typeId](index);
			}
			inline void registerDefaults()
			{
				/*
				helpers[Trait<::Asset::Resource::DialogTree>::typeId] = [this](const EntityIndex& index)
				{
					ref->request<::Asset::Resource::DialogTree>(FileId(FileId(index.modFile, index.ID)));
				};
				helpers[Trait<::Asset::Resource::Prefab>::typeId] = [this](const EntityIndex& index) {
					ref->request<::Asset::Resource::Prefab>(FileId(index.modFile, index.ID));
				};
				helpers[Trait<File::Asset::Resource::Template::WorldInstance>::typeId] = [this](const EntityIndex& index) {
					ref->request<File::Asset::Resource::Template::WorldInstance>(FileId(index.modFile, index.ID));
				};
				helpers[Trait<File::Asset::Resource::Template::TileChunk>::typeId] = [this](const EntityIndex& index) {
					ref->request<File::Asset::Resource::Template::TileChunk>(FileId(index.modFile, index.ID));
				};
				helpers[Trait<File::Asset::Resource::Template::ColliderChunk>::typeId] = [this](const EntityIndex& index) {
					ref->request<File::Asset::Resource::Template::ColliderChunk>(FileId(index.modFile, index.ID));
				};
				helpers[Trait<PrimitiveSaveable<common::String>>::typeId] = [this](const EntityIndex& index) {
					ref->request<PrimitiveSaveable<common::String>>(FileId(index.modFile, index.ID));
				};
				helpers[Trait<Combat::Element>::typeId] = [this](const EntityIndex& index) {
					ref->request<Combat::Element>(FileId(index.modFile, index.ID));
				};
				helpers[Trait<Combat::Effect>::typeId] = [this](const EntityIndex& index) {
					ref->request<Combat::Effect>(FileId(index.modFile, index.ID));
				};
				helpers[Trait<Combat::Skill>::typeId] = [this](const EntityIndex& index) {
					ref->request<Combat::Skill>(FileId(index.modFile, index.ID));
				};
				//helpers[Interfaces::Trait<Combat::EffectProperty>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Combat::EffectProperty>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Combat::DamageEffect>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Combat::DamageEffect>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Combat::BarrierEffect>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Combat::BarrierEffect>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Combat::VisualEffect>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Combat::VisualEffect>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Combat::ModifierEffect>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Combat::ModifierEffect>(FileId(index.modFile, index.ID));
				//};
				helpers[Trait<Questing::Quest>::typeId] = [this](const EntityIndex& index) {
					ref->request<Questing::Quest>(FileId(index.modFile, index.ID));
				};
				//helpers[Interfaces::Trait<Questing::AOrBObjective>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Questing::AOrBObjective>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Questing::CollectItemObjective>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Questing::CollectItemObjective>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Questing::DefeatEnemyObjective>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Questing::DefeatEnemyObjective>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Questing::DefendObjective>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Questing::DefendObjective>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Questing::DuelObjective>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Questing::DuelObjective>(FileId(index.modFile, index.ID));
				//};
				//helpers[Interfaces::Trait<Questing::ListObjective>::typeId] = [this](const EntityIndex& index) {
				//	ref->request<Questing::ListObjective>(FileId(index.modFile, index.ID));
				//};
				*/
			}

			void registerCustom(const common::uuid& uuid, const std::function<void(const EntityIndex&)>& func) // if custom dllmods ever become a thing
			{
				helpers[uuid] = func;
			}
		};

		// ##################################################
		// # VARIABLE SECTION								#
		// ##################################################

	protected:
		typedef std::unordered_map<FileId, std::unique_ptr<Requestable>> td_map;

		td_map requestedMap;

		common::String loadDirectory;
		common::String pointerPrefixString;

	private:
	
		// ##################################################
		// # ENABLE IF SECTION PRIVATE						#
		// # Enables different functions for pointer type	#
		// # and non pointer type.							#
		// # These functions should be as short as possible.#
		// ##################################################
	

		//template <class In>
		//inline typename std::enable_if < std::is_base_of<Interfaces::IPatch, In>::value>::type patch(In& toPatch, const In& patchObject) const
		//{
		//	toPatch.Patch(patchObject);
		//}
		//
		//template <class In>
		//inline typename std::enable_if < !std::is_base_of<Interfaces::IPatch, In>::value>::type patch(In&, In&) const
		//{
		//}

		bool saveIfMode(const std::unique_ptr<Requestable>& pref, const Header& header) const
		{
			if (pref->mode != ObjectSaveMode::REMOVE)
			{
				bool b = true;
				if (pref->fromMod == header.name && pref->mode == ObjectSaveMode::EDIT)
					pref->mode = ObjectSaveMode::DEFAULT;
				else if (pref->fromMod == header.name && pref->mode == ObjectSaveMode::ADD)
					pref->mode = ObjectSaveMode::DEFAULT;
				else if (pref->fromMod != header.name && pref->mode == ObjectSaveMode::DEFAULT)
					b = false;
				else if (pref->mode > ObjectSaveMode::ADD)
					pref->mode = ObjectSaveMode::DEFAULT;
				return b;
			}
			return true;
		}

		// ##################################################
		// # METHOD NOT IN NEED OF ENABLE IF				#
		// # Methods that can be used for both pointer		#
		// # and non pointer type.							#
		// ##################################################

		common::String getObjectTypeAsString(const ObjectType& objectType) const
		{
			return to_string(objectType) + pointerPrefixString;
		}

		template<class T>
		bool load(const FileId& modFile)
		{
			requestedMap[modFile] = loadInternal<T>(modFile);
			return true;
		}

		template<class T>
		std::unique_ptr<Requestable> loadInternal(const FileId& modFile)
		{
			std::unique_ptr<Requestable> t;
			if (modFile.name == "EMPTY" && modFile.uuid.is_nil() || modFile.name == common::Builtin && modFile.uuid.is_nil())
				return t;
			if (!requestFromDatabase<T>(t, modFile.name, modFile.uuid))
			{
				auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
				logger.Error("Requestor was unable to request [" + modFile.operator()() + "] from database.", logger.fileInfo(__FILE__, __LINE__));
			}
			return t;
		}

		template<class T>
		inline bool requestFromDatabase(std::unique_ptr<Requestable>& _t, const common::String& modName, const common::uuid & uuid) const
		{
			bool found = false;
			bool init = true;
			bool first_loaded = false;
			bool patching = false;
			auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
			for(std::pair<std::string, size_t> var : getLoadOrder())
			{
				logger.Debug("---------------------------------------------------------------------------------------");
				logger.Debug("Loading from archive file: " + var.first);
				bool eof = false;
				EntityIndex ind;
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
							logger.Debug("Loaded object from index file: " + ind.ID.to_string());

							if (ind.typeId == Trait<T>::typeId && init && (ind.ID == uuid && ind.modFile == modName) == false)
							{
								logger.Debug("Loading first found object to initialize polymorphic type. file.tellp " + std::to_string(ind.row));
								logger.Debug("Loading first found object to initialize polymorphic type. objectType " + getObjectTypeAsString(ind.type));
								logger.Debug("Loading first found object to initialize polymorphic type. objectTypeId " + ind.typeId.to_string());
								database.seekg(ind.row);
								try
								{
									loadArchive(_t);
								}
								catch (std::exception x)
								{
									logger.Debug("Loading object failed: file.tellg: " + std::to_string(database.tellg()));
									logger.Error("Loading object failed: " + common::String(x.what()));
								}
								_t.reset();
								init = false;

							}
							else if (ind.modFile == modName && ind.ID == uuid)
							{
								logger.Fine("Loading object: fileidx: " + std::to_string(ind.row));
								logger.Debug("Loading object: type: " + getObjectTypeAsString(ind.type));
								logger.Debug("Loading object: derived typename: " + common::String(typeid(T).name()));
								logger.Debug("Loading object: derived typehash: " + std::to_string(typeid(T).hash_code()));

								logger.Debug("Loading object: before file.seekg(ind.row): file.tellg: " + std::to_string(database.tellg()));
								database.seekg(ind.row);
								logger.Debug("Loading object: after file.seekg(ind.row): file.tellg: " + std::to_string(database.tellg()));

								//if (std::is_base_of<Interfaces::IPatch, T>::value)
								//	patching = true;
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
										logger.Debug("Finished loading object: base typename: " + common::String(base.name()));
										logger.Debug("Finished loading object: base typehash: " + std::to_string(base.hash_code()));
										logger.Debug("Finished loading object: derived typename: " + common::String(derived.name()));
										logger.Debug("Finished loading object: derived typehash: " + std::to_string(derived.hash_code()));
									}
									catch (std::exception x)
									{
										logger.Debug("Loading object failed: file.tellg: " + std::to_string(database.tellg()));
										logger.Error("Loading object failed: " + common::String(x.what()));
										logger.Error(" typeid: " + Trait<T>::typeId.to_string());
										logger.Error(" index.typeid: " + ind.typeId.to_string());
										logger.Error(" index.id: " + ind.ID.to_string());
										logger.Error(" arg: id " + uuid.to_string());
									}
								}
								eof = true;
								found = true;
							}
							else if (ind.flags == ObjectFlag::EoF)
								eof = true;
							else
								logger.Debug("Loading object ID didnt match the requssted ID: " + ind.ID.to_string() + " != " + uuid.to_string());

						}
					}
				}
				else
					logger.Error("Requestor was unable to open archive [" + modName + "]!", logger.fileInfo(__FILE__, __LINE__));
				if (found && !patching)
					return found;
			}
			return found;
		}

		std::map<common::String, size_t> getLoadOrder() const
		{
			if (fileLoadOrder.size() == 0)
				return of::engine::GetModule<file::Loader>().loadOrder;
			return fileLoadOrder;
		}

	public:

		std::map<common::String, size_t> fileLoadOrder;
		ArchiveFactory factory;

		// ##################################################
		// # INITIALIZERS									#
		// ##################################################

		Requestor(const common::String& loadDirectory = "Data\\", const std::map<common::String, size_t>& loadOrder = {}) :
			loadDirectory(loadDirectory), fileLoadOrder(loadOrder), factory(this)
		{
			factory.registerDefaults();
		}

		~Requestor()
		{
			clear();
		}

		Requestor(const Requestor& copy) : Requestor(copy.loadDirectory,  copy.fileLoadOrder)
		{
			//requestedMap = copy.requestedMap;
		}

		Requestor& operator=(const Requestor& right)
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

		template<class T>
		requires std::derived_from<T, Requestable>
		inline bool add(T* ptr)
		{
			FileId key(ptr->fromMod, ptr->ID);
			auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
			if (requestedMap.find(key) != requestedMap.end())
			{
				if (requestedMap[key].operator bool())
				{
					logger.Warning(getObjectTypeAsString(ptr->objectType) + " - Object from mod " + key.operator()() + " already exists!", logger.fileInfo(__FILE__, __LINE__));
					return false;
				}
			}
			logger.Info(getObjectTypeAsString(ptr->objectType) + " - Object from mod " + key.operator()() + " added.", logger.fileInfo(__FILE__, __LINE__));
			requestedMap[key] = std::unique_ptr<Requestable>(ptr);
			return true;
		}

		/*
		inline void add(const ObjectType& type, const Core::String& name)
		{
			switch (type)
			{
			case ObjectType::Element: 
			{
				auto elem = new Combat::Element;
				elem->fromMod = name;
				add(elem); 
				break;
			}
			default:
				Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Requestor").Warning("Trying to add type: " + Enums::to_string(type) + ", but it does not exist in switch case, consider adding it.");
			}
		}
		**/

		inline void clear()
		{
			auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
			logger.Warning("Unloading object using clear from Requestor it is still possible it has uses,"
				"this is dangerous and can lead to undefined behaviour if any references or pointers are used.", logger.fileInfo(__FILE__, __LINE__));
			requestedMap.clear();
		}


		inline void editorLoadAll()
		{
			auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
			clear();
			for(std::pair<std::string, size_t> var : getLoadOrder())
			{
				bool eof = false;
				EntityIndex ind;
				std::ifstream index(loadDirectory + var.first + ".index", std::ios::binary);
				if (index.is_open())
				{
					cereal::BinaryInputArchive ar(index);
					{
						while (!eof)
						{
							ar(ind);
							if (ind.flags != ObjectFlag::EoF && ind.type != ObjectType::Header)
							{
								factory.OnLoadingRequested(ind);
							}
							else if (ind.flags == ObjectFlag::EoF)
							{
								eof = true;
								logger.Info("Requestor loaded from ["+ var.first +"] total size is now: " + std::to_string(requestedMap.size()) + " objects", logger.fileInfo(__FILE__, __LINE__));
							}
						}
					}
				}
				else
					logger.Error("Requestor unable to open index file [" + var.first + ".index]!", logger.fileInfo(__FILE__, __LINE__));
				index.close();
			}
		}

		inline td_map& getLoadedMap()
		{
			return requestedMap;
		}

		inline bool editorKeyExists(const FileId& modFile) const
		{
			return requestedMap.contains(modFile);
		}

		inline common::String editorGetObjectName(const FileId& modFile)
		{
			if (editorKeyExists(modFile))
			{
				auto& ptr = requestedMap[modFile];
				return ptr->getName();
			}
			of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor").Warning("Tried to get name of object, but object does not exist!");
			return "";
		}

		inline std::vector<FileId> listAllCurrentLoadedObjects(const ObjectType& objectType) const
		{
			std::vector<FileId> listofall;
			td_map::const_iterator it = requestedMap.begin();
			td_map::const_iterator eit = requestedMap.end();
			for (it; it != eit; it++)
			{
				if(it->second->objectType == objectType)
					listofall.push_back(it->first);
			}
			return listofall;
		}

		inline std::vector<FileId> listAllObjectKeys(const ObjectType& objectType) const
		{
			auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
			std::vector<FileId> listofall;
			for(std::pair<std::string, size_t> var :getLoadOrder())
			{
				bool eof = false;
				EntityIndex ind;
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
								listofall.push_back(FileId(ind.modFile, ind.ID));
							}
							else if (ind.flags == ObjectFlag::EoF)
								eof = true;
						}
					}
				}
				else
					logger.Error("Requestor was unable to open index file [" + var.first + ".index]!", logger.fileInfo(__FILE__, __LINE__));
			}
			return listofall;
		}
	
		template<class T>
		requires std::derived_from<T, Requestable>
		inline T* requestUniqueInstancePtr(const FileId& modFile)
		{
			return (T*) loadInternal<T>(modFile).release();
		}

		template<class T>
		requires std::derived_from<T, Requestable>
		inline std::shared_ptr<T> requestShared(const FileId& modFile)
		{
			return std::shared_ptr<T>((T*)loadInternal<T>(modFile).release());
		}

		template<class T>
		requires std::derived_from<T, Requestable>
		inline T requestUniqueInstance(const FileId& modFile)
		{
			auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
			T* t = request<T>(modFile);
			if(t)
				return T(*t);
			logger.Warning("Unable to request object from data file: [" + modFile.name + ", " + modFile.uuid.to_string() + "], returning default", logger.fileInfo(__FILE__, __LINE__));
			return T();
		}

		template<class Ty>
		requires std::derived_from<Ty, Requestable>
		inline Ty* request(const FileId& modfile)
		{
			td_map::iterator it;
			bool found = false;
			if (!modfile.name.empty())
			{
				it = requestedMap.find(modfile);

				if (it != requestedMap.end())
					found = true;
				else if (!found && load<Ty>(modfile))
				{
					it = requestedMap.find(modfile);
					found = true;
				}
			}

			if (!found)
			{
				return nullptr;
			}
			Requestable* requested = it->second.get();
			if (requested && requested->getTrait().hasTypeId(Trait<Ty>::typeId))
				return (Ty*)requested;
			return nullptr;
		}

		template<class Ty>
		requires std::derived_from<Ty, Requestable>
		inline Ty* request(const FileId& modfile, const bool& )
		{
			Ty* ptr = request<Ty>(modfile);
			if (!ptr)
			{
				add(new Ty());
				return request<Ty>(modfile);
			}
			return ptr;
		}

		inline void requestRemoval(const FileId& modFile)
		{
			requestedMap.erase(modFile);
		}

		inline void save(EntityIndex & ind, std::ostream & file, cereal::BinaryOutputArchive & indexAr, cereal::BinaryOutputArchive & mainAr,
			const of::file::Header& header, const bool& skipSaveIfMode=false) const
		{
			auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("Requestor");
			td_map::const_iterator it = requestedMap.begin();
			td_map::const_iterator eit = requestedMap.end();
			for (it; it != eit; it++)
			{
				ind.flags = ObjectFlag::NoFlag;
				ind.ID = it->first.uuid;
				ind.type = it->second->objectType;
				ind.typeId = it->second->getTrait().typeId;
				ind.modFile = it->second->fromMod;
				ind.row = file.tellp();
	
				if (skipSaveIfMode || saveIfMode(it->second, header))
				{
					logger.Info("Saving object: uuid: " + ind.ID.to_string());
					logger.Debug(" modfile: " + ind.modFile);
					logger.Debug(" fileidx: " + std::to_string(ind.row));
					logger.Debug(" type: " + getObjectTypeAsString(ind.type));
					logger.Debug(" typeId: " + ind.typeId.to_string());
					indexAr(ind);
					try
					{
						mainAr(it->second);
						logger.Debug("Saving object finished: fileidx: " + std::to_string(file.tellp()));
					}
					catch (const std::exception x)
					{
						logger.Error(x.what());
					}
				}
			}
		}

	};
}

#endif