#include "ModLoader.hpp"
#include "../../Engine.hpp"
ModLoader::ModLoader() : loadOrder()
{

}

size_t ModLoader::getModPosition(std::string modName)
{
	std::map<std::string, size_t>::iterator it = loadOrder.find(modName);
	if (it != loadOrder.end())
	{
		return it->second;
	}
	else
	{
		Engine::Window.debug.print("Error Getting mod position", __LINE__, __FILE__);
		return 0xFFFFFFFF;
	}
}