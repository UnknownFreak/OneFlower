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
		std::unordered_map<of::file::FileId, Questing::QuestState> questState;
		std::unordered_map<of::file::FileId, Core::TickTimerInfo> tickTimers;
		std::unordered_map<of::common::uuid, std::vector<of::file::FileId>> npcCustomLootStates; // TODO: store the custom items sold to that specific npc.
		std::unordered_map<of::common::uuid, Enums::ObjectState> overridenRenderMode;

		void setPlayerInfo();

	public:
		of::file::FileId currentZone;
		of::file::FileId loadingScreen;
		glm::vec3 point;
		GameObject player;

		bool isTriggered(const of::common::uuid& uuid) const;
		void setTriggered(const of::common::uuid& uuid);

		Enums::ObjectState getObjectState(const of::common::uuid& uuid, const Enums::ObjectState& _default);
		void setObjectState(const of::common::uuid& uuid, const Enums::ObjectState& objectState);

		bool isLooted(const of::common::uuid& uuid) const;
		void setLooted(const of::common::uuid& uuid);

		void setQuestState(const of::file::FileId& quest, const Questing::QuestState& state);
		bool isQuestStored(const of::file::FileId& questId) const;
		Questing::QuestState& getQuestState(const of::file::FileId& quest);

		void setTickTimer(const of::file::FileId& timerId, const Core::TickTimerInfo& timer);
		bool isTimerSaved(const of::file::FileId& timerId) const;
		Core::TickTimerInfo& getTickTimer(const of::file::FileId& timerId);

		void newGame(const Enums::DifficultyLevel& diff, const of::common::uuid& customDiffId, const of::file::FileId& gameMode);
		Enums::DifficultyLevel getDifficulty() const;
		of::common::uuid getCustomDiffId() const;

		of::file::FileId getGameModeId() const;
		const ::Resource::GameMode& getGameMode() const;

		void save(const of::common::String& fileName);
		void load(const of::common::String& fileName);

		// Inherited via IEngineResource
		virtual of::module::EngineResourceType& getType() const override;
	};
}

#endif