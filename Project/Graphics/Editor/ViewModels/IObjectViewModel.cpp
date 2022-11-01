#include "IObjectViewModel.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.hpp>

namespace Graphics::Editor::ViewModels
{

	bool renderInfo(Interfaces::IObject* ptr, const bool& showIdentifier)
	{
		bool b = false;
		ImGui::Text("Basic Attributes:");
		if (showIdentifier)
		{
			ImGui::SameLine();
			ImGui::TextDisabled(ptr->identifier.to_string().c_str());
		}
		ImGui::NewLine();
		ImGui::Text("Object Name: ");
		ImGui::SameLine();
		ImGui::SetCursorPosX(120);
		if (ImGui::InputText("###ObjectName", &ptr->name))
		{
			b = true;
		}

		ImGui::Text("Tag: ");
		ImGui::SameLine();
		ImGui::SetCursorPosX(120);
		if (ImGui::InputText("###ObjectTag", &ptr->tag))
		{
			b = true;
		}
		ImGui::Separator();
		ImGui::Text("Specific Attributes:");
		ImGui::NewLine();
		return b;
	}
}
