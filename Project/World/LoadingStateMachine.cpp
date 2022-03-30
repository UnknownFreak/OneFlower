#include "LoadingStateMachine.hpp"

#include <Graphics/UI/LoadingScreen.hpp>
#include <Module/OneTime.hpp>
#include <Object/ObjectInstanceHandler.hpp>

const File::Mod::ModFileUUIDHelper& LoadingStateMachine::getCurrentWorld() const
{
	return worldToLoad;
}

const File::Mod::ModFileUUIDHelper& LoadingStateMachine::getCurrentLoadingScreen() const
{
	return loadingScreenToLoad;
}

LoadingStateMachine::LoadingStateMachine(Graphics::RenderWindow& gfx, bool& isLoading) : gfx(gfx), isLoading(isLoading), loadstate(Enums::LoadingState::UNDEFINED), loadingScreenInfoPtr(nullptr), playerPos{0.f, 0.f, 0.f}
{

}


void LoadingStateMachine::beginLoad(const File::Mod::ModFileUUIDHelper& world, const File::Mod::ModFileUUIDHelper& loadingScreen, const Core::Vector3f& playerPosition)
{
	loadstate = Enums::LoadingState::PREPARE_LOADINGSCREEN;
	worldToLoad = world;
	loadingScreenToLoad = loadingScreen;
	playerPos = playerPosition;
	auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("LoadingStateMachine");
	logger.Info("Begin loading world " + world(),logger.fileInfo( __FILE__, __LINE__));
	Engine::GetModule<EngineModule::Time> ().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
}

