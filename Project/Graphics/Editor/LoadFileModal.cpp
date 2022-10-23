#include "LoadFileModal.hpp"

#include <imgui/imgui.h>

#include <Helpers/ListDir.hpp>
#include <File/Asset/Manager.hpp>


namespace Graphics::Editor::Modals
{
	void LoadFile::load()
	{
		auto& manager = Engine::GetModule<File::Asset::Manager>();
		auto& modLoader = manager.getModLoader();
		modLoader.loadOrder.clear();

		File::Mod::Header header;
		manager.loadModHeader(m_selectedFile, header);


		std::set<Core::String> loadOrder;


		const auto x = [&](auto const& ref, std::set<Core::String>& loadOrder, std::vector<Core::String>& items) -> void
		{
			for (auto& item : items)
			{
				File::Mod::Header tmp;
				manager.loadModHeader(item, tmp);
				loadOrder.insert(item);
				ref(ref, loadOrder, tmp.dependencies);
			}
		};
		for (auto& d : header.dependencies)
		{
			File::Mod::Header tmp;
			manager.loadModHeader(d, tmp);
			loadOrder.insert(d);
			x(x, loadOrder, tmp.dependencies);
		}

		manager.buildModOrderFile(m_selectedFile, loadOrder);

		manager.openedMod = header;
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Graphics::Editor::Modals::LoadFile");
		logger.Debug("Loading Editor Variables...");
		manager.loadAllEditorVariables();
		logger.Info("Successfully loaded mod [" + header.name + "].");
	}
	LoadFile::LoadFile(const Core::String& modalName) : ModalBase(modalName)
	{
	}
	void LoadFile::ImGuiRenderModal()
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
	void LoadFile::OnOpen()
	{
		auto mainFiles = Helpers::os::listDirectory("Data", ".main", false);
		auto i_modFiles = Helpers::os::listDirectory("Data", ".mod", false);
		m_fileNames.clear();

		for (auto file : mainFiles)
		{
			m_fileNames.push_back({ file, false });
		}
		for (auto file : i_modFiles)
		{
			m_fileNames.push_back({ file, false });
		}

		std::sort(m_fileNames.begin(), m_fileNames.end());
	}
}
