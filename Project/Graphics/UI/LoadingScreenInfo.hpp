#ifndef LoadingScreenInfo_HPP
#define LoadingScreenInfo_HPP

#include "UIContext.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Helpers/Enum/LoadingState.hpp>

namespace Graphics::UI
{

	class LoadingScreenInfo : public Graphics::UI::UIContext
	{
		sf::Font f;
		sf::Text t;

	public:
		sf::Time totalLoadTime;

		sf::Time loadScreenSetupTime;
		sf::Time instanceLoadTime;

		size_t totalAtlasCount = 0;
		size_t currentAtlasCount = 0;
		sf::Time atlasLoadTimer;

		size_t totalPrefabCount = 0;
		size_t currentPrefabCount = 0;
		sf::Time prefabLoadTimer;


		size_t totalTileCount = 0;
		size_t currentTileCount = 0;
		sf::Time tileLoadTimer;

		size_t totalTileBuildingCount = 0;
		size_t currentTileBuildingCount = 0;
		sf::Time tileBuildLoadTimer;

		size_t totalColliderCount = 0;
		size_t currentColliderCount = 0;
		sf::Time colliderLoadTimer;

		size_t totalColliderBuildingCount = 0;
		size_t currentColliderBuildingCount = 0;
		sf::Time colliderBuildingLoadTimer;

		size_t totalObjectPartCount = 0;
		size_t currentObjectPartCount = 0;
		sf::Time objectPartLoadTimer;

		size_t totalObjectCount = 0;
		size_t currentObjectCount = 0;
		sf::Time objectLoadTimer;

		size_t currentLoadCount = 0;
		size_t totalLoadCount = 0;
		const Enums::LoadingState& theState;

		LoadingScreenInfo(const Enums::LoadingState& theState);

		// Inherited via UIContext
		virtual void readInput() override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void update() override;

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
	};
}

#endif