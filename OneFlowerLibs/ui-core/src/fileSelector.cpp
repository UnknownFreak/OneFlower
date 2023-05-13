#include <imgui/fileSelector.hpp>

#include <imgui/imgui.h>

#include <utils/os/ListDir.hpp>
#include <algorithm>

namespace of::imgui
{

	void of::imgui::FileSelector::load()
	{
		if (m_selectedFile != "")
		{
			fileSelected = true;
		}
	}

	of::imgui::FileSelector::FileSelector(const of::common::String& modalName, const of::common::String& path, const of::common::String& fileExt) : ModalBase(modalName), m_path(path), m_fileExtension(fileExt)
	{
	}

	void of::imgui::FileSelector::ImGuiRenderModal()
	{
		ImGui::SetNextWindowSize({ 600.f, 400.f });
		if (ImGui::BeginPopupModal(m_modalName.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove))
		{
			if (ImGui::BeginListBox("###Dependencies", ImVec2(-1, 335.f)))
			{
				for (auto& file : m_fileNames)
				{
					if (m_selectedFile != file.first)
						file.second = false;
					if (ImGui::Selectable(file.first.c_str(), &file.second))
					{
						m_selectedFile = file.first;
					}
				}
				ImGui::EndListBox();
			}

			ImGui::SetCursorPos(ImVec2(480.f, 370.f));
			if (ImGui::Button("Load", ImVec2(50, 0)))
			{
				load();
				close();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(50, 0)))
			{
				close();
			}

			ImGui::EndPopup();
		}
	}

	void of::imgui::FileSelector::OnOpen()
	{
		auto mainFiles = of::os::listDirectory(m_path, m_fileExtension, false);
		m_fileNames.clear();
		m_selectedFile = "";

		for (auto file : mainFiles)
		{
			m_fileNames.push_back({ file, false });
		}
		std::sort(m_fileNames.begin(), m_fileNames.end());
	}

	bool FileSelector::hasFileBeenSelected()
	{
		return fileSelected;
	}

	of::common::String FileSelector::getSelectedFile()
	{
		fileSelected = false;
		return m_path + m_selectedFile;
	}

}
