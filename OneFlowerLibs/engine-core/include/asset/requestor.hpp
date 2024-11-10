#ifndef REQUESTOR_HPP
#define REQUESTOR_HPP

#include <concepts>
#include <fstream>
#include <functional>
#include <unordered_map>

#include <filesystem>

#include <utils/common/String.hpp>
#include <logger/Logger.hpp>

#include <asset/assetIndex.hpp>
#include <asset/header.hpp>
#include <asset/assetId.hpp>

#include <asset/iAsset.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal\archives\binary.hpp>

namespace of::asset
{
	
	class Requestor
	{

		class ArchiveFactory
		{
			std::unordered_map<common::uuid, std::function<void(const AssetIndex&)>> helpers;

			Requestor* ref;

		public:

			ArchiveFactory(Requestor* ref) : ref(ref) {};

			inline void OnLoadingRequested(const AssetIndex& index)
			{
				helpers[index.typeId](index);
			}

			inline void registerDefaults(std::vector<std::pair<common::uuid, std::function<void(const AssetIndex&)>>>& vector)
			{
				for (auto& i : vector)
				{
					helpers[i.first] = i.second;
				}
			}

			void registerCustom(const common::uuid& uuid, const std::function<void(const AssetIndex&)>& func) // if custom dllmods ever become a thing
			{
				helpers[uuid] = func;
			}
		};

		// ##################################################
		// # VARIABLE SECTION								#
		// ##################################################

	protected:
		typedef std::unordered_map<AssetId, std::unique_ptr<IAsset>> td_map;

		td_map requestedMap;

		std::filesystem::path loadDirectory;
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

		bool saveIfMode(const std::unique_ptr<IAsset>& pref, const Header& header) const
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
			return false;
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
		bool load(const AssetId& modFile)
		{
			requestedMap[modFile] = loadInternal<T>(modFile);
			return true;
		}

		template<class T>
		std::unique_ptr<IAsset> loadInternal(const AssetId& modFile)
		{
			std::unique_ptr<IAsset> t;
			if (modFile.name == "EMPTY" && modFile.uuid.is_nil() || modFile.name == common::Builtin && modFile.uuid.is_nil())
				return t;
			if (!requestFromDatabase<T>(t, modFile.name, modFile.uuid))
			{
				auto& logger = of::logger::get().getLogger("Requestor");
				logger.Error("Requestor was unable to request [" + modFile.operator()() + "] from database.", logger.fileInfo(__FILE__, __LINE__));
			}
			return t;
		}

