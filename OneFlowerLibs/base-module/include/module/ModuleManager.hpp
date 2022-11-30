#ifndef EngineResourceManager_HPP
#define EngineResourceManager_HPP

#include <map>
#include <module/IEngineModule.hpp>
#include <memory>

namespace of::module
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
			componentMap.insert({ interface::IEngineResource<T>::type, std::make_unique<T>() });
			return (T*)componentMap[interface::IEngineResource<T>::type].get();
		}

	public:
		template<class T_S>
		T_S& GetResource()
		{
			std::map<EngineResourceType, std::unique_ptr<BaseEngineModule>>::iterator it;
			it = componentMap.find(interface::IEngineResource<T_S>::type);

			if (it != componentMap.end())
				return 	(T_S&)*it->second;
			else
				return (T_S&)*Create_T<T_S>();
		}

		static ModuleManager& get();
		static void deconstruct();

	};
}
namespace of::engine
{
	template<class T>
	inline T& GetModule()
	{
		return module::ModuleManager::get().GetResource<T>();
	}

	inline void Dispose() {
		module::ModuleManager::deconstruct();
	}
}

#endif
