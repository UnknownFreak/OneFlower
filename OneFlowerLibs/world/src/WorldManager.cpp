#include <module/WorldManager.hpp>

#include <file/Handler.hpp>
#include <module/OneTime.hpp>

#include <resource/Prefab.hpp>

//void WorldManager::doDayCycle(const float& fElapsedTime)
//{
//	float dt = 0.004f * fElapsedTime;
//	gfx.timeOfDay += dt;
//	float f = 3.14f / 20.f;
//	float f2 = 6.f / 20.f;
//	//float f3 = 1.4f / 18.f;
//	if (gfx.timeOfDay > 24.f)
//	{
//		gfx.timeOfDay = 0.f;
//		gfx.shadowAngle = 0.f;
//	}
//	if (gfx.timeOfDay > 0.f && gfx.timeOfDay < 5.f)
//	{
//		gfx.shadowLengthX = 6.f;
//		gfx.shadowLengthY = 1.4f;
//	}
//	//		gfx.shadowAngle += f * dt;
//	if (gfx.timeOfDay > 5.f && gfx.timeOfDay < 5.f + 20.f)
//	{
//		gfx.shadowAngle += f * dt;
//		if (gfx.timeOfDay < 4.f + 8)
//		{
//			gfx.shadowLengthX -= f2 * dt;
//		}
//		else
//		{
//			gfx.shadowLengthX += f2 * dt;
//		}
//	}
//
//	//gfx.shadowLengthX = gfx.timeOfDay / 12.f;
//	//gfx.shadowLengthY = gfx.timeOfDay / 18.f;
//	//uint_fast8_t time = (uint_fast8_t)(std::abs(std::sin(gfx.timeOfDay / 8.f)) * 255);
//	//if (time < 64)
//	//	time = 64;
//	//gfx.currentDayColor = sf::Color(time, time, time);
//	//std::cout << "Brightness of day (0-255): " << int(time) << std::endl;
//	//float whole, fractional;
//	//fractional = std::modf(gfx.timeOfDay, &whole);
//	//std::cout << "time of day: " << int(whole) << "h " << int(fractional*60) << "m " << int(fractional*3600) % 60 << "s" << std::endl;
//	//std::cout << "shadowAngle: " << gfx.shadowAngle << std::endl;
//	//std::cout << "shadow length x: " << gfx.shadowLengthX << std::endl;
//	//std::cout << "shadow length y: " << gfx.shadowLengthY << std::endl;
//}
of::module::EngineResourceType of::module::interface::IEngineResource<of::module::WorldManager>::type = of::module::EngineResourceType::WorldManager;

namespace of::module
{
	const of::file::FileId& WorldManager::LoadingStateMachine::getCurrentWorld() const
	{
		return worldToLoad;
	}

	const of::file::FileId& WorldManager::LoadingStateMachine::getCurrentLoadingScreen() const
	{
		return loadingScreenToLoad;
	}

