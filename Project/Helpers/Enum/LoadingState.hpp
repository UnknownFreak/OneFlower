#ifndef LoadingState_HPP
#define LoadingState_HPP

namespace Enums
{
	enum class LoadingState
	{
		UNDEFINED = 0,
		PREPARE_LOADINGSCREEN,
		BEGIN_LOAD,
		UNLOAD_OLD_OBJECTS,
		LOADING_TILES,
		LOADING_ATLAS,
		LOADING_PREFABS,
		LOADING_COLLIDERS,

		BUILD_COLLIDERS,
		BUILDING_TILEMAP,
		PRE_BUILDING_OBJECTS,
		BUILDING_OBJECTS,
		FINALIZING,
		DONE,
	};


	inline of::common::String to_string(const LoadingState& state)
	{
		switch (state)
		{
		case LoadingState::UNDEFINED: return "UNDEFINED";
		case LoadingState::PREPARE_LOADINGSCREEN: return "PREPARE_LOADINGSCREEN";
		case LoadingState::BEGIN_LOAD: return "BEGIN_LOAD";
		case LoadingState::UNLOAD_OLD_OBJECTS: return "UNLOAD_OLD_OBJECTS";
		case LoadingState::LOADING_TILES: return "LOADING_TILES";
		case LoadingState::LOADING_ATLAS: return "LOADING_ATLAS";
		case LoadingState::LOADING_PREFABS: return "LOADING_PREFABS";
		case LoadingState::LOADING_COLLIDERS: return "LOADING_COLLIDERS";
		case LoadingState::BUILD_COLLIDERS: return "BUILDING_COLLIDERS";
		case LoadingState::BUILDING_TILEMAP: return "BUILDING_TILEMAP";
		case LoadingState::PRE_BUILDING_OBJECTS: return "PRE_BUILDING_OBJECTS";
		case LoadingState::BUILDING_OBJECTS: return "BUILDING_OBJECTS";
		case LoadingState::FINALIZING: return "FINALIZING";
		case LoadingState::DONE: return "DONE";
		}
		return "";
	}
}

#endif 