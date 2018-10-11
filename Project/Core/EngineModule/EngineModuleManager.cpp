#include "EngineModuleManager.hpp"

EngineModuleManager* EngineModuleManager::m_engineResourceManager = nullptr;

EngineModuleManager::~EngineModuleManager()
{
	std::map<ResourceType, BaseEngineModule*>::iterator it = componentMap.begin();
	std::map<ResourceType, BaseEngineModule*>::iterator eit = componentMap.end();
	for (it; it != eit; it++)
	{
		delete it->second;
		it->second = nullptr;
	}
	componentMap.clear();
}

EngineModuleManager & EngineModuleManager::get()
{
	if (!m_engineResourceManager)
		m_engineResourceManager = new EngineModuleManager();
	return *m_engineResourceManager;
}

void EngineModuleManager::deconstruct()
{
	if (m_engineResourceManager)
		delete m_engineResourceManager;
	m_engineResourceManager = nullptr;
}
