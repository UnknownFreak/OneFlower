#include <Model\IModel.hpp>
#include "Requestor.hpp"

#include <SFML\System\Time.hpp>
#include <SFML\System.hpp>

template<class T>
inline bool Requester<T*>::requestFromDatabase(T *& _t, Core::String modName, size_t uuid)
{
	bool found = false;
	for each (std::pair<std::string, size_t> var in Engine::modLoadOrder.loadOrder)
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
						std::unique_ptr<T> _ptr;
						ModelLoad(_ptr);
						_t = _ptr.release();
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

template<class T>
inline const Core::String Requester<T*>::getObjectTypeAsString() const
{
	switch (objectType)
	{
	case DatabaseIndex::ObjectTypeEnum::Header:
		return "Header";
	case DatabaseIndex::ObjectTypeEnum::Zone:
		return "Zone";	
	case DatabaseIndex::ObjectTypeEnum::DBZone:
		return "DBZone";
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
		return "Unknown";
	}
}

template<class T>
inline void Requester<T*>::unload(Core::String modName, size_t uuid)
{
	td_map::iterator it = requestedMap.find({ modName, uuid });
	if (it != requestedMap.end())
	{
		delete it->second;
		it->second = nullptr;
		requestedMap.erase(it);
	}
}

template<class T>
inline const bool Requester<T*>::load(const Core::String & name, size_t uuid)
{
	td_key key(name, uuid);
	requestedMap.insert(std::make_pair(key, new Reference<T*>(name, uuid, this)));
	return true;
}

template<class T>
inline T* Requester<T*>::load_internal(const Core::String & name, size_t uuid)
{
	T* t = nullptr;
	if (name == "EMPTY" && uuid == 0)
		return t;
	if (!requestFromDatabase(t, name, uuid))
		OneLogger::Error("Requestor<" + getObjectTypeAsString() + "*> - Unable to request [" + name + ", " + std::to_string(uuid) + "] from database.", __FILE__, __LINE__);
	return t;
}

#ifdef _EDITOR_
template<class T>
inline bool Requester<T*>::add(T*& obj)
{
	const Core::String name = obj->fromMod;
	const size_t uuid = obj->ID;

	td_key key(name, uuid);

	if (requestedMap.find(key) != requestedMap.end())
	{
		OneLogger::Warning("Object with fromMod " + name + " and ID " + std::to_string(uuid) + " already exists", __FILE__, __LINE__);
		return false;
	}
	OneLogger::Info("Object with fromMod " + name + " and ID " + std::to_string(uuid) + " added.", __FILE__, __LINE__);
	
	Reference<T>* ref = new Reference<T>(name, uuid, this, obj);
	requestedMap.insert(std::make_pair(key, ref));
	return true;
}
#endif

#ifdef _EDITOR_
template<class T>
inline T* Requester<T*>::loadAsync(const Core::String& name, const size_t& uuid)
{
	T* t = load_internal(name, uuid);
	return t;
}
#else
template<class T>
std::shared_future<T*> Requester<T*>::loadAsync(Core::String& name, size_t uuid)
{
	std::shared_future<T*>tp = std::async(std::launch::async, [this](std::string name, size_t uuid) -> T* {return load_internal(name, uuid); }, name, uuid);
	return tp;
}
#endif

template<class T>
inline typename Reference<T*>*& Requester<T*>::request(const Core::String & name, const size_t uuid)
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

template<class T>
inline bool Requester<T*>::requestRemoval(const Core::String& name, const size_t uuid)
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

	bool rv = --it->second->useCount == 0;
	if (rv)
		it->second->unload();
	return rv;
}

template<class T>
inline void Requester<T*>::clear()
{
	td_map::iterator it = requestedMap.begin();
	td_map::iterator eit = requestedMap.end();

	for (; it != eit; it++)
	{
		if (it->second->useCount > 0)
			OneLogger::Warning("Unloading object from Requestor<"+getObjectTypeAsString()+"*> while it still has uses, this is dangerous and can lead to undefined behaviour", __FILE__, __LINE__);
		Reference<T*>*& pr = it->second;
		delete pr;
		pr = nullptr;
	}
	requestedMap.clear();
}

