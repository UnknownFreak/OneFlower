#ifndef SaveFile_HPP
#define SaveFile_HPP

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>
#include <file/FileId.hpp>

#include "SaveState.hpp"

#include <object/GameObject.hpp>

#include <unordered_set>
#include <unordered_map>

#include <resource/DifficultyLevel.hpp>
#include <resource/GameMode.hpp>

namespace of::session
{
	class GameSession
	{

		typedef std::unordered_map<of::file::FileId, std::unique_ptr<SaveState>>::const_iterator saveStateIterator;

		of::resource::DifficultyLevel diff = of::resource::DifficultyLevel::NotSet;
		of::resource::GameMode gameMode;
		of::common::uuid customDiffId = of::common::uuid::nil();

		std::unordered_map<of::file::FileId, std::unique_ptr<SaveState>> saveStates;
		std::unordered_map<of::common::uuid, float> despawnTimers;
		std::unordered_map<of::common::uuid, std::vector<of::file::FileId>> npcCustomLootStates; // TODO: store the custom items sold to that specific npc.

		void setPlayerInfo();

	public:
		of::file::FileId currentZone;
		of::file::FileId loadingScreen;
		glm::vec3 point;
		of::object::GameObject* player;

		void setState(const of::file::FileId& uuid, std::unique_ptr<SaveState> state);

		bool exists(const of::file::FileId& uuid);
		bool exists(const of::file::FileId& uuid, const common::String& type);
		void remove(const of::file::FileId& uuid);

		std::unique_ptr<SaveState>& getState(const of::file::FileId& uuid);

		template<class T>
		requires std::derived_from<T, SaveState>
		T* getState(const of::file::FileId& uuid)
		{
			return getState(uuid)->toDerived<T>();
		}

		void setDespawnTimers(const std::unordered_map<of::common::uuid, float>& timers);
		const std::unordered_map<of::common::uuid, float>& getDespawnTimers() const;

		void newGame(const of::resource::DifficultyLevel diff, const of::common::uuid& customDiffId, const of::file::FileId& gameMode);
		of::resource::DifficultyLevel getDifficulty() const;
		of::common::uuid getCustomDiffId() const;

		of::file::FileId getGameModeId() const;
		const of::resource::GameMode& getGameMode() const;

		saveStateIterator begin() const noexcept;
		saveStateIterator end() const noexcept;

		void save(const of::common::String& fileName);
		void load(const of::common::String& fileName);
	};

	GameSession& get();
}

#endif