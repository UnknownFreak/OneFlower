#include "NewFileModal.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.hpp>

namespace Graphics::Editor::Modals
{

	NewFile::NewFile(const Core::String& modalName) : ModalBase(modalName), m_fileName("")
	{
	}

	void NewFile::ImGuiRenderModal()
	{
		ImGui::SetNextWindowSize({ 600.f, 400.f });
		if (ImGui::BeginPopupModal(m_modalName.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::Text("File Name");
			ImGui::InputText("###FileName", &m_fileName);
				
			ImGui::Checkbox("Is Main", &isMaster);
			ImGui::SameLine();
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(
					"Check if this file is a main file (only changes extension from .mod to .main)\n"
					"This only highlights the file as a possible base mod.\n"
					"You can still create a mod based of a mod, but it's more for clarification than anything");
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}


			ImGui::Text("Dependencies");
			if (ImGui::BeginListBox("###Dependencies"))
			{
				//ImGui::Selectable("###1", &test, 0, { 0.f, 19.f });
				//ImGui::SameLine();
				//ImGui::Checkbox("Dep1", &test);
				//ImGui::Selectable("###2", &test2, 0, { 0.f, 19.f });
				//ImGui::SameLine();
				//ImGui::Checkbox("Dep2", &test2);

				//ImGui::Selectable("###Dep3", (bool*)&c, ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled, { 0,19 });
				//ImGui::SameLine(30);
				//ImGui::Checkbox("Dep2", &test2);
				ImGui::EndListBox();
			}

			if (ImGui::Button("Create"))
			{
				close();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				close();
			}

			ImGui::EndPopup();
		}
	}
}
