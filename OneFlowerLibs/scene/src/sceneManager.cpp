#include <scene/sceneManager.hpp>

#include <engine/runMode.hpp>

#include <file/Handler.hpp>
#include <timer/timer.hpp>

#include <resource/Prefab.hpp>
#include <graphics/sky/skyBox.hpp>

#include <resource/cutSceneInfo.hpp>

#include <scene/imgui/LoadingScreenInfo.hpp>

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

namespace of::scene
{
	const of::file::FileId& SceneManager::LoadingStateMachine::getCurrentWorld() const
	{
		return worldToLoad;
	}

	const of::file::FileId& SceneManager::LoadingStateMachine::getCurrentLoadingScreen() const
	{
		return loadingScreenToLoad;
	}

	SceneManager::LoadingStateMachine::LoadingStateMachine(SceneManager& parent) : parent(parent), loadingStateInfo(loadstate, parent.isLoading)
	{

	}

	void SceneManager::LoadingStateMachine::beginLoad(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& playerPosition, const of::world::LoadArgs _loadArgs)
	{
		loadstate = of::world::LoadingState::PREPARE_LOADINGSCREEN;
		worldToLoad = world;
		loadingScreenToLoad = loadingScreen;
		playerPos = playerPosition;
		loadArgs = _loadArgs;
		auto& logger = of::logger::get().getLogger("LoadingStateMachine");
		logger.Info("Begin loading world " + world(), logger.fileInfo(__FILE__, __LINE__));
		of::timer::reset(globals::TOTAL_TIME_LOADED_PART);
	}