	WorldManager::LoadingStateMachine::LoadingStateMachine(WorldManager& parent) : parent(parent), loadingStateInfo(loadstate, parent.isLoading)
	{

	}
	void WorldManager::LoadingStateMachine::beginLoad(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& playerPosition, const of::world::LoadArgs& _loadArgs)
	{
		loadstate = of::world::LoadingState::PREPARE_LOADINGSCREEN;
		worldToLoad = world;
		loadingScreenToLoad = loadingScreen;
		playerPos = playerPosition;
		loadArgs = _loadArgs;
		auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("LoadingStateMachine");
		logger.Info("Begin loading world " + world(), logger.fileInfo(__FILE__, __LINE__));
		of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).reset();
	}

	void WorldManager::LoadingStateMachine::load()
	{
		using namespace of::world;
		switch (loadstate)
		{
		case LoadingState::LOAD_MAIN_MENU:
			loadMainMenu();
			break;
		case LoadingState::PREPARE_LOADINGSCREEN:
			prepareLoadingScreen();
			break;
		case LoadingState::BEGIN_LOAD:
			beginLoad();
			break;
		case LoadingState::CACHE_ALL_ZONES:
			cacheAllZones();
			break;
		case LoadingState::UPDATE_LOAD_INFO:
			updateZoneInfo();
			break;
		case LoadingState::UNLOAD_OBJECTS:
			unloadObjects();
			break;
		case LoadingState::LOAD_ALL_PREFABS:
			loadAllPrefabs();
			break;
		case LoadingState::LOAD_ALL_NAVMESH:
			loadAllNavmesh();
			break;
		case LoadingState::LOAD_GROUND:
			loadGround();
			break;
		case LoadingState::BUILD_COLLIDERS:
			buildColliders();
			break;
		case LoadingState::PRE_BUILDING_OBJECTS:
			preBuildObjects();
			break;
		case LoadingState::BUILD_OBJECTS:
			buildObjects();
			break;
		case LoadingState::FINALIZING:
			finalize();
		case LoadingState::DONE:
			done();
			break;
		default:
			break;
		}
		if(parent.isLoading)
			loadingStateInfo.totalLoadTime = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED).secondsAsFloat();
	}

	void WorldManager::LoadingStateMachine::loadMainMenu()
	{
		loadstate = of::world::LoadingState::LOAD_GROUND;
	}
	void WorldManager::LoadingStateMachine::prepareLoadingScreen()
	{
		loadingStateInfo.loadScreenSetupTime = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat(true);
		loadstate = of::world::LoadingState::BEGIN_LOAD;
	}
	void WorldManager::LoadingStateMachine::beginLoad()
	{
		instanceToLoad = of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<of::resource::WorldInstance>(worldToLoad);
		loadingStateInfo.totalLoadCount = instanceToLoad.getLoadingCount();
		loadingStateInfo.totalPrefabCount = instanceToLoad.prefabs.size();
		loadingStateInfo.totalNavmeshCount = instanceToLoad.navMesh.size();
		loadingStateInfo.totalGeometryCount = instanceToLoad.worldGeometry.size();
		loadingStateInfo.totalObjectPartCount = instanceToLoad.objectChunk.size();
		loadingStateInfo.totalObjectCount = 0;

		loadingStateInfo.currentLoadCount = 0;
		loadingStateInfo.currentPrefabCount = 0;
		loadingStateInfo.currentNavmeshCount = 0;
		loadingStateInfo.currentGeometryCount = 0;
		loadingStateInfo.currentObjectPartCount = 0;
		loadingStateInfo.currentObjectCount = 0;
		loadingStateInfo.currentZoneCount = 0;

		buffer.clear();
		loadingStateInfo.instanceLoadTime = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat(true);
		loadstate = of::world::LoadingState::CACHE_ALL_ZONES;
		if (loadArgs == of::world::LoadArgs::NEW_GAME)
		{
			navMeshLoaded = false;
		}
	}
	void WorldManager::LoadingStateMachine::cacheAllZones()
	{
		allInstances = of::engine::GetModule<of::file::Handler>().archive.listAllObjectKeys(of::file::ObjectType::WorldInstance);
		loadingStateInfo.totalZoneCount = allInstances.size();
		// TODO: request all zones... this can be huge...
		loadstate = of::world::LoadingState::UPDATE_LOAD_INFO;
	}
	void WorldManager::LoadingStateMachine::updateZoneInfo()
	{
		if (loadingStateInfo.currentZoneCount == loadingStateInfo.totalZoneCount)
		{
			loadingStateInfo.totalZoneUpdateCountTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat(true);
			loadstate = of::world::LoadingState::UNLOAD_OBJECTS;
		}
		else
		{
			auto instance = of::engine::GetModule<of::file::Handler>().archive.request<of::resource::WorldInstance>(allInstances[loadingStateInfo.currentZoneCount]);
			{
				for (auto it : instance->objectChunk)
				{
					objectChunkToInstanceId[it] = instance->getModfile();
				}
				if (!navMeshLoaded)
				{
					for (auto it : instance->navMesh)
					{
						objectChunkToInstanceId[it] = instance->getModfile();
					}
				}
				instanceToLoad.addTo(*instance, navMeshLoaded);
				loadingStateInfo.totalLoadCount = instanceToLoad.getLoadingCount();
				loadingStateInfo.totalPrefabCount = instanceToLoad.prefabs.size();
				loadingStateInfo.totalNavmeshCount = instanceToLoad.navMesh.size();
				loadingStateInfo.totalGeometryCount = instanceToLoad.worldGeometry.size();
				loadingStateInfo.totalObjectPartCount = instanceToLoad.objectChunk.size();
			}
			loadingStateInfo.currentZoneCount++;
			loadingStateInfo.totalZoneUpdateCountTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat();
		}
	}
	void WorldManager::LoadingStateMachine::unloadObjects()
	{
		auto& handler = parent.objectHandler;
		if (loadArgs == of::world::LoadArgs::NEW_GAME)
		{
			// things may be a bit confusing regarding new game... but we do not need to set the clear persistance flag on the gameobjects when deleted,
			// because first of all if new game is called from the main menu, zero objects should be loaded (minus the splash screen objects)
			// on the other hand, if the player goes back to main menu, ALL objects should still have been unloaded via the of::world::LoadingState::UNLOAD_ALL state,
			// and even if objects still exist, the save file reference itself has nuked ALL object persistance data before any loading is started.
			handler.unloadAll();
		}
		else
		{
			handler.unloadNonUnique();
		}
		loadstate = of::world::LoadingState::LOAD_ALL_PREFABS;
	}
	void WorldManager::LoadingStateMachine::loadAllPrefabs()
	{
		if (loadingStateInfo.currentPrefabCount == loadingStateInfo.totalPrefabCount)
		{
			loadingStateInfo.prefabLoadTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat(true);
			loadstate = of::world::LoadingState::LOAD_ALL_NAVMESH;
		}
		else
		{
			of::engine::GetModule<of::file::Handler>().archive.request<of::resource::Prefab>(instanceToLoad.prefabs[loadingStateInfo.currentPrefabCount]);
			loadingStateInfo.currentPrefabCount++;
			loadingStateInfo.currentLoadCount++;
			loadingStateInfo.prefabLoadTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat();
		}
	}
	void WorldManager::LoadingStateMachine::loadAllNavmesh()
	{
		if (!navMeshLoaded)
		{
			if (loadingStateInfo.currentNavmeshCount == loadingStateInfo.totalNavmeshCount)
			{
				loadingStateInfo.navmeshLoadTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat(true);
				navMeshLoaded = true;
				loadstate = of::world::LoadingState::LOAD_GROUND;
			}
			else
			{
				
			}
		}
		else
		{
			loadstate = of::world::LoadingState::LOAD_GROUND;
		}
	}
	void WorldManager::LoadingStateMachine::loadGround()
	{
		loadstate = of::world::LoadingState::BUILD_COLLIDERS;
	}
	void WorldManager::LoadingStateMachine::buildColliders()
	{
		loadstate = of::world::LoadingState::PRE_BUILDING_OBJECTS;
	}
	void WorldManager::LoadingStateMachine::preBuildObjects()
	{
		if (loadingStateInfo.currentObjectPartCount == loadingStateInfo.totalObjectPartCount)
		{
			loadingStateInfo.objectPartLoadTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat(true);
			loadstate = of::world::LoadingState::BUILD_OBJECTS;
		}
		else
		{
			auto& requestor = of::engine::GetModule<of::file::Handler>().archive;
			auto chunk = requestor.request<of::resource::ObjectChunk>(instanceToLoad.objectChunk[loadingStateInfo.currentObjectPartCount]);
			for (auto& x : chunk->objectLocations)
			{
				loadingStateInfo.totalObjectCount += x.second.size();
				loadingStateInfo.totalLoadCount += x.second.size();
				auto pref = requestor.requestShared<of::resource::Prefab>(x.first);
				for (auto& location : x.second)
				{
					location.prefab = x.first;
					location.layer = chunk->getModfile();
				}
				buffer.reserve(buffer.size() + x.second.size());
				buffer.insert(buffer.end(), x.second.begin(), x.second.end());
			}
			loadingStateInfo.totalObjectCount = buffer.size();

			loadingStateInfo.currentObjectPartCount++;
			loadingStateInfo.currentLoadCount++;
			loadingStateInfo.objectPartLoadTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat();
		}
	}
	void WorldManager::LoadingStateMachine::buildObjects()
	{
		if (loadingStateInfo.currentObjectCount == loadingStateInfo.totalObjectCount)
		{
			loadingStateInfo.objectLoadTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat(true);
			loadstate = of::world::LoadingState::FINALIZING;
		}
		else
		{
			auto& bufferObj = buffer[loadingStateInfo.currentObjectCount];

			auto& requestor = of::engine::GetModule<of::file::Handler>().archive;
			auto prefab = requestor.request<of::resource::Prefab>(bufferObj.prefab);

			if (bufferObj.isUnique || bufferObj.layer == getCurrentWorld())
			{

			auto object = prefab->createNewInstance(bufferObj.objectId, bufferObj.location);
			object->unique = bufferObj.isUnique;
			// TODO:
			//object->post(of::object::messaging::Topic::of(of::object::messaging::Topics::MOVE_ZONE), std::make_shared<MoveToZone>(bufferObj.layer));
			// The render, physics & ai component should listen to this to properly move it to the correct layer upon loading
			}

			loadingStateInfo.currentObjectCount++;
			loadingStateInfo.currentLoadCount++;
			loadingStateInfo.objectLoadTimer = of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED_PART).secondsAsFloat();
		}
	}
	void WorldManager::LoadingStateMachine::finalize()
	{
		if (loadArgs == of::world::LoadArgs::LOAD_FROM_FILE)
		{
			parent.objectHandler.resolveObjectReferences();
		}
		loadstate = of::world::LoadingState::DONE;
	}
	void WorldManager::LoadingStateMachine::done()
	{
		if (parent.isLoading)
		{
			auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("LoadingStateMachine");
			logger.Info("Finished loading world, it took " + std::to_string(of::engine::GetModule<of::module::Time>().getTimer(globals::TOTAL_TIME_LOADED).secondsAsFloat(true)) + "s", logger.fileInfo(__FILE__, __LINE__));
		}
		// TODO: replace with GameObject MessageTopic SetPosition
		// of::engine::GetModule<of::module::ObjectInstanceHandler>().player->getComponent<of::object::component::Transform>()->pos = playerPos;
		parent.isLoading = false;
		loadstate = of::world::LoadingState::UNDEFINED;
	}
	void WorldManager::LoadingStateMachine::unloadAll()
	{
		parent.objectHandler.unloadAll();
		//parent.navMesh.unload();
		// or similar way to get the navmesh module and unload it
		navMeshLoaded = false;
		loadstate = of::world::LoadingState::LOAD_MAIN_MENU;
	}
}

