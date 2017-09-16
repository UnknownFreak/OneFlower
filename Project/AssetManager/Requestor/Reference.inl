#include "Requestor.hpp"
#include "Reference.hpp"

template<typename T>
inline Reference<T>::Reference(const Core::String name, const size_t Id, Requester<T>* const requester) : name(name), ID(Id), useCount(0), requester(requester)
{
	reload();
}

template<class T>
inline Reference<T>::~Reference()
{
	delete_if_pointer();
}

template<class T>
template<typename I>
inline typename std::enable_if<std::is_pointer<I>::value>::type Reference<T>::delete_if_pointer()
{
#ifdef _EDITOR_
	if (myRef)
	{
		delete myRef;
		myRef = nullptr;
	}
#else
	if(myRef.valid())
		delete myRef.get();
#endif

}

template<class T>
template<typename I>
inline typename std::enable_if<!std::is_pointer<I>::value>::type Reference<T>::delete_if_pointer()
{
	Logger::Info("Delete if pointer with non pointer type. Doing nothing");
}

template<class T>
template<class I>
inline typename std::enable_if<std::is_pointer<I>::value>::type Reference<T>::set_to_null_if_pointer()
{
#ifdef _EDITOR_
	myRef = nullptr;
#endif
}

template<class T>
template<class I>
inline typename std::enable_if<!std::is_pointer<I>::value>::type Reference<T>::set_to_null_if_pointer()
{
	Logger::Info("set to null if pointer with non pointer type. Doing nothing");
}

template<class T>
inline void Reference<T>::unload()
{
	requester->unload(name, ID);
}

#ifdef _EDITOR_
template<class T>
inline Reference<T>::Reference(const Core::String name, const size_t Id, Requester<T>* const requester, const T& objectToSet) : name(name), ID(Id), requester(requester), myRef(T(objectToSet)), useCount(0)
{
}
#endif

template<typename T>
inline Reference<T>::Reference(const Reference& copy) : name(copy.name), ID(copy.ID), useCount(copy.useCount), requester(copy.requester), myRef(copy.myRef)
{

}

template<typename T>
inline T& Reference<T>::getReferenced()
{
#ifdef _EDITOR_
	return myRef;
#else
	return myRef.get();
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
	myRef = future;
}
#endif

template<typename T>
inline void Reference<T>::reload()
{
	myRef = requester->loadAsync(name, ID);
}