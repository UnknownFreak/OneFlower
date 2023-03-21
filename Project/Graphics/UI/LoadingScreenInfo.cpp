#include "LoadingScreenInfo.hpp"

#include <Module/Globals.hpp>
#include <File/GameConfig.hpp>

#include <imgui/imgui.h>
#include <Module/sceneManager.hpp>

Graphics::UI::LoadingScreenInfo::LoadingScreenInfo() : UIContext(swizzle::input::Keys::KeyNone, "LoadingScreenInfo", true), info(of::engine::GetModule<of::module::SceneManager>().getLoadingStateInfo())
{
	visible = of::engine::GetModule<Globals>().boolGlobals[Globals::B_GLOBAL_LOADINGSCREENINFO];
	auto height = of::engine::GetModule<EngineModule::GameConfig>().videoMode.second;
	pos = { 5, height - 420.f };
}

void Graphics::UI::LoadingScreenInfo::readInput()
{
}

void Graphics::UI::LoadingScreenInfo::render()
{
	if (visible && info.isLoading)
	{
		ImGui::SetWindowFocus();
		ImGui::Begin("LoadingScreenInfo", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs |ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
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
		"\nIs Loading: " + std::to_string(info.isLoading) + 
		"\nElapsed time: " + std::to_string(info.totalLoadTime) +
		"\nLoading State: " + of::world::to_string(info.theState) +
		"\nProgress (Total): " + std::to_string(info.currentLoadCount) + "/" + std::to_string(info.totalLoadCount) +
		"\nTime (Prepare load): " + std::to_string(info.instanceLoadTime) +
		"\nProgress (CutScenes): " + std::to_string(info.currentCutSceneCount) + "/" + std::to_string(info.totalCutSceneCount) +
		"\n    Elapsed: " + std::to_string(info.totalCutSceneCountTimer) +
		"\nProgress (Instances): " + std::to_string(info.currentZoneCount) + "/" + std::to_string(info.totalZoneCount) +
		"\n    Elapsed: " + std::to_string(info.totalZoneUpdateCountTimer) +
		"\nProgress (Unload objects): " + "TODO / TODO" +
		"\n    Elapsed: " + "N/A" +
		"\nProgress (Prefabs): " + std::to_string(info.currentPrefabCount) + "/" + std::to_string(info.totalPrefabCount) +
		"\n    Elapsed: " + std::to_string(info.prefabLoadTimer) +
		"\nProgress (NavMesh): " + std::to_string(info.currentNavmeshCount) + "/" + std::to_string(info.totalNavmeshCount) +
		"\n    Elapsed: " + std::to_string(info.navmeshLoadTimer) +
		"\nProgress (Geometry): " + std::to_string(info.currentGeometryCount) + "/" + std::to_string(info.totalGeometryCount) +
		"\n    Elapsed: " + std::to_string(info.geometryLoadTimer) +
		"\nProgress (Collider): " + "TODO / TODO"
		"\n    Elapsed: " + "N/A" +
		"\nProgress (Building Colliders): " + "TODO / TODO" +
		"\n    Elapsed: " + "N/A" +
		"\nProgress (Pre building objects): " + std::to_string(info.currentObjectPartCount) + "/" + std::to_string(info.totalObjectPartCount) +
		"\n    Elapsed: " + std::to_string(info.objectPartLoadTimer) +
		"\nProgress (Building objects): " + std::to_string(info.currentObjectCount) + "/" + std::to_string(info.totalObjectCount) +
		"\n    Elapsed: " + std::to_string(info.objectLoadTimer) +
		"";
}

void Graphics::UI::LoadingScreenInfo::onMouseHover(const glm::vec2&)
{
}

void Graphics::UI::LoadingScreenInfo::updateFrame(const float&)
{
}

void Graphics::UI::LoadingScreenInfo::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& , of::graphics::view::MVP&)
{
	render();
}
