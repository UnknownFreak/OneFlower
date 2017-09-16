#ifndef TEMPLATEDREF_HPP
#define TEMPLATEDREF_HPP

#include <Core/String.hpp>
#ifndef _EDITOR_
#include<future>
#endif

template<class T>
class Requester;

template<class T>
class Reference
{
#ifdef _EDITOR_
	T myRef;
#else
	std::shared_future<T> myRef;
#endif

	Core::String name;
	size_t ID;

	friend class Requester<T>;

	Requester<T>* requester;

	Reference(const Core::String name, const size_t Id, Requester<T>* const requester);

	size_t useCount;

	void unload();

	template <class I = T>
	typename std::enable_if<std::is_pointer<I>::value>::type
		delete_if_pointer();

	template <class I = T>
	typename std::enable_if<!std::is_pointer<I>::value>::type
		delete_if_pointer();

	template <class I = T>
	typename std::enable_if<std::is_pointer<I>::value>::type
		set_to_null_if_pointer();

	template <class I = T>
	typename std::enable_if<!std::is_pointer<I>::value>::type
		set_to_null_if_pointer();

public:
	~Reference();

#ifdef _EDITOR_
	// This should only be used by the editor as this will force create the referenced object without requesting it from file.
	Reference(const Core::String name, const size_t Id, Requester<T>* const requester, const T& objectToSet);
#endif

	Reference(const Reference& copy);

	T& getReferenced();

	const bool isValid() const;
#ifdef _EDITOR_
	void setNewFuture(const T future);
#else
	void setNewFuture(const std::shared_future<T> future);
#endif

	void reload();

};

#include "Reference.inl"

#endif