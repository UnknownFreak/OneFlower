#ifndef LoadingState_HPP
#define LoadingState_HPP

#include <utils/common/string.hpp>

namespace of::world
{
	enum class LoadingState
	{
		UNDEFINED = 0,
		LOAD_MAIN_MENU,
		PREPARE_LOADINGSCREEN,
		BEGIN_LOAD,
		CACHE_ALL_ZONES,
		CACHE_ALL_CUTSCENES,
		UPDATE_LOAD_INFO,
		UNLOAD_OBJECTS,
		LOAD_ALL_PREFABS,
		LOAD_ALL_NAVMESH,
		LOAD_GROUND,

		BUILD_COLLIDERS,
		BUILDING_TILEMAP,
		PRE_BUILDING_OBJECTS,
		BUILD_OBJECTS,
		FINALIZING,
		DONE,

		UNLOAD_ALL,
	};


	inline of::common::String to_string(const LoadingState& state)
	{
		switch (state)
		{
		case LoadingState::UNDEFINED: return "UNDEFINED";
		case LoadingState::LOAD_MAIN_MENU: return "LOAD_MAIN_MENU";
		case LoadingState::PREPARE_LOADINGSCREEN: return "PREPARE_LOADINGSCREEN";
		case LoadingState::BEGIN_LOAD: return "BEGIN_LOAD";
		case LoadingState::CACHE_ALL_ZONES: return "CACHE_ALL_ZONES";
		case LoadingState::CACHE_ALL_CUTSCENES: return "CACHE_ALL_CUTSCENES";
		case LoadingState::UPDATE_LOAD_INFO: return "UPDATE_LOAD_INFO";
		case LoadingState::UNLOAD_OBJECTS: return "UNLOAD_OBJECTS";
		case LoadingState::LOAD_ALL_PREFABS: return "LOAD_ALL_PREFABS";
		case LoadingState::LOAD_ALL_NAVMESH: return "LOAD_ALL_NAVMESH";
		case LoadingState::LOAD_GROUND: return "LOAD_GROUND";
		case LoadingState::BUILD_COLLIDERS: return "BUILDING_COLLIDERS";
		case LoadingState::BUILDING_TILEMAP: return "BUILDING_TILEMAP";
		case LoadingState::PRE_BUILDING_OBJECTS: return "PRE_BUILDING_OBJECTS";
		case LoadingState::BUILD_OBJECTS: return "BUILD_OBJECTS";
		case LoadingState::FINALIZING: return "FINALIZING";
		case LoadingState::DONE: return "DONE";
		case LoadingState::UNLOAD_ALL: return "UNLOAD_ALL";
		}
		return "";
	}
}

#endif 