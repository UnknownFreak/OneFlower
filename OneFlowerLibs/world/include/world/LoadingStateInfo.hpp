#pragma once

#include <world/LoadingState.hpp>

namespace of::world
{

	class LoadingStateInfo
	{
	public:
		float totalLoadTime = 0.f;

		float loadScreenSetupTime = 0.f;
		float instanceLoadTime = 0.f;

		size_t totalPrefabCount = 0;
		size_t currentPrefabCount = 0;
		float prefabLoadTimer = 0.f;

		size_t totalNavmeshCount = 0;
		size_t currentNavmeshCount = 0;
		float navmeshLoadTimer = 0.f;

		size_t totalGeometryCount = 0;
		size_t currentGeometryCount = 0;
		float geometryLoadTimer = 0.f;

		size_t totalObjectPartCount = 0;
		size_t currentObjectPartCount = 0;
		float objectPartLoadTimer = 0.f;

		size_t totalObjectCount = 0;
		size_t currentObjectCount = 0;
		float objectLoadTimer = 0.f;

		size_t currentLoadCount = 0;
		size_t totalLoadCount = 0;

		size_t currentZoneCount = 0;
		size_t totalZoneCount = 0;
		float totalZoneUpdateCountTimer = 0.f;

		const LoadingState& theState;
		const bool& isLoading;

		LoadingStateInfo(const LoadingState& theState, const bool& isLoading);
	};

}