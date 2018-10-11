#include "WorldManager.hpp"
#include "Zone.hpp"

#include <Asset\AssetManagerCore.hpp>
#include <Graphic\Gfx.h>

ResourceType IEngineResource<WorldManager>::type = ResourceType::WorldManager;

WorldManager::WorldManager() : lastLoadedZone("", 0), currentZone(0), refZoneToLoad(nullptr)
{

	if (Engine::GetModule<Asset::AssetManager>().loadModOrderFile() == false)
	{
		Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.insert(std::pair<Core::String, size_t>("OneFlower", 1));
		Engine::GetModule<Asset::AssetManager>().saveModOrderFile();
	}
}
// deconstructor
WorldManager::~WorldManager()
{
	for (std::map<std::pair<Core::String, size_t>, Zone>::iterator it = worldmap.begin(); it != worldmap.end(); it++)
	{
		for (size_t j = 0; j < it->second.objects.size(); j++)
		{
			// request removal of GameObjects /to fix
			//Engine::game.requestRemoveal(it->second->objects[j].second);
			it->second.objects[j].second = nullptr;
		}
	}
}

void WorldManager::loadZone(Core::String addedFromMod, size_t zoneID)
{
	zoneToLoadID = std::pair<Core::String, size_t>(addedFromMod, zoneID);
	startLoad();
}

Zone& WorldManager::getCurrentZone()
{
	return *currentZone;
}
const bool WorldManager::isLoading() const
{
	return _isLoading;
}
void WorldManager::drawLoadingScreen()
{
	if (currentZone)
	{
		Engine::GetModule<Gfx>().DrawLoadingScreen(*currentZone->getLoadingScreen(), currentZone->getLoadingScreenMessage());
	}
}

const WorldManager::Loadstate WorldManager::getCurrentLoadingState() const
{
	return loadState;
}

