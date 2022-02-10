#include "ModLoader.hpp"
#include <Module\EngineModuleManager.hpp>
#include <Module\Logger\OneLogger.hpp>


Enums::EngineResourceType Interfaces::IEngineResource<ModLoader>::type = Enums::EngineResourceType::ModLoader;

const size_t ModLoader::getModPosition(const Core::String& modName) const
{
	std::map<Core::String, size_t>::const_iterator it = loadOrder.find(modName);
	if (it != loadOrder.end())
		return it->second;
	else
	{
		Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Failed to get mod position", __FILE__, __LINE__);
		return 0xFFFFFFFF;
	}
}
