#pragma once

#include <vector>
#include <memory>

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>

#include <file/FileId.hpp>

#include <module/IEngineModule.hpp>
#include <module/ObjectInstanceHandler.hpp>
#include <module/SaveFile.hpp>
#include <module/ModuleManager.hpp>

#include <resource/WorldInstance.hpp>
#include <scene/LoadingState.hpp>
#include <scene/LoadingStateInfo.hpp>
#include <scene/LoadArgs.hpp>

namespace of::module::globals
{
	static const of::common::String LOADING_TIMER = "LOADING_TIMER";
	static const of::common::String TOTAL_TIME_LOADED = "TOTAL_TIME_LOADED";
	static const of::common::String TOTAL_TIME_LOADED_PART = "TOTAL_TIME_LOADED_PART";
}

namespace of::module
{
	class SceneManager : public of::module::interface::IEngineResource<SceneManager>
	{

		class LoadingStateMachine
		{
			void loadMainMenu();

			void prepareLoadingScreen();
			void beginLoad();
			void cacheAllZones();
			void updateZoneInfo();
			void unloadObjects();
			void loadAllPrefabs();
			void loadAllNavmesh();
			void loadGround();
			void buildColliders();
			void preBuildObjects();
			void buildObjects();
			void finalize();
			void done();
			void unloadAll();
		public:

			of::world::LoadingStateInfo loadingStateInfo;
			of::world::LoadingState loadstate;

			of::file::FileId worldToLoad;
			of::file::FileId loadingScreenToLoad;
			of::resource::WorldInstance instanceToLoad;
			SceneManager& parent;

			std::map<of::file::FileId, of::file::FileId> objectChunkToInstanceId;

			std::vector<of::file::FileId> allInstances;

			bool navMeshLoaded = false;
			of::world::LoadArgs loadArgs = of::world::LoadArgs::UNDEFINED;


			const of::file::FileId& getCurrentWorld() const;
			const of::file::FileId& getCurrentLoadingScreen() const;

			std::vector<of::resource::ObjectInfo> buffer;
			glm::vec3 playerPos;

			LoadingStateMachine(SceneManager& parent);

			void beginLoad(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& position, const of::world::LoadArgs& loadArgs);
			void load();
			// TODO
			//void unloadAllAssets();

		};

		LoadingStateMachine loadStateMachine;

		of::module::ObjectInstanceHandler& objectHandler;
		of::module::SaveFile& saveFile;

		//void doDayCycle(const float& fElapsedTime);

	public:
		bool isLoading = false;
		SceneManager();
		SceneManager(const SceneManager& copy);

	//#ifdef _DEBUG
		//void setCurrentTime(const float& currentTime);

	//#endif

		of::world::LoadingStateInfo& getLoadingStateInfo();

		void newGame();
		void save(const of::common::String& fileName);
		void load(const of::common::String& fileName);
		void initialize();

		void loadWorldInstance(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& playerPosition = {0.f, 0.f, 0.f}, const of::world::LoadArgs& loadArgs = of::world::LoadArgs::GAME_ALREADY_LOADED_JUST_LOAD);
	
		virtual void Update();
		virtual void Simulate(const float& fElapsedTime);

		// Inherited via IEngineResource
		virtual of::module::EngineResourceType& getType() const override;

	};
}
