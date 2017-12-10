#ifndef EngineResourceManager_HPP
#define EngineResourceManager_HPP

#include <map>
#include "IEngineResource.hpp"

class EngineResourceManager
{
	friend class BaseEngineResource;
	static EngineResourceManager* m_engineResourceManager;

	~EngineResourceManager();

		
	std::map<ResourceType, BaseEngineResource* > componentMap;

	template<class T>
	T* Create_T()
	{
		BaseEngineResource* t = new T();
		componentMap.insert({ t->getType(), t });
		return (T*)t;
	}

public:
	template<class T_S>
	T_S& GetResource()
	{
		std::map<ResourceType, BaseEngineResource*>::iterator it;
		it = componentMap.find(IEngineResource<T_S>::type);

		if (it != componentMap.end())
			return 	(T_S&)*it->second;
		else
			return (T_S&)*Create_T<T_S>();
	}

	static EngineResourceManager& get();
	static void deconstruct();


};

namespace Engine
{
	template<class T>
	inline T& Get()
	{
		return EngineResourceManager::get().GetResource<T>();
	}
	inline void Dispose() {
		EngineResourceManager::deconstruct();
	}
}

#endif
