#ifndef SaveFile_HPP
#define SaveFile_HPP

#include <module/IEngineModule.hpp>
#include <Object/GameObject.hpp>
#include <Quest/QuestState.hpp>
#include <utils/common/string.hpp>
#include <Helpers/Enum/ObjectState.hpp>
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

	class SaveFile : public of::module::interface::IEngineResource<SaveFile>
	{

		Enums::DifficultyLevel diff = Enums::DifficultyLevel::NotSet;
		::Resource::GameMode gameMode;
		of::common::uuid customDiffId = of::common::uuid::nil();
		std::unordered_set<of::common::uuid> lootedContainers;
		std::unordered_set<of::common::uuid> triggerState;
		std::unordered_map<File::Mod::ModFileUUIDHelper, Questing::QuestState> questState;
		std::unordered_map<File::Mod::ModFileUUIDHelper, Core::TickTimerInfo> tickTimers;
		std::unordered_map<of::common::uuid, std::vector<File::Mod::ModFileUUIDHelper>> npcCustomLootStates; // TODO: store the custom items sold to that specific npc.
		std::unordered_map<of::common::uuid, Enums::ObjectState> overridenRenderMode;

		void setPlayerInfo();

	public:
		File::Mod::ModFileUUIDHelper currentZone;
		File::Mod::ModFileUUIDHelper loadingScreen;
		glm::vec3 point;
		GameObject player;

		bool isTriggered(const of::common::uuid& uuid) const;
		void setTriggered(const of::common::uuid& uuid);

		Enums::ObjectState getObjectState(const of::common::uuid& uuid, const Enums::ObjectState& _default);
		void setObjectState(const of::common::uuid& uuid, const Enums::ObjectState& objectState);

		bool isLooted(const of::common::uuid& uuid) const;
		void setLooted(const of::common::uuid& uuid);

		void setQuestState(const File::Mod::ModFileUUIDHelper& quest, const Questing::QuestState& state);
		bool isQuestStored(const File::Mod::ModFileUUIDHelper& questId) const;
		Questing::QuestState& getQuestState(const File::Mod::ModFileUUIDHelper& quest);

		void setTickTimer(const File::Mod::ModFileUUIDHelper& timerId, const Core::TickTimerInfo& timer);
		bool isTimerSaved(const File::Mod::ModFileUUIDHelper& timerId) const;
		Core::TickTimerInfo& getTickTimer(const File::Mod::ModFileUUIDHelper& timerId);

		void newGame(const Enums::DifficultyLevel& diff, const of::common::uuid& customDiffId, const File::Mod::ModFileUUIDHelper& gameMode);
		Enums::DifficultyLevel getDifficulty() const;
		of::common::uuid getCustomDiffId() const;

		File::Mod::ModFileUUIDHelper getGameModeId() const;
		const ::Resource::GameMode& getGameMode() const;

		void save(const of::common::String& fileName);
		void load(const of::common::String& fileName);

		// Inherited via IEngineResource
		virtual of::module::EngineResourceType& getType() const override;
	};
}

#endif