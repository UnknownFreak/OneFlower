#include "SaveFile.hpp"
#include <cereal\types\unordered_set.hpp>

#include <Object/ObjectInstanceHandler.hpp>
#include <Graphics/Render.hpp>
#include <Graphics/PlayerInteractionPrompt.hpp>
#include <Graphics/UI/PlayerStats.hpp>
#include <Physics/Colliders/VisionCollider.hpp>
#include <Input/PlayerController.hpp>
#include <Quest/Quest.hpp>

#include <File/Asset/Resource/Prefab.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<File::SaveFile>::type = Enums::EngineResourceType::SaveFile;

namespace File
{
	void SaveFile::setPlayerInfo()
	{
		auto& ui = Engine::GetModule<Graphics::UI::UIHandler>();
		auto& objectHandler = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		objectHandler.player = &player;
		ui.addUIContext(Enums::UIContextNames::PlayerStats, std::make_unique<Graphics::UI::PlayerStats>());
		ui.getUIContext<Graphics::UI::PlayerStats>(Enums::UIContextNames::PlayerStats)->setPlayerStats(player.getSharedComponent<Component::Stats>());
		ui.getUIContext<Graphics::UI::PlayerStats>(Enums::UIContextNames::PlayerStats)->update();
	}
	bool SaveFile::isTriggered(const Core::uuid& uuid) const
	{
		return triggerState.find(uuid) != triggerState.end();
	}
	
	void SaveFile::setTriggered(const Core::uuid& uuid)
	{
		triggerState.insert(uuid);
	}

	Enums::ObjectState SaveFile::getObjectState(const Core::uuid& uuid, const Enums::ObjectState& default)
	{
		auto it = overridenRenderMode.find(uuid);
		if (it != overridenRenderMode.end())
			return it->second;
		return default;
	}

	void SaveFile::setObjectState(const Core::uuid& uuid, const Enums::ObjectState& objectState)
	{
		overridenRenderMode[uuid] = objectState;
	}

	bool SaveFile::isLooted(const Core::uuid& uuid) const
	{
		return lootedContainers.find(uuid) != lootedContainers.end();
	}

	void SaveFile::setLooted(const Core::uuid& uuid)
	{
		lootedContainers.insert(uuid);
	}

	void SaveFile::setQuestState(const File::Mod::ModFileUUIDHelper& questId, const Questing::QuestState& state)
	{
		questState[questId] = state;
	}

	bool SaveFile::isQuestStored(const File::Mod::ModFileUUIDHelper& questId) const
	{
		return questState.find(questId) != questState.end();
	}

	Questing::QuestState& SaveFile::getQuestState(const File::Mod::ModFileUUIDHelper& quest)
	{
		return questState.at(quest);
	}

	void SaveFile::setTickTimer(const File::Mod::ModFileUUIDHelper& timerId, const Core::TickTimerInfo& timer)
	{
		tickTimers[timerId] = timer;
	}

	bool SaveFile::isTimerSaved(const File::Mod::ModFileUUIDHelper& timerId) const
	{
		return tickTimers.find(timerId) != tickTimers.end();
	}

	Core::TickTimerInfo& SaveFile::getTickTimer(const File::Mod::ModFileUUIDHelper& timerId)
	{
		return tickTimers.at(timerId);
	}

	void SaveFile::newGame(const Enums::DifficultyLevel& difficulty, const Core::uuid& customDifficultyId, const File::Mod::ModFileUUIDHelper& gameModeId)
	{
		diff = difficulty;
		gameModeId;
		if (!gameModeId.isValid())
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::SaveFile::newGame").Critical("invalidGameModeId:", gameModeId.operator()(),
				" this is very bad...");
#ifndef _DEBUG
				std::exit(-1);
#else
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::SaveFile::newGame").Always("But we're in debug mode so gonna continue anyways...");
#endif // !_DEBUG

		}
		//gameMode = Engine::GetModule<File::Asset::AssetManager>().requestor.requestUniqueInstance<Resource::GameMode>(gameModeId);
		customDiffId = customDifficultyId;
		questState.clear();
		lootedContainers.clear();
		npcCustomLootStates.clear();

		currentZone = gameMode.startingZone;
		loadingScreen = gameMode.loadingScreen;
		point = gameMode.startingPosition;

		if (!gameMode.playerPrefab.isValid())
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::SaveFile::newGame").Error("This is probably not intentional, but player prefab is not valid for gameModeId:", gameModeId.operator()());
		}
		auto prefab = Engine::GetModule<Asset::Manager>().requestor.requestUniqueInstance<::Asset::Resource::Prefab>(gameMode.playerPrefab);
		player = GameObject();

		prefab.createNewInstance(player);
		player.applyGameMode(gameMode.playerModifiers);
		player.tag = "player";
		player.id = Core::uuid::nil();
		player.addComponent<Render>();
		player.addComponent<PlayerInteractionPrompt>();
		player.addComponent<VisionCollider>(glm::vec2{ 45.f, 30.f });
		player.addComponent<Component::Stats>();
		player.addComponent<Component::CombatComponent>();
		player.getComponent<Collider>()->hitboxOffset = { 8.f, 32.f };
		player.addComponent<Component::PlayerController>();
		setPlayerInfo();
	}

	Enums::DifficultyLevel SaveFile::getDifficulty() const
	{
		return diff;
	}

	Core::uuid SaveFile::getCustomDiffId() const
	{
		return customDiffId;
	}

	File::Mod::ModFileUUIDHelper SaveFile::getGameModeId() const
	{
		return gameMode.getModfile();
	}

	const ::Resource::GameMode& SaveFile::getGameMode() const
	{
		return gameMode;
	}


	void SaveFile::save(const Core::String& fileName)
	{
		point = player.getComponent<Component::Transform>()->pos;
		std::ofstream file(Core::savePath + fileName, std::ios::binary | std::ios::out);
		{
			cereal::BinaryOutputArchive mainAr(file);
			mainAr(diff);
			mainAr(gameMode);
			mainAr(customDiffId);
			//mainAr(player);
			mainAr(lootedContainers);
			mainAr(questState);
			mainAr(currentZone);
			mainAr(loadingScreen);
			mainAr(point.x, point.y, point.z);
		}
		file.close();
	}

	void SaveFile::load(const Core::String& fileName)
	{
		player.getComponent<Collider>()->floor = nullptr;
		std::ifstream file(Core::savePath + fileName, std::ios::binary | std::ios::in);
		{
			cereal::BinaryInputArchive mainAr(file);
			mainAr(diff);
			mainAr(gameMode);
			mainAr(customDiffId);
			//mainAr(player);
			mainAr(lootedContainers);
			mainAr(questState);
			mainAr(currentZone);
			mainAr(loadingScreen);
			mainAr(point.x, point.y, point.z);
		}
		point.z += 0.15f;
		file.close();
		setPlayerInfo();
	}

	Enums::EngineResourceType& SaveFile::getType() const
	{
		return type;
	}
}