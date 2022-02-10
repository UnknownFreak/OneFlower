#ifndef SaveFile_HPP
#define SaveFile_HPP

#include <Interfaces/IEngineModule.hpp>
#include <Object/GameObject.hpp>
#include <Quest/QuestState.hpp>
#include <Helpers/String.hpp>
#include <Helpers/TickTimer.hpp>

#include <unordered_set>
#include <unordered_map>
#include <Helpers/Enum/QuestState.hpp>
#include <Helpers/Enum/DifficultyLevels.hpp>

#include <Resources/GameMode.hpp>

namespace Questing {
	class Quest;
}

namespace File
{

	class SaveFile : public Interfaces::IEngineResource<SaveFile>
	{

		Enums::DifficultyLevel diff = Enums::DifficultyLevel::NotSet;
		Resource::GameMode gameMode;
		Core::uuid customDiffId = Core::uuid::nil();
		std::unordered_set<Core::uuid> lootedContainers;
		std::unordered_set<Core::uuid> triggerState;
		std::unordered_map<ModFileUUIDHelper, Questing::QuestState> questState;
		std::unordered_map<ModFileUUIDHelper, Core::TickTimerInfo> tickTimers;
		std::unordered_map<Core::uuid, std::vector<ModFileUUIDHelper>> npcCustomLootStates; // TODO: store the custom items sold to that specific npc.

		void setPlayerInfo();

	public:
		ModFileUUIDHelper currentZone;
		ModFileUUIDHelper loadingScreen;
		Core::Vector3f point;
		GameObject player;

		bool isTriggered(const Core::uuid& uuid) const;
		void setTriggered(const Core::uuid& uuid);

		bool isLooted(const Core::uuid& uuid) const;
		void setLooted(const Core::uuid& uuid);

		void setQuestState(const ModFileUUIDHelper& quest, const Questing::QuestState& state);
		bool isQuestStored(const ModFileUUIDHelper& questId) const;
		Questing::QuestState& getQuestState(const ModFileUUIDHelper& quest);

		void setTickTimer(const ModFileUUIDHelper& timerId, const Core::TickTimerInfo& timer);
		bool isTimerSaved(const ModFileUUIDHelper& timerId) const;
		Core::TickTimerInfo& getTickTimer(const ModFileUUIDHelper& timerId);

		void newGame(const Enums::DifficultyLevel& diff, const Core::uuid& customDiffId, const ModFileUUIDHelper& gameMode);
		Enums::DifficultyLevel getDifficulty() const;
		Core::uuid getCustomDiffId() const;

		ModFileUUIDHelper getGameModeId() const;
		const Resource::GameMode& getGameMode() const;

		void save(const Core::String& fileName);
		void load(const Core::String& fileName);

		// Inherited via IEngineResource
		virtual Enums::EngineResourceType& getType() const override;
	};
}

#endif