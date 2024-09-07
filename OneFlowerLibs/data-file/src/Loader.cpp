#include <file/Loader.hpp>
#include <logger/Logger.hpp>

namespace of::file
{
	const size_t Loader::getModPosition(const common::String& modName) const
	{
		std::map<common::String, size_t>::const_iterator it = loadOrder.find(modName);
		if (it != loadOrder.end())
			return it->second;
		else
		{
			auto& logger = of::logger::get().getLogger("of::file::Loader");
			logger.Error("Failed to get mod position", logger.fileInfo(__FILE__, __LINE__));
			return 0xFFFFFFFF;
		}
	}
};