#include "NewFileModal.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.hpp>

#include <Helpers/ListDir.hpp>
#include <File/Mod/ModHeader.hpp>
#include <File/Asset/Manager.hpp>

namespace Graphics::Editor::Modals
{
	void NewFile::loadDependencyDetails(const Core::String& file)
	{
		
		auto& manager = Engine::GetModule<File::Asset::Manager>();
		File::Mod::Header header;
		if (manager.loadModHeader(file, header))
		{
			dependencies.clear();
			for (auto dependency : header.dependencies)
			{
				dependencies.push_back({"", dependency});
				loadDependencyDetails(dependency, dependencies, 1);
			}
		}
	}
	void NewFile::loadDependencyDetails(const Core::String& file, std::vector<std::pair<Core::String, Core::String>>& i_dependencies, int index)
	{

		auto& manager = Engine::GetModule<File::Asset::Manager>();
		File::Mod::Header header;
		if (manager.loadModHeader(file, header))
		{
			for (auto dependency : header.dependencies)
			{
				Core::String indent = "";
				for (int i = 0; i < index; i++)
				{
					indent.push_back('-');
				}
				i_dependencies.push_back({ indent ,dependency});
				loadDependencyDetails(dependency, i_dependencies, index++);
			}
		}
	}


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

			auto cursor = ImGui::GetCursorPos();

			ImGui::SetCursorPos(ImVec2(480.f, 370.f));
			if (ImGui::Button("Create"))
			{
				close();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				close();
			}
			ImGui::SetCursorPos(cursor);

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 300.f);
			ImGui::SetColumnWidth(1, 300.f);

			ImGui::Text("Dependency Files");

			if (ImGui::BeginListBox("###Dependencies", ImVec2(300.f, 275.f)))
			{
				for (auto& file : modFiles)
				{
					std::string s = "###" + file.first;
					if (ImGui::Selectable(s.c_str(), &file.second, 0, { 0,19 }))
					{
						loadDependencyDetails(file.first);
					}
					ImGui::SameLine();
					ImGui::Checkbox(file.first.c_str(), &file.second);
					
				}
				ImGui::EndListBox();
			}
			ImGui::NextColumn();
			ImGui::Text("Dependencies");
			if (ImGui::BeginListBox("###Dependencies2", ImVec2(300.f, 275.f)))
			{

				for (auto& dependency : dependencies)
				{
					Core::String s = dependency.first + dependency.second;
					ImGui::Text(s.c_str());
				}
				ImGui::EndListBox();
			}


			ImGui::EndPopup();
		}
	}

	void NewFile::OnOpen()
	{
		auto mainFiles = Helpers::os::listDirectory("Data", ".main", false);
		auto i_modFiles = Helpers::os::listDirectory("Data", ".mod", false);
		modFiles.clear();

		for (auto file : mainFiles)
			modFiles.push_back(std::make_pair(file, false));
		for (auto file : i_modFiles)
			modFiles.push_back(std::make_pair(file, false));

		std::sort(modFiles.begin(), modFiles.end());
	}
}
