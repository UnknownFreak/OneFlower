#include "ModLoader.hpp"
#include <Logger\Logger.hpp>
size_t ModLoader::getModPosition(Core::String modName)
{
	std::map<Core::String, size_t>::iterator it = loadOrder.find(modName);
	if (it != loadOrder.end())
		return it->second;
	else
	{
		Logger::Error("Failed to get mod position", __FILE__, __LINE__);
		return 0xFFFFFFFF;
	}
}