	void SceneManager::LoadingStateMachine::load()
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
		case LoadingState::CACHE_ALL_CUTSCENES:
			cacheCutScenes();
			break;
		case LoadingState::UPDATE_LOAD_INFO:
			updateLoadInfo();
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
			break;
		case LoadingState::DONE:
			done();
			break;
		default:
			break;
		}
		if (parent.isLoading)
			loadingStateInfo.totalLoadTime = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED);
	}

	void SceneManager::LoadingStateMachine::loadMainMenu()
	{
		loadstate = of::world::LoadingState::LOAD_GROUND;
	}
	void SceneManager::LoadingStateMachine::prepareLoadingScreen()
	{
		loadingStateInfo.loadScreenSetupTime = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
		loadstate = of::world::LoadingState::BEGIN_LOAD;
	}
	void SceneManager::LoadingStateMachine::beginLoad()
	{
		instanceToLoad = of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<of::resource::WorldInstance>(worldToLoad);
		loadingStateInfo.totalLoadCount = instanceToLoad.getLoadingCount();
		loadingStateInfo.totalPrefabCount = instanceToLoad.prefabs.size();
		loadingStateInfo.totalNavmeshCount = instanceToLoad.navMesh.size();
		loadingStateInfo.totalGeometryCount = instanceToLoad.worldGeometry.size();
		loadingStateInfo.totalObjectPartCount = instanceToLoad.objectChunk.size();
		loadingStateInfo.totalCutSceneCount = instanceToLoad.cutScenes.size();
		loadingStateInfo.totalObjectCount = 0;

		loadingStateInfo.currentLoadCount = 0;
		loadingStateInfo.currentPrefabCount = 0;
		loadingStateInfo.currentNavmeshCount = 0;
		loadingStateInfo.currentGeometryCount = 0;
		loadingStateInfo.currentObjectPartCount = 0;
		loadingStateInfo.currentObjectCount = 0;
		loadingStateInfo.currentCutSceneCount = 0;
		loadingStateInfo.currentZoneCount = 0;

		buffer.clear();
		loadingStateInfo.instanceLoadTime = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
		loadstate = of::world::LoadingState::CACHE_ALL_ZONES;

		if (auto valid = parent.appl.lock())
		{
			if (instanceToLoad.skybox != "")
			{
				valid->setSkybox(instanceToLoad.skybox);
			}
		}

		if (loadArgs == of::world::LoadArgs::NEW_GAME)
		{
			navMeshLoaded = false;
		}
		else if (loadArgs == of::world::LoadArgs::LOAD_FROM_FILE)
		{
			auto it = parent.saveFile.begin();
			for (it; it != parent.saveFile.end(); it++)
			{
				if (it->second->isOfType(of::session::SaveStateTypeRef<of::object::ObjectSaveState>::type))
				{
					auto derived = it->second->toDerived<of::object::ObjectSaveState>();
					if (derived->prefabId.isValid())
					{
						// We're currently lacking layer info... we need to account for that in the future.
						// The best is if we do not need to account for it, because it should be stored on 
						// ActiveLayerComponent could be a solution.
						buffer.push_back(of::resource::ObjectInfo{ .prefab = derived->prefabId, .objectId = it->first.uuid, .location = {0,0,0}, .isUnique = true });
					}
				}
			}
		}
	}
	void SceneManager::LoadingStateMachine::cacheAllZones()
	{
		allInstances = of::engine::GetModule<of::file::Handler>().archive.listAllObjectKeys(of::file::ObjectType::WorldInstance);
		loadingStateInfo.totalZoneCount = allInstances.size();
		// TODO: request all zones... this can be huge...
		loadstate = of::world::LoadingState::CACHE_ALL_CUTSCENES;
	}
	void SceneManager::LoadingStateMachine::cacheCutScenes()
	{
		if (loadingStateInfo.currentCutSceneCount == loadingStateInfo.totalCutSceneCount)
		{
			loadingStateInfo.totalCutSceneCountTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
			loadstate = of::world::LoadingState::UPDATE_LOAD_INFO;
		}
		else
		{
			//auto instance = of::engine::GetModule<of::file::Handler>().archive.request<of::resource::CutSceneInfo>(instanceToLoad.cutScenes[loadingStateInfo.currentCutSceneCount]);
			{
				
				if (of::engine::getRunMode() == of::engine::RunMode::EDITOR)
				{
					/*
					Create a temporary object to push an editor renderable to represent the cutscene renderInfo (e.g camera lookat & camera path etc.)
					*/
				}
			}
			loadingStateInfo.currentCutSceneCount++;
			loadingStateInfo.totalCutSceneCountTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
		}
	}
	void SceneManager::LoadingStateMachine::updateLoadInfo()
	{
		if (loadingStateInfo.currentZoneCount == loadingStateInfo.totalZoneCount)
		{
			loadingStateInfo.totalZoneUpdateCountTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
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
			loadingStateInfo.totalZoneUpdateCountTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART);
		}
	}
	void SceneManager::LoadingStateMachine::unloadObjects()
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
	void SceneManager::LoadingStateMachine::loadAllPrefabs()
	{
		if (loadingStateInfo.currentPrefabCount == loadingStateInfo.totalPrefabCount)
		{
			loadingStateInfo.prefabLoadTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
			loadstate = of::world::LoadingState::LOAD_ALL_NAVMESH;
		}
		else
		{
			of::engine::GetModule<of::file::Handler>().archive.request<of::resource::Prefab>(instanceToLoad.prefabs[loadingStateInfo.currentPrefabCount]);
			loadingStateInfo.currentPrefabCount++;
			loadingStateInfo.currentLoadCount++;
			loadingStateInfo.prefabLoadTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART);
		}
	}
	void SceneManager::LoadingStateMachine::loadAllNavmesh()
	{
		if (!navMeshLoaded)
		{
			if (loadingStateInfo.currentNavmeshCount == loadingStateInfo.totalNavmeshCount)
			{
				loadingStateInfo.navmeshLoadTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
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
	void SceneManager::LoadingStateMachine::loadGround()
	{
		loadstate = of::world::LoadingState::BUILD_COLLIDERS;
	}
	void SceneManager::LoadingStateMachine::buildColliders()
	{
		loadstate = of::world::LoadingState::PRE_BUILDING_OBJECTS;
	}
	void SceneManager::LoadingStateMachine::preBuildObjects()
	{
		if (loadingStateInfo.currentObjectPartCount == loadingStateInfo.totalObjectPartCount)
		{
			loadingStateInfo.objectPartLoadTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
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
			loadingStateInfo.objectPartLoadTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART);
		}
	}
	void SceneManager::LoadingStateMachine::buildObjects()
	{
		if (loadingStateInfo.currentObjectCount == loadingStateInfo.totalObjectCount)
		{
			loadingStateInfo.objectLoadTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART, true);
			loadstate = of::world::LoadingState::FINALIZING;
		}
		else
		{
			auto& bufferObj = buffer[loadingStateInfo.currentObjectCount];

			auto& requestor = of::engine::GetModule<of::file::Handler>().archive;
			auto prefab = requestor.request<of::resource::Prefab>(bufferObj.prefab);

			if (bufferObj.isUnique || bufferObj.layer == getCurrentWorld())
			{

				if (parent.saveFile.getState<of::object::ObjectSaveState>(bufferObj.objectId)->objectState == of::object::ObjectState::NoRecreate)
				{
					of::logger::get().getLogger("LoadingStateMachine").Debug("Skipping object creation as it's flagged NoRecreate in saveFile");
					// Pass
				}
				else
				{
					auto object = prefab->createNewInstance(bufferObj.objectId, bufferObj.location);
					object->unique = bufferObj.isUnique;
					// TODO:
					// object->post(of::object::messaging::Topic::of(of::object::messaging::Topics::MOVE_ZONE), std::make_shared<MoveToZone>(bufferObj.layer));
					// The render, physics & ai component should listen to this to properly move it to the correct layer upon loading
					// We need to be careful here with layer info, the option might be to add a paremeter to createNewInstance, 
					// since we only want to set the current layer if we're creating the object and not it's already loaded.
					// currently prefab checks for object existance, BUT, maybe it should be unaware of that, and existance needs to be checked before hand...
					// layers should preferably be stored on the gameobject root
				}

			}

			loadingStateInfo.currentObjectCount++;
			loadingStateInfo.currentLoadCount++;
			loadingStateInfo.objectLoadTimer = of::timer::elapsedTime(globals::TOTAL_TIME_LOADED_PART);
		}
	}
	void SceneManager::LoadingStateMachine::finalize()
	{
		if (loadArgs == of::world::LoadArgs::LOAD_FROM_FILE)
		{
			parent.objectHandler.resolveObjectReferences();
		}
		loadstate = of::world::LoadingState::DONE;
	}
	void SceneManager::LoadingStateMachine::done()
	{
		if (parent.isLoading)
		{
			auto& logger = of::logger::get().getLogger("LoadingStateMachine");
			logger.Info("Finished loading world, it took " + std::to_string(of::timer::elapsedTime(globals::TOTAL_TIME_LOADED, true)) + "s", logger.fileInfo(__FILE__, __LINE__));
		}
		// TODO: replace with GameObject MessageTopic SetPosition
		// of::engine::GetModule<of::module::ObjectInstanceHandler>().player->getComponent<of::object::component::Transform>()->pos = playerPos;
		parent.isLoading = false;
		loadstate = of::world::LoadingState::UNDEFINED;
	}
	void SceneManager::LoadingStateMachine::unloadAll()
	{
		parent.objectHandler.unloadAll();
		//parent.navMesh.unload();
		// or similar way to get the navmesh module and unload it
		navMeshLoaded = false;
		loadstate = of::world::LoadingState::LOAD_MAIN_MENU;
	}
}

