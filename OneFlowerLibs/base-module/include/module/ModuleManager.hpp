#ifndef EngineResourceManager_HPP
#define EngineResourceManager_HPP

#include <map>
#include <module/IEngineModule.hpp>
#include <memory>

namespace OneFlower::Module
{
	class ModuleManager
	{
		friend class BaseEngineModule;
		static ModuleManager* m_engineResourceManager;

		~ModuleManager();

		std::map<EngineResourceType, std::unique_ptr<BaseEngineModule> > componentMap;

		template<class T>
		T* Create_T()
		{
			componentMap.insert({ Interface::IEngineResource<T>::type, std::make_unique<T>() });
			return (T*)componentMap[Interface::IEngineResource<T>::type].get();
		}

	public:
		template<class T_S>
		T_S& GetResource()
		{
			std::map<EngineResourceType, std::unique_ptr<BaseEngineModule>>::iterator it;
			it = componentMap.find(Interface::IEngineResource<T_S>::type);

			if (it != componentMap.end())
				return 	(T_S&)*it->second;
			else
				return (T_S&)*Create_T<T_S>();
		}

		static ModuleManager& get();
		static void deconstruct();

	};
}
namespace OneFlower::Engine
{
	template<class T>
	inline T& GetModule()
	{
		return Module::ModuleManager::get().GetResource<T>();
	}

	inline void Dispose() {
		Module::ModuleManager::deconstruct();
	}
}

#endif
