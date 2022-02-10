#ifndef EngineResourceManager_HPP
#define EngineResourceManager_HPP

#include <map>
#include <Interfaces/IEngineModule.hpp>
#include <memory>
namespace EngineModule
{
	class ModuleManager
	{
		friend class BaseEngineModule;
		static ModuleManager* m_engineResourceManager;

		~ModuleManager();

		std::map<Enums::EngineResourceType, std::unique_ptr<BaseEngineModule> > componentMap;

		template<class T>
		T* Create_T()
		{
			componentMap.insert({ Interfaces::IEngineResource<T>::type, std::make_unique<T>() });
			return (T*)componentMap[Interfaces::IEngineResource<T>::type].get();
		}

	public:
		template<class T_S>
		T_S& GetResource()
		{
			std::map<Enums::EngineResourceType, std::unique_ptr<BaseEngineModule>>::iterator it;
			it = componentMap.find(Interfaces::IEngineResource<T_S>::type);

			if (it != componentMap.end())
				return 	(T_S&)*it->second;
			else
				return (T_S&)*Create_T<T_S>();
		}

		static ModuleManager& get();
		static void deconstruct();

	};
}
namespace Engine
{
	template<class T>
	inline T& GetModule()
	{
		return EngineModule::ModuleManager::get().GetResource<T>();
	}
	inline void Dispose() {
		EngineModule::ModuleManager::deconstruct();
	}
}

#endif