namespace of::scene
{
	SceneManager::SceneManager(std::weak_ptr<of::graphics::window::Application> application) : loadStateMachine(*this)
		, objectHandler(of::object::get())
		, saveFile(of::session::get())
		, appl(application)
	{
	}

	SceneManager::~SceneManager()
	{
		if (auto valid = appl.lock())
		{
			valid->removeRenderable(loadingScreenInfoId);
		}
	}

	void SceneManager::initialize()
	{
		if (auto valid = appl.lock())
		{
			valid->addRenderable(of::graphics::window::RenderLayer::IMGUI, loadingScreenInfoId, std::make_shared<of::scene::imgui::LoadingScreenInfo>(getLoadingStateInfo()));
		}
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

	//void WorldManager::setCurrentTime(const float& currentTime)
	//{
	//	while (gfx.timeOfDay < currentTime || gfx.timeOfDay > currentTime + 0.5f)
	//		Simulate(12.f);
	//}

	of::file::FileId SceneManager::getCurrentInstanceId() const
	{
		return loadStateMachine.getCurrentWorld();
	}

	of::file::FileId SceneManager::getCurrentLoadScreenId() const
	{
		return loadStateMachine.getCurrentLoadingScreen();
	}

	of::world::LoadingStateInfo& SceneManager::getLoadingStateInfo()
	{
		return loadStateMachine.loadingStateInfo;
	}

	void SceneManager::loadWorldInstance(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& playerPosition, const of::world::LoadArgs loadArgs)
	{
		isLoading = true;
		of::timer::reset(globals::LOADING_TIMER);
		of::timer::reset(globals::TOTAL_TIME_LOADED);

		loadStateMachine.beginLoad(world, loadingScreen, playerPosition, loadArgs);

	}

	void SceneManager::Update()
	{
		if (isLoading)
		{
			auto& timer = of::timer::get(globals::LOADING_TIMER);
			timer.reset();
			while (timer.secondsAsFloat() < 0.05f && isLoading)
			{
				loadStateMachine.load();
			}
		}
	}

	void SceneManager::Simulate(const float fElapsedTime)
	{
		//doDayCycle(fElapsedTime);
		objectHandler.processDeletedObjects(fElapsedTime);
	}

	void SceneManager::SetSceneManager(std::weak_ptr<SceneManager> scene)
	{
		sScene = scene;
	}

	std::weak_ptr<SceneManager> SceneManager::GetSceneManager()
	{
		return sScene;
	}
}
