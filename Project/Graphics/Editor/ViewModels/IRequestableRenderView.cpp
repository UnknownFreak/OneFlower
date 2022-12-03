#include "IRequestableRenderView.hpp"

#include <imgui/imgui.h>

namespace Graphics::Editor::ViewModels
{
	void renderInfo(of::file::archive::Requestable* ptr)
	{
		ImGui::SameLine();
		ImGui::TextDisabled("(Version: ");
		ImGui::SameLine();
		ImGui::TextDisabled(ptr->objectVersion.str().c_str());
		ImGui::SameLine();
		ImGui::TextDisabled(")");
		ImGui::NewLine();
		ImGui::Text("Type: ");
		ImGui::SameLine();
		ImGui::Text(of::file::to_string(ptr->objectType).c_str());
		ImGui::Text("Id:");
		ImGui::SameLine();
		ImGui::TextDisabled(ptr->fromMod.c_str());
		ImGui::SameLine();
		ImGui::TextDisabled("-");
		ImGui::SameLine();
		ImGui::TextDisabled(ptr->ID.to_string().c_str());
		ImGui::Text("Save Mode:");
		ImGui::SameLine();
		ImGui::Text(of::file::archive::to_string(ptr->mode).c_str());
	}
}
