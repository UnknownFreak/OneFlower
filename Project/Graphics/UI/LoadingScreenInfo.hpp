#ifndef LoadingScreenInfo_HPP
#define LoadingScreenInfo_HPP

#include "UIContext.hpp"

#include <Helpers/Enum/LoadingState.hpp>

namespace Graphics::UI
{

	class LoadingScreenInfo : public Graphics::UI::UIContext
	{
		Core::String t;
		ImVec2 pos;

	public:
		float totalLoadTime = 0.f;

		float loadScreenSetupTime = 0.f;
		float instanceLoadTime = 0.f;

		size_t totalAtlasCount = 0;
		size_t currentAtlasCount = 0;
		float atlasLoadTimer = 0.f;

		size_t totalPrefabCount = 0;
		size_t currentPrefabCount = 0;
		float prefabLoadTimer = 0.f;


		size_t totalTileCount = 0;
		size_t currentTileCount = 0;
		float tileLoadTimer = 0.f;

		size_t totalTileBuildingCount = 0;
		size_t currentTileBuildingCount = 0;
		float tileBuildLoadTimer = 0.f;

		size_t totalColliderCount = 0;
		size_t currentColliderCount = 0;
		float colliderLoadTimer = 0.f;

		size_t totalColliderBuildingCount = 0;
		size_t currentColliderBuildingCount = 0;
		float colliderBuildingLoadTimer = 0.f;

		size_t totalObjectPartCount = 0;
		size_t currentObjectPartCount = 0;
		float objectPartLoadTimer = 0.f;

		size_t totalObjectCount = 0;
		size_t currentObjectCount = 0;
		float objectLoadTimer = 0.f;

		size_t currentLoadCount = 0;
		size_t totalLoadCount = 0;
		const Enums::LoadingState& theState;

		LoadingScreenInfo(const Enums::LoadingState& theState);

		// Inherited via UIContext
		virtual void readInput() override;
		virtual void render() override;
		virtual void update() override;

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
	};
}

#endif