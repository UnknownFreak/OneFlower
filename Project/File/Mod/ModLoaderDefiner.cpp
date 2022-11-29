#include "ModLoader.hpp"
#include <Module\EngineModuleManager.hpp>
#include <Module\Logger\OneLogger.hpp>


Enums::EngineResourceType Interfaces::IEngineResource<File::Mod::Loader>::type = Enums::EngineResourceType::ModLoader;

namespace File::Mod
{
	const size_t Loader::getModPosition(const of::common::String& modName) const
	{
		std::map<of::common::String, size_t>::const_iterator it = loadOrder.find(modName);
		if (it != loadOrder.end())
			return it->second;
		else
		{
			auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::Mod::ModLoader");
			logger.Error("Failed to get mod position", logger.fileInfo(__FILE__, __LINE__));
			return 0xFFFFFFFF;
		}
	}
};