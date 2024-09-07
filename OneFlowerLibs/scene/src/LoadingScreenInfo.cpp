#include <scene/imgui/LoadingScreenInfo.hpp>

#include <engine/settings.hpp>

#include <imgui/imgui.h>
#include <scene/sceneManager.hpp>

namespace of::scene::imgui
{
	LoadingScreenInfo::LoadingScreenInfo(of::world::LoadingStateInfo& info) : mInfo(info)
	{
		visible = of::settings::get().showLoadingScreenInfo();
		auto height = of::settings::get().getScreenResolution().height;
		pos = { 15, height - 520.f };
	}

	void LoadingScreenInfo::updateFrame(const float)
	{
		t =
			"\nIs Loading: " + std::to_string(mInfo.isLoading) +
			"\nElapsed time: " + std::to_string(mInfo.totalLoadTime) +
			"\nLoading State: " + of::world::to_string(mInfo.theState) +
			"\nProgress (Total): " + std::to_string(mInfo.currentLoadCount) + "/" + std::to_string(mInfo.totalLoadCount) +
			"\nTime (Prepare load): " + std::to_string(mInfo.instanceLoadTime) +
			"\nProgress (CutScenes): " + std::to_string(mInfo.currentCutSceneCount) + "/" + std::to_string(mInfo.totalCutSceneCount) +
			"\n    Elapsed: " + std::to_string(mInfo.totalCutSceneCountTimer) +
			"\nProgress (Instances): " + std::to_string(mInfo.currentZoneCount) + "/" + std::to_string(mInfo.totalZoneCount) +
			"\n    Elapsed: " + std::to_string(mInfo.totalZoneUpdateCountTimer) +
			"\nProgress (Unload objects): " + "TODO / TODO" +
			"\n    Elapsed: " + "N/A" +
			"\nProgress (Prefabs): " + std::to_string(mInfo.currentPrefabCount) + "/" + std::to_string(mInfo.totalPrefabCount) +
			"\n    Elapsed: " + std::to_string(mInfo.prefabLoadTimer) +
			"\nProgress (NavMesh): " + std::to_string(mInfo.currentNavmeshCount) + "/" + std::to_string(mInfo.totalNavmeshCount) +
			"\n    Elapsed: " + std::to_string(mInfo.navmeshLoadTimer) +
			"\nProgress (Geometry): " + std::to_string(mInfo.currentGeometryCount) + "/" + std::to_string(mInfo.totalGeometryCount) +
			"\n    Elapsed: " + std::to_string(mInfo.geometryLoadTimer) +
			"\nProgress (Collider): " + "TODO / TODO"
			"\n    Elapsed: " + "N/A" +
			"\nProgress (Building Colliders): " + "TODO / TODO" +
			"\n    Elapsed: " + "N/A" +
			"\nProgress (Pre building objects): " + std::to_string(mInfo.currentObjectPartCount) + "/" + std::to_string(mInfo.totalObjectPartCount) +
			"\n    Elapsed: " + std::to_string(mInfo.objectPartLoadTimer) +
			"\nProgress (Building objects): " + std::to_string(mInfo.currentObjectCount) + "/" + std::to_string(mInfo.totalObjectCount) +
			"\n    Elapsed: " + std::to_string(mInfo.objectLoadTimer) +
			"";
	}

	void LoadingScreenInfo::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		if (visible)// && mInfo.isLoading)
		{
			auto vp = ImGui::GetWindowViewport();
			ImGui::SetNextWindowPos(ImVec2{ vp->Pos.x + pos.x, vp->Pos.y + pos.y }, ImGuiCond_::ImGuiCond_Once);
			ImGui::SetWindowFocus();
			ImGui::Begin("LoadingScreenInfo", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
			{
				ImGui::Text("%s", t.c_str());
			}
			ImGui::End();
		}
	}
}