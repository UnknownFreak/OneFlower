#ifndef GameMode_HPP
#define GameMode_HPP
#include <vector>

#include <cereal/cereal.hpp>

#include <glm/vec3.hpp>

#include <Interfaces/IRequestable.hpp>
#include <Helpers/String.hpp>

#include "GameModeModifier.hpp"

namespace Resource
{
	class GameMode : public Interfaces::IRequestable
	{
		void loadTranslation();
	public:
		Core::uuid gameModeNameStringTranslation;

		Core::String gameModeName;

		File::Mod::ModFileUUIDHelper startingZone;
		File::Mod::ModFileUUIDHelper loadingScreen;
		glm::vec3 startingPosition;

		File::Mod::ModFileUUIDHelper playerPrefab;

		GameModeModifier playerModifiers;
		GameModeModifier enemyModifiers;
		std::unordered_map<Core::String, GameModeModifier> tagModifiers;

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
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
			ar(cereal::base_class<Interfaces::IRequestable>(this));
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