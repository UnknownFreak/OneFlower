#include "EngineResourceManager.hpp"

EngineResourceManager* EngineResourceManager::m_engineResourceManager = nullptr;

EngineResourceManager::~EngineResourceManager()
{
	std::map<ResourceType, BaseEngineResource*>::iterator it = componentMap.begin();
	std::map<ResourceType, BaseEngineResource*>::iterator eit = componentMap.end();
	for (it; it != eit; it++)
	{
		delete it->second;
	}
	componentMap.clear();
}

EngineResourceManager & EngineResourceManager::get()
{
	if (!m_engineResourceManager)
		m_engineResourceManager = new EngineResourceManager();
	return *m_engineResourceManager;
}

void EngineResourceManager::deconstruct()
{
	if (m_engineResourceManager)
		delete m_engineResourceManager;
	m_engineResourceManager = nullptr;
}
