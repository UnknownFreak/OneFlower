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

		template<class T, class ...Args>
		T* Create_T(Args&&... args)
		{
			componentMap.insert({ interface::IEngineResource<T>::type, std::make_unique<T>(std::forward<Args>(args)...) });
			return (T*)componentMap[interface::IEngineResource<T>::type].get();
		}

	public:
		template<class T_S, class ...Args>
		T_S& GetResource(Args&&... args)
		{
			std::map<EngineResourceType, std::unique_ptr<BaseEngineModule>>::iterator it;
			it = componentMap.find(interface::IEngineResource<T_S>::type);

			if (it != componentMap.end())
				return 	(T_S&)*it->second;
			else
				return (T_S&)*Create_T<T_S>(std::forward<Args>(args)...);
		}

		static ModuleManager& get();
		static void deconstruct();

	};
}
namespace of::engine
{
	template<class T, typename... Args>
	inline T& GetModule(Args&& ... args)
	{
		return module::ModuleManager::get().GetResource<T>(std::forward<Args>(args)...);
	}

	inline void Dispose() {
		module::ModuleManager::deconstruct();
	}
}

#endif
