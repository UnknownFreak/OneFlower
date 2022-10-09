#include "EngineModuleManager.hpp"

namespace EngineModule
{
	ModuleManager* ModuleManager::m_engineResourceManager = nullptr;

	ModuleManager::~ModuleManager()
	{
		std::map<Enums::EngineResourceType, std::unique_ptr<BaseEngineModule>>::iterator it = componentMap.begin();
		std::map<Enums::EngineResourceType, std::unique_ptr<BaseEngineModule>>::iterator eit = componentMap.end();
		for (it; it != eit; it++)
		{
			it->second->disable();
			//delete it->second;
			//it->second = nullptr;
		}
		componentMap.clear();
	}

	ModuleManager & ModuleManager::get()
	{
		if (!m_engineResourceManager)
			m_engineResourceManager = new ModuleManager();
		return *m_engineResourceManager;
	}

	void ModuleManager::deconstruct()
	{
		if (m_engineResourceManager)
			delete m_engineResourceManager;
		m_engineResourceManager = nullptr;
	}
}