namespace of::module
{
	WorldManager::WorldManager() : loadStateMachine(*this), objectHandler(of::engine::GetModule<of::module::ObjectInstanceHandler>()), saveFile(of::engine::GetModule<of::module::SaveFile>())
	{
	}

	void WorldManager::initialize()
	{
		newGame();
		//auto& f = of::engine::GetModule<Input::InputHandler>();
		//
		//f.uiKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("Console", [&](bool, swizzle::input::Keys, const float&) {gfx.ui.ToggleConsole(); f.togglePlayerInput(); }, false),
		//	swizzle::input::Keys::KeyF1
		//, Enums::Input::Action::Press);
		//
		//f.uiKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("GlobalFlag", [&](bool, swizzle::input::Keys, const float&) {
		//	of::engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX] = !of::engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX];
		//	}, false), 
		//	 swizzle::input::Keys::KeyF2
		//	, Enums::Input::Action::Press);
		//
		//auto& console = of::engine::GetModule<Console>();
		//console;

	}

	WorldManager::WorldManager(const WorldManager& ) : objectHandler(of::engine::GetModule<of::module::ObjectInstanceHandler>()), loadStateMachine(*this), saveFile(of::engine::GetModule<of::module::SaveFile>())
	{
	}

	//void WorldManager::setCurrentTime(const float& currentTime)
	//{
	//	while (gfx.timeOfDay < currentTime || gfx.timeOfDay > currentTime + 0.5f)
	//		Simulate(12.f);
	//}