		template<class T>
		inline bool requestFromDatabase(std::unique_ptr<IAsset>& _t, const common::String& modName, const common::uuid & uuid) const
		{
			bool found = false;
			bool init = true;
			bool first_loaded = false;
			bool patching = false;
			auto& logger = of::logger::get().getLogger("Requestor");
			for(auto & var : getLoadOrder())
			{
				logger.Debug("---------------------------------------------------------------------------------------");
				logger.Debug("Loading from archive file: " + var);
				bool eof = false;
				AssetIndex ind;
				auto indexFileName = var + ".index";
				std::ifstream index(loadDirectory / indexFileName, std::ios::binary);
				std::ifstream database(loadDirectory / var, std::ios::binary);
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
								logger.Fine("Loading object: AssetIdx: " + std::to_string(ind.row));
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

		const std::vector<common::String>& getLoadOrder() const
		{
			return modLoadOrder;
		}

	public:

		ArchiveFactory factory;
		const std::vector<of::common::String>& modLoadOrder;

		// ##################################################
		// # INITIALIZERS									#
		// ##################################################

		Requestor(const std::filesystem::path& loadDirectory, const std::vector<of::common::String>& loadOrder) :
			loadDirectory(loadDirectory), modLoadOrder(loadOrder), factory(this)
		{
		}

		~Requestor()
		{
			clear();
		}

		Requestor& operator=(const Requestor& right) = delete;

		// ##################################################
		// # PUBLIC METHODS									#
		// ##################################################

		template<class T>
		requires std::derived_from<T, IAsset>
		inline bool add(T* ptr)
		{
			AssetId key(ptr->fromMod, ptr->ID);
			auto& logger = of::logger::get().getLogger("Requestor");
			if (requestedMap.find(key) != requestedMap.end())
			{
				if (requestedMap[key].operator bool())
				{
					logger.Warning(getObjectTypeAsString(ptr->objectType) + " - Object from mod " + key.operator()() + " already exists!", logger.fileInfo(__FILE__, __LINE__));
					return false;
				}
			}
			logger.Info(getObjectTypeAsString(ptr->objectType) + " - Object from mod " + key.operator()() + " added.", logger.fileInfo(__FILE__, __LINE__));
			requestedMap[key] = std::unique_ptr<IAsset>(ptr);
			return true;
		}

		inline void clear()
		{
			auto& logger = of::logger::get().getLogger("Requestor");
			logger.Warning("Unloading object using clear from Requestor it is still possible it has uses,"
				"this is dangerous and can lead to undefined behaviour if any references or pointers are used.", logger.fileInfo(__FILE__, __LINE__));
			requestedMap.clear();
		}


		inline void editorLoadAll()
		{
			auto& logger = of::logger::get().getLogger("Requestor");
			clear();
			for(const common::String& var : getLoadOrder())
			{
				bool eof = false;
				AssetIndex ind;
				std::ifstream index(loadDirectory / (var + ".index"), std::ios::binary);
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
								logger.Info("Requestor loaded from ["+ var +"] total size is now: " + std::to_string(requestedMap.size()) + " objects", logger.fileInfo(__FILE__, __LINE__));
							}
						}
					}
				}
				else
					logger.Error("Requestor unable to open index file [" + var + ".index]!", logger.fileInfo(__FILE__, __LINE__));
				index.close();
			}
		}

		inline td_map& getLoadedMap()
		{
			return requestedMap;
		}

		inline bool editorKeyExists(const AssetId& modFile) const
		{
			return requestedMap.contains(modFile);
		}

		inline common::String editorGetObjectName(const AssetId& modFile)
		{
			if (editorKeyExists(modFile))
			{
				auto& ptr = requestedMap[modFile];
				return ptr->getName();
			}
			of::logger::get().getLogger("Requestor").Warning("Tried to get name of object, but object does not exist!");
			return "";
		}

		inline std::vector<AssetId> listAllCurrentLoadedObjects(const ObjectType& objectType) const
		{
			std::vector<AssetId> listofall;
			td_map::const_iterator it = requestedMap.begin();
			td_map::const_iterator eit = requestedMap.end();
			for (it; it != eit; it++)
			{
				if (it->second.operator bool() == false)
				{
					of::logger::get().getLogger("Requestor").Error("Found empty object in requestor" + it->first.operator()());
				}
				else if(it->second.operator bool() && it->second->objectType == objectType)
					listofall.push_back(it->first);
			}
			return listofall;
		}

		inline std::vector<AssetId> listAllObjectKeys(const ObjectType& objectType) const
		{
			auto& logger = of::logger::get().getLogger("Requestor");
			std::vector<AssetId> listofall;
			for(const common::String& var : getLoadOrder())
			{
				bool eof = false;
				AssetIndex ind;
				std::ifstream index(loadDirectory / (var + ".index"), std::ios::binary);
				if (index.is_open())
				{
					cereal::BinaryInputArchive ar(index);
					{
						while (!eof)
						{
							ar(ind);
							if (ind.type == objectType)
							{
								listofall.push_back(AssetId(ind.modFile, ind.ID));
							}
							else if (ind.flags == ObjectFlag::EoF)
								eof = true;
						}
					}
				}
				else
					logger.Error("Requestor was unable to open index file [" + var + ".index]!", logger.fileInfo(__FILE__, __LINE__));
			}
			return listofall;
		}
	
		template<class T>
		requires std::derived_from<T, IAsset>
		inline T* requestUniqueInstancePtr(const AssetId& modFile)
		{
			return (T*) loadInternal<T>(modFile).release();
		}

		template<class T>
		requires std::derived_from<T, IAsset>
		inline std::shared_ptr<T> requestShared(const AssetId& modFile)
		{
			return std::shared_ptr<T>((T*)loadInternal<T>(modFile).release());
		}

		template<class T>
		requires std::derived_from<T, IAsset>
		inline T requestUniqueInstance(const AssetId& modFile)
		{
			auto& logger = of::logger::get().getLogger("Requestor");
			T* t = request<T>(modFile);
			if(t)
				return T(*t);
			logger.Warning("Unable to request object from data file: [" + modFile.name + ", " + modFile.uuid.to_string() + "], returning default", logger.fileInfo(__FILE__, __LINE__));
			return T();
		}

		template<class Ty>
		requires std::derived_from<Ty, IAsset>
		inline Ty* request(const AssetId& modfile)
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
			IAsset* requested = it->second.get();
			if (requested && requested->getTrait().hasTypeId(Trait<Ty>::typeId))
				return (Ty*)requested;
			return nullptr;
		}

		inline void requestRemoval(const AssetId& modFile)
		{
			requestedMap.erase(modFile);
		}

		inline void save(AssetIndex & ind, std::ostream & file, cereal::BinaryOutputArchive & indexAr, cereal::BinaryOutputArchive & mainAr,
			const of::asset::Header& header, const bool& skipSaveIfMode=false) const
		{
			auto& logger = of::logger::get().getLogger("Requestor");
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
					logger.Debug(" AssetIdx: " + std::to_string(ind.row));
					logger.Debug(" type: " + getObjectTypeAsString(ind.type));
					logger.Debug(" typeId: " + ind.typeId.to_string());
					indexAr(ind);
					try
					{
						mainAr(it->second);
						logger.Debug("Saving object finished: AssetIdx: " + std::to_string(file.tellp()));
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