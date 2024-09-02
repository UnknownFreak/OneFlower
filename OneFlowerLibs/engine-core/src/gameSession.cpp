#include <session/gameSession.hpp>

#include <session/internalGameSession.hpp>

#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/archives/binary.hpp>

#include <object/InstanceHandler.hpp>
#include <logger/Logger.hpp>

of::session::GameSession* g_gameSession = nullptr;

namespace of::session
{

	void GameSession::setPlayerInfo()
	{
	}

	void GameSession::setState(const of::file::FileId& uuid, std::unique_ptr<SaveState> state)
	{
		saveStates[uuid] = std::move(state);
	}

	bool GameSession::exists(const of::file::FileId& uuid)
	{
		return saveStates.find(uuid) != saveStates.end();
	}

	bool GameSession::exists(const of::file::FileId& uuid, const of::common::String& type_)
	{
		return exists(uuid) && saveStates[uuid]->isOfType(type_);
	}

	void GameSession::remove(const of::file::FileId& uuid)
	{
		saveStates.erase(uuid);
	}

	std::unique_ptr<SaveState>& GameSession::getState(const of::file::FileId& uuid)
	{
		return saveStates[uuid];
	}

	of::resource::DifficultyLevel GameSession::getDifficulty() const
	{
		return diff;
	}

	of::common::uuid GameSession::getCustomDiffId() const
	{
		return customDiffId;
	}

	of::file::FileId GameSession::getGameModeId() const
	{
		return gameMode.getModfile();
	}

	const of::resource::GameMode& GameSession::getGameMode() const
	{
		return gameMode;
	}

	GameSession::saveStateIterator GameSession::begin() const noexcept
	{
		return saveStates.begin();
	}
	GameSession::saveStateIterator GameSession::end() const noexcept
	{
		return saveStates.end();
	}

	void GameSession::setDespawnTimers(const std::unordered_map<of::common::uuid, float>& timers)
	{
		despawnTimers = timers;
	}

	const std::unordered_map<of::common::uuid, float>& GameSession::getDespawnTimers() const
	{
		return despawnTimers;
	}

	void GameSession::newGame(const of::resource::DifficultyLevel difficulty, const of::common::uuid& customDifficultyId, const of::file::FileId& gameModeId)
	{
		diff = difficulty;
		gameModeId;
		if (!gameModeId.isValid())
		{
			of::logger::get().getLogger("File::SaveFile").Critical("Invalid GameModeId:", gameModeId.operator()(),
				" this is very bad...");
#ifndef _DEBUG
			std::exit(-1);
#else
			of::logger::get().getLogger("File::SaveFile").Always("But we're in debug mode so gonna continue anyways...");
#endif // !_DEBUG

		}
		//gameMode = Engine::GetModule<File::Asset::AssetManager>().requestor.requestUniqueInstance<Resource::GameMode>(gameModeId);
		customDiffId = customDifficultyId;
		saveStates.clear();
		npcCustomLootStates.clear();

		currentZone = gameMode.startingZone;
		loadingScreen = gameMode.loadingScreen;
		point = gameMode.startingPosition;

		if (!gameMode.playerPrefab.isValid())
		{
			of::logger::get().getLogger("File::SaveFile").Error("This is probably not intentional, but player prefab is not valid for gameModeId:", gameModeId.operator()());
		}
		
		auto& objectHandler = of::object::get();

		player = objectHandler.createPlayer();

		//auto prefab = of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<::Asset::Resource::Prefab>(gameMode.playerPrefab);
		// prefab.createNewPlayerInstance(&player);
		//player->initialize();

		//prefab.createNewPlayerInstance(player);

		//player.addComponent<Render>();
		//player.addComponent<PlayerInteractionPrompt>();
		//player.addComponent<Component::Stats>();
		//player.addComponent<Component::CombatComponent>();
		//player.removeComponent<Component::AI>();
		//player.addComponent<Component::PlayerController>();
		setPlayerInfo();
	}

	void GameSession::save(const of::common::String& fileName)
	{
		//point = player.getComponent<Component::Transform>()->pos;
		std::ofstream file(of::common::savePath + fileName, std::ios::binary | std::ios::out);
		{
			cereal::BinaryOutputArchive mainAr(file);
			mainAr(diff);
			mainAr(gameMode);
			mainAr(customDiffId);
			mainAr(*player);
			mainAr(saveStates);
			mainAr(despawnTimers);
			mainAr(currentZone);
			mainAr(loadingScreen);
			mainAr(point.x, point.y, point.z);
		}
		file.close();
	}

	void GameSession::load(const of::common::String& fileName)
	{
		auto& objectHandler = of::object::get();
		player = objectHandler.createPlayer();
		std::ifstream file(of::common::savePath + fileName, std::ios::binary | std::ios::in);
		{
			cereal::BinaryInputArchive mainAr(file);
			mainAr(diff);
			mainAr(gameMode);
			mainAr(customDiffId);
			mainAr(*player);
			mainAr(saveStates);
			mainAr(despawnTimers);
			mainAr(currentZone);
			mainAr(loadingScreen);
			mainAr(point.x, point.y, point.z);
		}
		point.z += 0.15f;
		file.close();
		setPlayerInfo();
	}


	void init()
	{
		if (g_gameSession == nullptr)
		{
			g_gameSession = new GameSession();
		}
	}

	void shutdown()
	{
		delete g_gameSession;
		g_gameSession = nullptr;
	}

	GameSession& get()
	{
		return *g_gameSession;
	}
}