template<class T>
inline Requester<T*>::Requester(DatabaseIndex::ObjectTypeEnum objectType) : objectType(objectType)
{
	check();
}

template<class T>
inline Requester<T*>::~Requester()
{
	clear();
}

#ifdef _EDITOR_

template<class T>
inline void Requester<T*>::editorLoadAll()
{

}
//	for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
//	{
//		bool eof = false;
//		DatabaseIndex ind;
//		std::ifstream index(var.first + ".index", std::ios::binary);
//		std::ifstream database(var.first, std::ios::binary);
//		if (index.is_open())
//		{
//			cereal::BinaryInputArchive ar(index);
//			{
//				while (!eof)
//				{
//					ar(ind);
//					if (ind.type == objectType)
//					{
//						database.seekg(ind.row);
//						cereal::BinaryInputArchive loader(database);
//						std::map<std::pair<std::string, size_t>, Reference<T>>::iterator it = requestedMap.find(std::pair<std::string, size_t>(ind.modFile, ind.ID));
//						if (it != requestedMap.end())
//						{
//							// stuff exist add extra things to object.
//							loader(it->second.getReferenced());
//						}
//						else
//						{
//							T tmp;
//							loader(tmp);
//							worldmap.insert(std::pair<std::pair<std::string, size_t>, Reference<T>>
//								(std::pair<std::string, size_t>(ind.modFile, ind.ID), Reference<T>(ind.modFile, ind.ID, this, tmp)));
//						}
//					}
//					else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
//						eof = true;
//				}
//			}
//		}
//		else
//			OneLogger::Error("Unable to open Index file [" + var.first +
//				".index] in Requestor <" + getObjectTypeAsString() + ">", __FILE__, __LINE__);
//	}
//}
#endif _EDITOR_

template<class T>
inline void Requester<T*>::save(DatabaseIndex & ind, std::ostream & file, cereal::BinaryOutputArchive & indexAr, cereal::BinaryOutputArchive & mainAr)
{
	td_map::iterator it = requestedMap.begin();
	td_map::iterator eit = requestedMap.end();
	for (it; it != eit; it++)
	{
		T* pref = (T*)it->second->getReferenced();
		ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
		ind.ID = it->first.second;
		ind.type = objectType;
		ind.modFile = pref->fromMod;
		ind.row = file.tellp();
		if (pref->mode != ObjectSaveMode::REMOVE)
		{
			bool b = true;
			if (pref->fromMod == Engine::getAssetManager().openedMod && pref->mode == ObjectSaveMode::EDIT)
				pref->mode = ObjectSaveMode::DEFAULT;
			else if (pref->fromMod == Engine::getAssetManager().openedMod && pref->mode == ObjectSaveMode::ADD)
				pref->mode = ObjectSaveMode::DEFAULT;
			else if (pref->fromMod != Engine::getAssetManager().openedMod && pref->mode == ObjectSaveMode::DEFAULT)
				b = false;
			else if (pref->mode > ObjectSaveMode::ADD)
				pref->mode = ObjectSaveMode::DEFAULT;
			if (b)
			{
				indexAr(ind);
				std::unique_ptr<T> _ptr(pref);
				mainAr(_ptr);
				// release object as we do not want to de-allocate it
				_ptr.release();
			}
		}
	}
}


template<class T>
inline std::vector<std::pair<Core::String, size_t>> Requester<T*>::listAllCurrentLoadedObjects()
{
	std::vector<std::pair<Core::String, size_t>> listofall;
	td_map::iterator it = requestedMap.begin();
	td_map::iterator eit = requestedMap.end();
	for (it; it != eit; it++)
	{
		listofall.push_back(it->first);
	}
	return listofall;
}