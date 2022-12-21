#ifndef SaveFile_HPP
#define SaveFile_HPP

#include <module/IEngineModule.hpp>

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>
#include <file/FileId.hpp>

#include "SaveState.hpp"

#include <object/GameObject.hpp>

#include <unordered_set>
#include <unordered_map>

#include <resource/DifficultyLevel.hpp>
#include <resource/GameMode.hpp>

namespace of::module
{

	class SaveFile : public of::module::interface::IEngineResource<SaveFile>
	{

		of::resource::DifficultyLevel diff = of::resource::DifficultyLevel::NotSet;
		of::resource::GameMode gameMode;
		of::common::uuid customDiffId = of::common::uuid::nil();

		std::unordered_map<of::file::FileId, std::unique_ptr<save_state::SaveState>> saveStates;


		std::unordered_map<of::common::uuid, std::vector<of::file::FileId>> npcCustomLootStates; // TODO: store the custom items sold to that specific npc.

		void setPlayerInfo();

	public:
		of::file::FileId currentZone;
		of::file::FileId loadingScreen;
		glm::vec3 point;
		of::object::GameObject player;

		void setState(const of::file::FileId& uuid, std::unique_ptr<save_state::SaveState> state);

		bool exists(const of::file::FileId& uuid);
		bool exists(const of::file::FileId& uuid, const common::String& type);

		std::unique_ptr<save_state::SaveState>& getState(const of::file::FileId& uuid);

		template<class T>
		requires std::derived_from<T, save_state::SaveState>
		T* getState(const of::file::FileId& uuid)
		{
			return getState(uuid)->toDerived<T>();
		}

		void newGame(const of::resource::DifficultyLevel& diff, const of::common::uuid& customDiffId, const of::file::FileId& gameMode);
		of::resource::DifficultyLevel getDifficulty() const;
		of::common::uuid getCustomDiffId() const;

		of::file::FileId getGameModeId() const;
		const of::resource::GameMode& getGameMode() const;

		void save(const of::common::String& fileName);
		void load(const of::common::String& fileName);

		// Inherited via IEngineResource
		virtual of::module::EngineResourceType& getType() const override;
	};
}

#endif