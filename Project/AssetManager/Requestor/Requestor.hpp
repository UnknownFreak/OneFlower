#ifndef TEMPLATEDREQUESTOR_HPP
#define TEMPLATEDREQUESTOR_HPP

#include <fstream>

#include <cereal\archives\binary.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>

#include <memory>
#include <map>
#include <Core\String.hpp>
#include <Logger\Logger.hpp>

#include "../Database/DatabaseIndex.hpp"
#include "../IRequestable.hpp"
#include "Reference.hpp"

// Any requestable T must have these attributes:
// Default Ctor
// Copy Ctor
// Assignment Operator

template<class T>
class Requester
{
	friend class Reference<T>;

	typedef std::map<std::pair<Core::String, size_t>, Reference<T>*> td_map;
	td_map requestedMap;
	typedef std::pair<Core::String, size_t> td_key;
	const DatabaseIndex::ObjectTypeEnum objectType;

	bool requestFromDatabase(T& _t, Core::String modName, size_t uuid);
	

	const Core::String getObjectTypeAsString() const;
	

	void unload(Core::String modName, size_t uuid);
	

	const bool load(const Core::String& name, size_t uuid);


	T load_internal(const Core::String& name, size_t uuid);
	
	template <class In = T>
	inline typename std::enable_if < std::is_base_of<IRequestable, In>::value, void>::type check()
	{
		OneLogger::Info("Requester with class T was a base class of IRequestable - OK!");
	}

	template <class In = T>
	inline typename std::enable_if <!std::is_base_of<IRequestable, In>::value, void>::type check()
	{
		static_assert(false, "Class T is not a base class of IRequestable - this object will not be requestable");
	}

public:

#ifdef _EDITOR_
	bool add(T& obj);
	
#endif

#ifdef _EDITOR_
	T loadAsync(const Core::String& name, const size_t& uuid);
#else
	std::shared_future<T> loadAsync(Core::String& name, size_t uuid);
#endif

	Reference<T>*& request(const Core::String& name, const size_t uuid);

	bool requestRemoval(const Core::String& name, const size_t uuid);

public:

	void clear();

	Requester(DatabaseIndex::ObjectTypeEnum objectType);

	Requester(const Requester& copy) = delete;

#ifdef _EDITOR_
	void editorLoadAll();

	std::vector<std::pair<Core::String, size_t>> listAllCurrentLoadedObjects();

#endif

	void save(DatabaseIndex& ind,
		std::ostream& file,
		cereal::BinaryOutputArchive& indexAr,
		cereal::BinaryOutputArchive& mainAr);
};
#include "Requestor.inl"


// Any requestable T must have these attributes:
// Default Ctor
// Copy Ctor
// Assignment Operator
// when added, use the operator new to allocate object on heap as this will use pointer map. Only to use with object that require inheritence. 
// Allocated objects will automatically be decunstructed when object exist scope
template<class T>
class Requester<T*>
{
	friend class Reference<T*>;

	typedef std::map<std::pair<Core::String, size_t>, Reference<T*>*> td_map;
	td_map requestedMap;
	typedef std::pair<Core::String, size_t> td_key;
	//#define _kvp(modfile, id, this, tmp) std::pair<std::pair<std::string, size_t>, Reference<T>*>\
	//(std::pair<std::string, size_t>(modFile, id), new Reference<T>(modFile, id, this, tmp))

	const DatabaseIndex::ObjectTypeEnum objectType;

	bool requestFromDatabase(T*& _t, Core::String modName, size_t uuid);


	const Core::String getObjectTypeAsString() const;


	void unload(Core::String modName, size_t uuid);


	const bool load(const Core::String& name, size_t uuid);


	T* load_internal(const Core::String& name, size_t uuid);

	template <class In = T>
	inline typename std::enable_if < std::is_base_of<IRequestable, In>::value>::type check()
	{
	}

	template <class In = T>
	inline typename std::enable_if < ! std::is_base_of<IRequestable, In>::value>::type check()
	{
		static_assert(false, "Class T is not a base class of IRequestable - this object will not be requestable");
	}

public:

#ifdef _EDITOR_
	// Added object must be allocated via new, otherwise clear fails
	bool add(T*& obj);

#endif

#ifdef _EDITOR_
	T* loadAsync(const Core::String& name, const size_t& uuid);
#else
	std::shared_future<T> loadAsync(Core::String& name, size_t uuid);
#endif

	Reference<T*>*& request(const Core::String& name, const size_t uuid);

	// requests removal of a object with name and id, reduces it's use count by 1, if it is 0 the object get removed
	// returns true when object is removed/deleted.
	bool requestRemoval(const Core::String& name, const size_t uuid);

public:

	void clear();

	Requester(DatabaseIndex::ObjectTypeEnum objectType);

	Requester(const Requester& copy) = delete;

	~Requester();

#ifdef _EDITOR_
	void editorLoadAll();
	std::vector<std::pair<Core::String, size_t>> listAllCurrentLoadedObjects();

#endif

	void save(DatabaseIndex& ind,
		std::ostream& file,
		cereal::BinaryOutputArchive& indexAr,
		cereal::BinaryOutputArchive& mainAr);
};

#include "Requestor_ptr.inl"

#endif