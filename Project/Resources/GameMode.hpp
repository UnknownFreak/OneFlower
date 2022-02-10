#ifndef GameMode_HPP
#define GameMode_HPP
#include <vector>

#include <Helpers/Vector3.hpp>

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

		ModFileUUIDHelper startingZone;
		ModFileUUIDHelper loadingScreen;
		Core::Vector3f startingPosition;

		GameModeModifier playerModifiers;
		GameModeModifier enemyModifiers;
		std::unordered_map<Core::String, GameModeModifier> bossTagModifiers;

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(gameModeNameStringTranslation);
			ar(startingZone);
			ar(loadingScreen);
			ar(startingPosition);
			ar(playerModifiers);
			ar(enemyModifiers);
			ar(bossTagModifiers);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(gameModeNameStringTranslation);
			ar(startingZone);
			ar(loadingScreen);
			ar(startingPosition); 
			ar(playerModifiers);
			ar(enemyModifiers);
			ar(bossTagModifiers);
			loadTranslation();
		}
	};
}


#endif