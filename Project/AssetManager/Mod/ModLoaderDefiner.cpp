#include "ModLoader.hpp"
#include <Logger\Logger.hpp>
size_t ModLoader::getModPosition(Core::String modName) const
{
	std::map<Core::String, size_t>::const_iterator it = loadOrder.find(modName);
	if (it != loadOrder.end())
		return it->second;
	else
	{
		OneLogger::Error("Failed to get mod position", __FILE__, __LINE__);
		return 0xFFFFFFFF;
	}
}