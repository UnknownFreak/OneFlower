#pragma once
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>

#include <glm/vec3.hpp>

#include <asset/iAsset.hpp>
#include <utils/common/String.hpp>

#include "GameModeModifier.hpp"

namespace of::resource
{
	class GameMode : public of::asset::IAsset
	{
		void loadTranslation();
	public:
		of::common::uuid gameModeNameStringTranslation;

		of::common::String gameModeName;

		of::asset::AssetId startingZone;
		of::asset::AssetId loadingScreen;
		glm::vec3 startingPosition;

		of::asset::AssetId playerPrefab;

		GameModeModifier playerModifiers;
		GameModeModifier enemyModifiers;
		std::unordered_map<of::common::String, GameModeModifier> tagModifiers;

		// Inherited via IRequestable
		virtual of::asset::TypeInfo getTrait() const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAsset>(this));
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
			ar(cereal::base_class<IAsset>(this));
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
