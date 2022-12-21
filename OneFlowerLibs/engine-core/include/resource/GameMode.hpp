#ifndef GameMode_HPP
#define GameMode_HPP
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>

#include <glm/vec3.hpp>

#include <file/archive/Requestable.hpp>
#include <utils/common/String.hpp>

#include "GameModeModifier.hpp"

namespace of::resource
{
	class GameMode : public of::file::archive::Requestable
	{
		void loadTranslation();
	public:
		of::common::uuid gameModeNameStringTranslation;

		of::common::String gameModeName;

		of::file::FileId startingZone;
		of::file::FileId loadingScreen;
		glm::vec3 startingPosition;

		of::file::FileId playerPrefab;

		GameModeModifier playerModifiers;
		GameModeModifier enemyModifiers;
		std::unordered_map<of::common::String, GameModeModifier> tagModifiers;

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(gameModeNameStringTranslation);
			ar(startingZone);
			ar(loadingScreen);
			ar(startingPosition.x, startingPosition.y, startingPosition.z);
			ar(playerModifiers);
			ar(enemyModifiers);
			ar(tagModifiers);
			ar(playerPrefab);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(gameModeNameStringTranslation);
			ar(startingZone);
			ar(loadingScreen);
			ar(startingPosition.x, startingPosition.y, startingPosition.z);
			ar(playerModifiers);
			ar(enemyModifiers);
			ar(tagModifiers);
			ar(playerPrefab);
			loadTranslation();
		}
	};
}


#endif