#include <file/Loader.hpp>
#include <Module/ModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>


of::module::EngineResourceType of::module::interface::IEngineResource<of::file::Loader>::type = of::module::EngineResourceType::Loader;

namespace of::file
{
	const size_t Loader::getModPosition(const common::String& modName) const
	{
		std::map<common::String, size_t>::const_iterator it = loadOrder.find(modName);
		if (it != loadOrder.end())
			return it->second;
		else
		{
			auto& logger = engine::GetModule<module::logger::OneLogger>().getLogger("File::Loader");
			logger.Error("Failed to get mod position", logger.fileInfo(__FILE__, __LINE__));
			return 0xFFFFFFFF;
		}
	}

	module::EngineResourceType& Loader::getType() const
	{
		return type;
	}
};