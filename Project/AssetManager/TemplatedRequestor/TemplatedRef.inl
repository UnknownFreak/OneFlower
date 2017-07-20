#include "TemplatedRequestor.hpp"
#include "TemplatedRef.hpp"
template<typename T>
inline Reference<T>::Reference(const Core::String name, const size_t Id, Requester<T>* const requester) : name(name), ID(Id), useCount(0), requester(requester)
{
	reload();
}

#ifdef _EDITOR_
template<class T>
inline Reference<T>::Reference(const Core::String name, const size_t Id, Requester<T>* const requester, const T& objectToSet) : name(name), ID(Id), requester(requester), myRef(T(objectToSet))
{
}
#endif

template<typename T>
inline Reference<T>::Reference(const Reference& copy) : name(copy.name), ID(copy.ID), useCount(copy.useCount), requester(copy.requester), myRef(copy.myRef)
{
	//reload();
	//myRef = copy.myRef;
}

template<typename T>
inline const T& Reference<T>::getReferenced() const
{
#ifdef _EDITOR_
	return myRef;
#else
	return myRef.get();
#endif
}

template<typename T>
inline const bool Reference<T>::isReady() const
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