void LoadingStateMachine::load()
{
	if (Engine::GetModule<Globals>().boolGlobals[Globals::B_GLOBAL_SLOW_LOADING])
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	switch (loadstate)
	{
	case Enums::LoadingState::PREPARE_LOADINGSCREEN:
		// TODO
		// Requestor<LoadingScreen>& instance = Engine::GetModule<Asset::AssetManager>().getLoadingScreenRequestor();
		// loadingScreen = instance.request(loadingScreenToLoad);
		// Below is temporary for testing Since the loadingscreen will be hardcoded to an ugly one
		gfx.ui.addUIContext(Enums::UIContextNames::LoadingScreen, std::make_unique<Graphics::UI::LoadingScreen>());
		gfx.ui.addUIContext(Enums::UIContextNames::LoadingScreenInfo, std::make_unique<Graphics::UI::LoadingScreenInfo>(loadstate));
		gfx.ui.showLoadingScreenOnly = true;
		loadingScreenInfoPtr = gfx.ui.getUIContext<Graphics::UI::LoadingScreenInfo>(Enums::UIContextNames::LoadingScreenInfo);
		loadingScreenInfoPtr->loadScreenSetupTime = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
		loadstate = Enums::LoadingState::BEGIN_LOAD;
		break;
	
	case Enums::LoadingState::BEGIN_LOAD:
	{
		instanceToLoad = Engine::GetModule<Asset::AssetManager>().requestor.requestUniqueInstance<WorldInstance>(worldToLoad);
		loadingScreenInfoPtr->totalLoadCount = instanceToLoad.getLoadingCount();
		loadingScreenInfoPtr->totalAtlasCount = instanceToLoad.tileAtlases.size();
		loadingScreenInfoPtr->totalPrefabCount = instanceToLoad.prefabs.size();
		loadingScreenInfoPtr->totalTileCount = instanceToLoad.tileInfo.size();
		loadingScreenInfoPtr->totalTileBuildingCount = instanceToLoad.tileInfo.size();
		loadingScreenInfoPtr->totalColliderCount = instanceToLoad.colliderInfo.size();
		loadingScreenInfoPtr->totalColliderBuildingCount = instanceToLoad.colliderInfo.size();
		loadingScreenInfoPtr->totalObjectPartCount = instanceToLoad.objectChunk.size();
		loadingScreenInfoPtr->totalObjectCount = 0;

		loadingScreenInfoPtr->currentLoadCount = 0;
		loadingScreenInfoPtr->currentAtlasCount = 0;
		loadingScreenInfoPtr->currentPrefabCount = 0;
		loadingScreenInfoPtr->currentTileCount = 0;
		loadingScreenInfoPtr->currentTileBuildingCount = 0;
		loadingScreenInfoPtr->currentColliderCount = 0;
		loadingScreenInfoPtr->currentColliderBuildingCount = 0;
		loadingScreenInfoPtr->currentObjectPartCount = 0;
		loadingScreenInfoPtr->currentObjectCount = 0;

		gfx.mtx.lock();
		gfx.clearDrawList();
		buffer.clear();
		gfx.mtx.unlock();

		loadingScreenInfoPtr->instanceLoadTime = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
		loadstate = Enums::LoadingState::UNLOAD_OLD_OBJECTS;
		break;
	}
	case Enums::LoadingState::UNLOAD_OLD_OBJECTS:
	{
		auto& handler = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		handler.unload();
		loadstate = Enums::LoadingState::LOADING_ATLAS;
		break;
	}
	case Enums::LoadingState::LOADING_ATLAS:
	{
		if (loadingScreenInfoPtr->currentAtlasCount == loadingScreenInfoPtr->totalAtlasCount)
		{
			loadingScreenInfoPtr->atlasLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::LOADING_PREFABS;
		}
		else
		{
			Engine::GetModule<Asset::AssetManager>().requestor.request<File::Resource::Texture::TileAtlas>(instanceToLoad.tileAtlases[loadingScreenInfoPtr->currentAtlasCount]);
			loadingScreenInfoPtr->currentAtlasCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->atlasLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
		break;
	}
	case Enums::LoadingState::LOADING_PREFABS:
	{
		if (loadingScreenInfoPtr->currentPrefabCount == loadingScreenInfoPtr->totalPrefabCount)
		{
			loadingScreenInfoPtr->prefabLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::LOADING_TILES;
		}
		else
		{
			Engine::GetModule<Asset::AssetManager>().requestor.request<Prefab>(instanceToLoad.prefabs[loadingScreenInfoPtr->currentPrefabCount]);
			loadingScreenInfoPtr->currentPrefabCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->prefabLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
		break;
	}
	case Enums::LoadingState::LOADING_TILES:
	{
		if (loadingScreenInfoPtr->currentTileCount == loadingScreenInfoPtr->totalTileCount)
		{
			loadingScreenInfoPtr->tileLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::BUILDING_TILEMAP;
		}
		else
		{
			Engine::GetModule<Asset::AssetManager>().requestor.request<TileChunk>(instanceToLoad.tileInfo[loadingScreenInfoPtr->currentTileCount]);
			loadingScreenInfoPtr->currentTileCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->tileLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
	}
		break;
	case Enums::LoadingState::BUILDING_TILEMAP:
	{
		if (loadingScreenInfoPtr->currentTileBuildingCount == loadingScreenInfoPtr->totalTileBuildingCount)
		{
			loadingScreenInfoPtr->tileBuildLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::LOADING_COLLIDERS;
		}
		else
		{
			auto chunk = Engine::GetModule<Asset::AssetManager>().requestor.request<TileChunk>(instanceToLoad.tileInfo[loadingScreenInfoPtr->currentTileBuildingCount]);
			for (auto& x : chunk->tileInfo)
				gfx.addRenderable(chunk->layer, chunk->group, x.pos.toVector2(), x.pos.z, chunk->atlas, x.textureCoors, x.type, x.hasShadow);
			if (chunk->chunkTransparency.set)
			{
				auto& tl = chunk->chunkTransparency;
				gfx.setTileMapTransparencyHitbox(chunk->layer, chunk->group, { tl.pos.x, tl.pos.y, tl.size.x, tl.size.y }, tl.pos.z);
			}
			loadingScreenInfoPtr->currentTileBuildingCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->tileBuildLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
	}
	break;
	case Enums::LoadingState::LOADING_COLLIDERS:
	{
		if (loadingScreenInfoPtr->currentColliderCount == loadingScreenInfoPtr->totalColliderCount)
		{
			loadingScreenInfoPtr->colliderLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::BUILD_COLLIDERS;
		}
		else
		{
			Engine::GetModule<Asset::AssetManager>().requestor.request<ColliderChunk>(instanceToLoad.colliderInfo[loadingScreenInfoPtr->currentColliderCount]);
			loadingScreenInfoPtr->currentColliderCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->colliderLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
	}
	break;
	case Enums::LoadingState::BUILD_COLLIDERS:
	{
		if (loadingScreenInfoPtr->currentColliderBuildingCount == loadingScreenInfoPtr->totalColliderBuildingCount)
		{
			loadingScreenInfoPtr->colliderBuildingLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::PRE_BUILDING_OBJECTS;
		}
		else
		{
			auto chunk = Engine::GetModule<Asset::AssetManager>().requestor.request<ColliderChunk>(instanceToLoad.colliderInfo[loadingScreenInfoPtr->currentColliderBuildingCount]);
			for(auto & x : chunk->colliderInfo)
				gfx.addHitbox(std::make_unique<TileCollider>(x.pos, x.size, x.type, x.isRoof), chunk->layer, chunk->group);
			loadingScreenInfoPtr->currentColliderBuildingCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->colliderBuildingLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
	}
	break;
	
	case Enums::LoadingState::PRE_BUILDING_OBJECTS:
	{
		if (loadingScreenInfoPtr->currentObjectPartCount == loadingScreenInfoPtr->totalObjectPartCount)
		{
			loadingScreenInfoPtr->objectPartLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::BUILDING_OBJECTS;
		}
		else
		{
			auto& requestor = Engine::GetModule<Asset::AssetManager>().requestor;
			auto chunk = requestor.request<ObjectChunk>(instanceToLoad.colliderInfo[loadingScreenInfoPtr->currentObjectPartCount]);
			for (auto& x : chunk->objectLocations)
			{
				loadingScreenInfoPtr->totalObjectCount += x.second.size();
				loadingScreenInfoPtr->totalLoadCount += x.second.size();
				auto pref = requestor.requestShared<Prefab>(x.first);
				for (auto& location : x.second)
				{
					location.prefab = x.first;
				}
				buffer.reserve(buffer.size() + x.second.size());
				buffer.insert(buffer.end(), x.second.begin(), x.second.end());
			}
			loadingScreenInfoPtr->currentObjectPartCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->objectPartLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
	}
		//loadstate = Enums::LoadingState::BUILDING_OBJECTS;
		break;

	case Enums::LoadingState::BUILDING_OBJECTS:
	{
		if (loadingScreenInfoPtr->currentObjectPartCount == loadingScreenInfoPtr->totalObjectCount)
		{
			loadingScreenInfoPtr->objectLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).restart();
			loadstate = Enums::LoadingState::DONE;
		}
		else
		{
			auto& location = buffer[loadingScreenInfoPtr->currentObjectCount];

			auto& requestor = Engine::GetModule<Asset::AssetManager>().requestor;
			auto prefab = requestor.request<Prefab>(location.prefab);

			prefab->createNewInstance(location.objectId, location.location);

			loadingScreenInfoPtr->currentObjectCount++;
			loadingScreenInfoPtr->currentLoadCount++;
			loadingScreenInfoPtr->objectLoadTimer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED_PART).getElapsedTime();
		}
	}
	//loadstate = Enums::LoadingState::BUILDING_OBJECTS;
	break;
	//case Enums::LoadingState::BUILDING_OBJECTS:
	//	loadstate = Enums::LoadingState::FINALIZING;
	//	break;
	//case Enums::LoadingState::BUILDING_TILEMAP:
	//	loadstate = Enums::LoadingState::BUILD_COLLIDERS;
	//	break;
	//case Enums::LoadingState::FINALIZING:
	//	loadstate = Enums::LoadingState::DONE;
	//	break;
	case Enums::LoadingState::DONE:
	{
		if (isLoading)
		{
			gfx.ui.removeUIContext(Enums::UIContextNames::LoadingScreen);
			gfx.ui.removeUIContext(Enums::UIContextNames::LoadingScreenInfo);
			gfx.ui.showLoadingScreenOnly = false;
			auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("LoadingStateMachine");
			logger.Info("Finished loading world, it took " + std::to_string(Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED).getElapsedTime().asSeconds()) + "s", logger.fileInfo(__FILE__, __LINE__));
		}
		Engine::GetModule<EngineModule::ObjectInstanceHandler>().player->getComponent<Component::Transform>()->pos = playerPos;
		loadingScreenInfoPtr = nullptr;
		isLoading = false;
		loadstate = Enums::LoadingState::UNDEFINED;
		break;
	}
	default:
		break;
	}
	if (loadingScreenInfoPtr)
	{
		loadingScreenInfoPtr->totalLoadTime = Engine::GetModule<EngineModule::Time>().getTimer(Globals::TOTAL_TIME_LOADED).getElapsedTime();
		loadingScreenInfoPtr->update();
	}
}