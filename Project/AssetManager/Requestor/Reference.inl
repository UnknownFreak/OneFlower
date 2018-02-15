#include "Requestor.hpp"
#include "Reference.hpp"
#include <Logger\Logger.hpp>


// ##############################################
// # INITIALIZERS								#
// ##############################################

template<typename T>
inline Reference<T>::Reference(const Core::String name, const size_t Id, Requestor<T>* const requester) : name(name), ID(Id), useCount(0), requester(requester)
{
	reload();
}

#if defined(_EDITOR_) || defined(_UNITTESTS_)
template<class T>
inline Reference<T>::Reference(const Core::String name, const size_t Id, Requestor<T>* const requester, const T& objectToSet) : name(name), ID(Id), requester(requester),
#ifdef _EDITOR_
myRef(T(objectToSet))
#else
myRef(std::async(std::launch::async, [this](T object) -> T {return object; }, objectToSet))
#endif
, useCount(0), skipUnload(true)
{
}

#endif

template<typename T>
inline Reference<T>::Reference(const Reference& copy) : name(copy.name), ID(copy.ID), useCount(copy.useCount), requester(copy.requester), myRef(copy.myRef), skipUnload(copy.skipUnload)
{
}

template<class T>
inline Reference<T>::~Reference()
{
	delete_if_pointer(std::is_pointer<T>());
}

// ##############################################
// # ENABLE IF METHODS							#
// ##############################################


template<class T> 
inline void Reference<T>::delete_if_pointer(std::true_type)
{
#ifdef _EDITOR_
	if (myRef)
	{
		delete myRef;
		myRef = nullptr;
	}
#else
	if (myRef.valid())
		delete myRef.get();
#endif
}

template<class T>
inline void Reference<T>::delete_if_pointer(std::false_type)
{
	Engine::Get<OneLogger>().Info("Delete if pointer with non pointer type. Doing nothing.", __FILE__, __LINE__);
}

template<class T> template<class I>
inline typename std::enable_if<std::is_pointer<I>::value, typename std::remove_pointer<I>::type>::type Reference<T>::getUnique()
{
#ifdef _EDITOR_
	return std::remove_pointer<I>::type(*myRef);
#else
	if(myRef.valid())
		return std::remove_pointer<I>::type(*myRef.get());
#endif
	throw std::runtime_error("Unable to get unique!");
}

template<class T> template<class I>
inline typename std::enable_if<!std::is_pointer<I>::value, I>::type Reference<T>::getUnique()
{
#ifdef _EDITOR_
	return T(myRef);
#else
	if (myRef.valid())
		return T(myRef.get());
#endif
	throw std::runtime_error("Unable to get unique!");
}

// ##############################################
// # REGULAR METHODS							#
// ##############################################

template<class T>
inline void Reference<T>::unload()
{
	if (skipUnload == false)
		requester->unload(name, ID);
}

template<typename T>
inline T& Reference<T>::getReferenced()
{
#ifdef _EDITOR_
	return myRef;
#else
	return (T&)myRef.get();
#endif
}

template<typename T>
inline const bool Reference<T>::isValid() const
{
#ifdef _EDITOR_
	return true;
#else
	return myRef.valid();
#endif
}

#ifdef _EDITOR_
template<typename T>
inline void Reference<T>::setNewFuture(const T future)
{
	delete_if_pointer();
	myRef = future;
}
#else
template<typename T>
inline void Reference<T>::setNewFuture(const std::shared_future<T> future)
{
	delete_if_pointer(std::is_pointer<T>());
	myRef = future;
}
#endif

template<typename T>
inline void Reference<T>::reload()
{
	myRef = requester->loadAsync(name, ID);
}