#include "ModLoader.hpp"
#include <Module\ModuleManager.hpp>
#include <Module\Logger\OneLogger.hpp>


of::module::EngineResourceType of::module::interface::IEngineResource<File::Mod::Loader>::type = of::module::EngineResourceType::Loader;

namespace File::Mod
{
	const size_t Loader::getModPosition(const of::common::String& modName) const
	{
		std::map<of::common::String, size_t>::const_iterator it = loadOrder.find(modName);
		if (it != loadOrder.end())
			return it->second;
		else
		{
			auto& logger = of::engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::Mod::ModLoader");
			logger.Error("Failed to get mod position", logger.fileInfo(__FILE__, __LINE__));
			return 0xFFFFFFFF;
		}
	}
};