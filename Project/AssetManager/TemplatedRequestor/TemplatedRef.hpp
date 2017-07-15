#ifndef TEMPLATEDREF_HPP
#define TEMPLATEDREF_HPP

#include <Core/String.hpp>
#ifndef _EDITOR_
#include<future>
#endif

//#include "TemplatedRequestor.hpp"

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

	size_t useCount;
	Core::String name;
	size_t ID;

	friend class Requester<T>;

	Requester<T> & requester;

	Reference(Core::String name, size_t Id, Requester<T>& requester);

public:

#ifdef _EDITOR_
	// This should only be used by the editor as this will force create the referenced object without requesting it from file.
	Reference(Core::String name, size_t Id, Requester<T>& requester, T objectToSet);
#endif

	Reference(const Reference& copy);

	T& getReferenced() const;
	const bool isReady() const;
#ifdef _EDITOR_
	void setNewFuture(T future);
#else
	void setNewFuture(std::shared_future<T> future);
#endif

	void reload();

};

#include "TemplatedRef.inl"

#endif





//void TextureRef::reloadTexture()
//{
//	myTexture = Engine::Textureloader.loadTextureAsync(name);
//}
//
//