	void WorldManager::newGame()
	{
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("WorldManager").Info("New Game");
		saveFile.newGame(of::resource::DifficultyLevel::Normal, of::common::uuid::nil(), {});
		auto& p = saveFile.getGameMode();
		loadWorldInstance(p.startingZone, p.loadingScreen, p.startingPosition, of::world::LoadArgs::NEW_GAME);
		//auto& glob = of::engine::GetModule<Globals>();
		//loadWorldInstance(glob.newGameWorldInstance, glob.newGameWorldInstanceLoadingScreen, glob.newGamePoint);
	}

	of::world::LoadingStateInfo& WorldManager::getLoadingStateInfo()
	{
		return loadStateMachine.loadingStateInfo;
	}

	void WorldManager::save(const of::common::String& fileName)
	{
		objectHandler.persistGameObjects();
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("WorldManager").Info("Save Game");
		saveFile.currentZone = loadStateMachine.getCurrentWorld();
		saveFile.loadingScreen = loadStateMachine.getCurrentLoadingScreen();
		saveFile.save(fileName);
	}

	void WorldManager::load(const of::common::String& fileName)
	{
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("WorldManager").Info("Load Game");
		isLoading = true;
		saveFile.load(fileName);
		loadWorldInstance(saveFile.currentZone, saveFile.loadingScreen, saveFile.point, of::world::LoadArgs::LOAD_FROM_FILE);
		// TODO: start timers from questing module if needed
	}

	void WorldManager::loadWorldInstance(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& playerPosition, const of::world::LoadArgs& loadArgs)
	{
		isLoading = true;
		of::module::Time& time = of::engine::GetModule<of::module::Time>();
		time.getTimer(globals::LOADING_TIMER).reset();
		time.getTimer(globals::TOTAL_TIME_LOADED).reset();

		loadStateMachine.beginLoad(world, loadingScreen, playerPosition, loadArgs);

	}

	void WorldManager::Update()
	{
		if (isLoading)
		{
			auto timer = of::engine::GetModule<of::module::Time>().getTimer(globals::LOADING_TIMER);
			timer.reset();
			while (timer.secondsAsFloat() < 0.05f && isLoading)
			{
				loadStateMachine.load();
			}
		}
	}

	void WorldManager::Simulate(const float& fElapsedTime)
	{
		//doDayCycle(fElapsedTime);
		objectHandler.processDeletedObjects(fElapsedTime);
	}

	of::module::EngineResourceType& WorldManager::getType() const
	{
		return type;
	}
}
