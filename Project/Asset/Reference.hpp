//#ifndef REFERENCE_HPP
//#define REFERENCE_HPP
//
//#ifndef _EDITOR_
//#include<future>
//#endif
//
//#include <Core/String.hpp>
//
//template<class T>
//class Requestor;
//
//template<class T>
//class Reference
//{
//	// ##############################################
//	// # PRIVATE VARIABLES							#
//	// ##############################################
//
//#ifdef _EDITOR_
//	T myRef;
//#else
//	std::shared_future<T> myRef;
//#endif
//
//	Core::String name;
//
//	Requestor<T>* requester;
//
//	bool skipUnload = false;
//	size_t ID;
//
//	// ##############################################
//	// # ENABLE IF METHODS 							#
//	// ##############################################
//
//	void delete_if_pointer(std::true_type);
//	void delete_if_pointer(std::false_type);
//
//public:
//
//	// ##############################################
//	// # PUBLIC VARIABLES							#
//	// ##############################################
//
//	size_t useCount;
//
//	// ##############################################
//	// # INITIALIZERS								#
//	// ##############################################
//
//
//#if defined(_EDITOR_) || defined(_UNITTESTS_)
//	Reference(const Core::String name, const size_t Id, Requestor<T>* const requester, const T& objectToSet);
//#endif
//
//	Reference(const Core::String name, const size_t Id, Requestor<T>* const requester);
//
//	Reference(const Reference& copy);
//
//	~Reference();
//	
//	// ##############################################
//	// # METHODS									#
//	// ##############################################
//
//	const size_t getUseCount()
//	{
//		return useCount;
//	}
//
//	T& getReferenced();
//
//	//Get a unique T not managed by the Reference.
//	template <class I = T>
//	typename std::enable_if<std::is_pointer<I>::value, typename std::remove_pointer<I>::type>::type
//		getUnique();
//
//	//Get a unique T not managed by the Reference.
//	template <class I = T>
//	typename std::enable_if<!std::is_pointer<I>::value, I>::type
//		getUnique();
//
//	const bool isValid() const;
//
//#ifdef _EDITOR_
//	void setNewFuture(const T future);
//#else
//	void setNewFuture(const std::shared_future<T> future);
//#endif
//
//	void reload();
//
//	void unload();
//
//};
//
//#include "Reference.inl"
//
//#endif