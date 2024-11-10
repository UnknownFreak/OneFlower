#ifndef SaveFile_HPP
#define SaveFile_HPP

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>
#include <asset/assetId.hpp>

#include "SaveState.hpp"

#include <object/GameObject.hpp>

#include <vector>
#include <unordered_map>

#include <resource/DifficultyLevel.hpp>
#include <resource/GameMode.hpp>

namespace of::session
{
	class GameSession
	{

		typedef std::unordered_map<of::asset::AssetId, std::unique_ptr<SaveState>>::const_iterator saveStateIterator;

		of::resource::DifficultyLevel diff = of::resource::DifficultyLevel::NotSet;
		of::resource::GameMode gameMode;
		of::common::uuid customDiffId = of::common::uuid::nil();

		std::unordered_map<of::asset::AssetId, std::unique_ptr<SaveState>> saveStates;
		std::unordered_map<of::common::uuid, float> despawnTimers;
		std::unordered_map<of::common::uuid, std::vector<of::asset::AssetId>> npcCustomLootStates; // TODO: store the custom items sold to that specific npc.

		//TODO: hooks to return true/false?
		std::vector<std::function<void(GameSession&)>> newGameHooks;
		std::vector<std::function<void(GameSession&)>> saveGameHooks;
		std::vector<std::function<void(GameSession&)>> loadGameHooks;

		void setPlayerInfo();

	public:

		void addNewGameHook(std::function<void(GameSession&)> func)
		{
			newGameHooks.push_back(func);
		}

		void addSaveGameHook(std::function<void(GameSession&)> func)
		{
			saveGameHooks.push_back(func);
		}

		void addLoadGameHook(std::function<void(GameSession&)> func)
		{
			loadGameHooks.push_back(func);
		}

		of::asset::AssetId currentZone;
		of::asset::AssetId loadingScreen;
		glm::vec3 point;
		of::object::GameObject* player = nullptr;

		void setState(const of::asset::AssetId& uuid, std::unique_ptr<SaveState> state);

		bool exists(const of::asset::AssetId& uuid);
		bool exists(const of::asset::AssetId& uuid, const common::String& type);
		void remove(const of::asset::AssetId& uuid);

		std::unique_ptr<SaveState>& getState(const of::asset::AssetId& uuid);

		template<class T>
		requires std::derived_from<T, SaveState>
		T* getState(const of::asset::AssetId& uuid)
		{
			return getState(uuid)->toDerived<T>();
		}

		void setDespawnTimers(const std::unordered_map<of::common::uuid, float>& timers);
		const std::unordered_map<of::common::uuid, float>& getDespawnTimers() const;

		void newGame(const of::resource::DifficultyLevel diff, const of::common::uuid& customDiffId, const of::asset::AssetId& gameMode);
		of::resource::DifficultyLevel getDifficulty() const;
		of::common::uuid getCustomDiffId() const;

		of::asset::AssetId getGameModeId() const;
		const of::resource::GameMode& getGameMode() const;

		saveStateIterator begin() const noexcept;
		saveStateIterator end() const noexcept;

		void save(const of::common::String& fileName);
		void load(const of::common::String& fileName);
	};

	GameSession& get();
}

#endif