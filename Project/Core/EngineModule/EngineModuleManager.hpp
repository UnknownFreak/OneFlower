#ifndef EngineResourceManager_HPP
#define EngineResourceManager_HPP

#include <map>
#include "IEngineModule.hpp"

class EngineModuleManager
{
	friend class BaseEngineModule;
	static EngineModuleManager* m_engineResourceManager;

	~EngineModuleManager();

		
	std::map<ResourceType, BaseEngineModule* > componentMap;

	template<class T>
	T* Create_T()
	{
		BaseEngineModule* t = new T();
		componentMap.insert({ t->getType(), t });
		return (T*)t;
	}

public:
	template<class T_S>
	T_S& GetResource()
	{
		std::map<ResourceType, BaseEngineModule*>::iterator it;
		it = componentMap.find(IEngineResource<T_S>::type);

		if (it != componentMap.end())
			return 	(T_S&)*it->second;
		else
			return (T_S&)*Create_T<T_S>();
	}

	static EngineModuleManager& get();
	static void deconstruct();


};

namespace Engine
{
	template<class T>
	inline T& GetModule()
	{
		return EngineModuleManager::get().GetResource<T>();
	}
	inline void Dispose() {
		EngineModuleManager::deconstruct();
	}
}

#endif
