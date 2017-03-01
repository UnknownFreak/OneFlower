#include "ModLoader.hpp"

size_t ModLoader::getModPosition(Core::String modName)
{
	std::map<Core::String, size_t>::iterator it = loadOrder.find(modName);
	if (it != loadOrder.end())
	{
		return it->second;
	}
	else
	{
		//Engine::Window.debug.print("Error Getting mod position", __LINE__, __FILE__);
		return 0xFFFFFFFF;
	}
}