#include <module/SaveFile.hpp>

#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/archives/binary.hpp>

#include <module/ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::SaveFile>::type = of::module::EngineResourceType::SaveFile;

namespace of::module
{


	void SaveFile::setState(const of::file::FileId& uuid, std::unique_ptr<save_state::SaveState> state)
	{
		saveStates[uuid] = std::move(state);
	}

	bool SaveFile::exists(const of::file::FileId& uuid)
	{
		return saveStates.find(uuid) != saveStates.end();
	}

	bool SaveFile::exists(const of::file::FileId& uuid, const of::common::String& type)
	{
		return exists(uuid) && saveStates[uuid]->isOfType(type);
	}

	std::unique_ptr<save_state::SaveState>& SaveFile::getState(const of::file::FileId& uuid)
	{
		return saveStates[uuid];
	}


	of::resource::DifficultyLevel SaveFile::getDifficulty() const
	{
		return diff;
	}

	of::common::uuid SaveFile::getCustomDiffId() const
	{
		return customDiffId;
	}

	of::file::FileId SaveFile::getGameModeId() const
	{
		return gameMode.getModfile();
	}

	const of::resource::GameMode& SaveFile::getGameMode() const
	{
		return gameMode;
	}


	void SaveFile::newGame(const of::resource::DifficultyLevel& difficulty, const of::common::uuid& customDifficultyId, const of::file::FileId& gameModeId)
	{
		diff = difficulty;
		gameModeId;
		if (!gameModeId.isValid())
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("File::SaveFile").Critical("Invalid GameModeId:", gameModeId.operator()(),
				" this is very bad...");
#ifndef _DEBUG
			std::exit(-1);
#else
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("File::SaveFile").Always("But we're in debug mode so gonna continue anyways...");
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
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("File::SaveFile").Error("This is probably not intentional, but player prefab is not valid for gameModeId:", gameModeId.operator()());
		}
		//auto prefab = of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<::Asset::Resource::Prefab>(gameMode.playerPrefab);
		//player = GameObject();

		//prefab.createNewPlayerInstance(player);
		player.tag = "player";
		player.id = of::common::uuid::nil();
		//player.addComponent<Render>();
		//player.addComponent<PlayerInteractionPrompt>();
		//player.addComponent<Component::Stats>();
		//player.addComponent<Component::CombatComponent>();
		//player.removeComponent<Component::AI>();
		//player.addComponent<Component::PlayerController>();
		setPlayerInfo();
	}

	void SaveFile::save(const of::common::String& fileName)
	{
		//point = player.getComponent<Component::Transform>()->pos;
		std::ofstream file(of::common::savePath + fileName, std::ios::binary | std::ios::out);
		{
			cereal::BinaryOutputArchive mainAr(file);
			mainAr(diff);
			mainAr(gameMode);
			mainAr(customDiffId);
			mainAr(player);
			mainAr(saveStates);
			mainAr(currentZone);
			mainAr(loadingScreen);
			mainAr(point.x, point.y, point.z);
		}
		file.close();
	}

	void SaveFile::load(const of::common::String& fileName)
	{
		std::ifstream file(of::common::savePath + fileName, std::ios::binary | std::ios::in);
		{
			cereal::BinaryInputArchive mainAr(file);
			mainAr(diff);
			mainAr(gameMode);
			mainAr(customDiffId);
			mainAr(player);
			mainAr(saveStates);
			mainAr(currentZone);
			mainAr(loadingScreen);
			mainAr(point.x, point.y, point.z);
		}
		point.z += 0.15f;
		file.close();
		setPlayerInfo();
	}

	of::module::EngineResourceType& SaveFile::getType() const
	{
		return type;
	}
}