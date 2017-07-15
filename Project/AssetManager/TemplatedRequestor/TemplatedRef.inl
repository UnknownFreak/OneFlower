#include "TemplatedRequestor.hpp"
#include "TemplatedRef.hpp"
template<typename T>
inline Reference<T>::Reference(Core::String name, size_t Id, Requester<T>& requester) : name(name), ID(Id), useCount(0), requester(requester)
{
	reload()
}

#ifdef _EDITOR_
template<class T>
inline Reference<T>::Reference(Core::String name, size_t Id, Requester<T>& requester, T objectToSet) : name(name), ID(Id), requester(requester), myRef(objectToSet)
{
}
#endif

template<typename T>
inline Reference<T>::Reference(const Reference& copy) : name(copy.name), myRef(copy.myRef), ID(copy.ID), useCount(copy.useCount), requester(requester)
{

}

template<typename T>
inline T& Reference<T>::getReferenced() const
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
inline void Reference<T>::setNewFuture(T future)
{
	myRef = future;
}
#else
template<typename T>
inline void Reference<T>::setNewFuture(std::shared_future<T> future)
{
	myRef = future;
}
#endif

template<typename T>
inline void Reference<T>::reload()
{
	myRef = requester.loadAsync(name, ID);
}