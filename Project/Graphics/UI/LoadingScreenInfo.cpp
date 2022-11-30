#include "LoadingScreenInfo.hpp"

#include <Module/Globals.hpp>
#include <File/GameConfig.hpp>

#include <imgui/imgui.h>

Graphics::UI::LoadingScreenInfo::LoadingScreenInfo(const Enums::LoadingState& theState) : UIContext(swizzle::input::Keys::KeyNone, "LoadingScreenInfo", true), theState(theState)
{
	visible = of::engine::GetModule<Globals>().boolGlobals[Globals::B_GLOBAL_LOADINGSCREENINFO];
	auto height = of::engine::GetModule<EngineModule::GameConfig>().videoMode.second;
	pos = { 5, height - 320.f };
}

void Graphics::UI::LoadingScreenInfo::readInput()
{
}

void Graphics::UI::LoadingScreenInfo::render()
{
	if (visible)
	{
		ImGui::Begin("LoadingScreenInfo", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs);
		{
			ImGui::SetWindowPos(pos);
			ImGui::Text("%s", t.c_str());
		}
		ImGui::End();
	}
}

void Graphics::UI::LoadingScreenInfo::update()
{
	t =
		"\nElapsed time: " + std::to_string(totalLoadTime) + 
		"\nLoading State: " + Enums::to_string(theState) +
		"\nProgress (Total): " + std::to_string(currentLoadCount) +"/" + std::to_string(totalLoadCount) +
		"\nTime (Prepare load): " + std::to_string(instanceLoadTime) +
		"\nProgress (Tile Atlas): " + std::to_string(currentAtlasCount) +"/" + std::to_string(totalAtlasCount) +
		"\n    Elapsed: " + std::to_string(atlasLoadTimer) +
		"\nProgress (Prefabs): " + std::to_string(currentPrefabCount) +"/" + std::to_string(totalPrefabCount) +
		"\n    Elapsed: " + std::to_string(prefabLoadTimer) +
		"\nProgress (Tiles): " + std::to_string(currentTileCount) +"/" + std::to_string(totalTileCount) +
		"\n    Elapsed: " + std::to_string(tileLoadTimer) +
		"\nProgress (Tile Building): " + std::to_string(currentTileBuildingCount) +"/" + std::to_string(totalTileBuildingCount) +
		"\n    Elapsed: " + std::to_string(tileBuildLoadTimer) +
		"\nProgress (Collider): " + std::to_string(currentColliderCount) +"/" + std::to_string(totalColliderCount) +
		"\n    Elapsed: " + std::to_string(colliderLoadTimer) +
		"\nProgress (Building Colliders): " + std::to_string(currentColliderBuildingCount) +"/" + std::to_string(totalColliderBuildingCount) +
		"\n    Elapsed: " + std::to_string(colliderBuildingLoadTimer) +
		"\nProgress (Pre building objects): " + std::to_string(currentObjectPartCount) + "/" + std::to_string(totalObjectPartCount) +
		"\n    Elapsed: " + std::to_string(objectPartLoadTimer) + 
		"\nProgress (Building objects): " + std::to_string(currentObjectCount) + "/" + std::to_string(totalObjectCount) +
		"\n    Elapsed: " + std::to_string(objectLoadTimer) +
		""
	;
}

void Graphics::UI::LoadingScreenInfo::onMouseHover(const glm::vec2&)
{
}
