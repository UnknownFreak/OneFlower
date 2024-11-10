#include <internal/modal/loadFileModal.hpp>

#include <imgui/imgui.h>

#include <utils/os/ListDir.hpp>

#include <asset/internalAsset.hpp>
#include <asset/loadHeader.hpp>

#include <internal/editorContext.hpp>

namespace of::editor::modal
{
	void LoadFile::load()
	{
		//tree.clear();
		auto& managerInternal = of::asset::get();
		managerInternal.loadOrder.clear();
		auto& context = of::editor::getEditorContext();
		of::asset::Header& header = context.header;
		of::asset::loadHeader(m_selectedFile, header);

		std::set<of::common::String> loadOrder;

		const auto x = [&](auto const& ref, std::set<of::common::String>& loadOrder, std::vector<of::common::String>& items) -> void
			{
				for (auto& item : items)
				{
					of::asset::Header tmp;
					of::asset::loadHeader(item, tmp);
					loadOrder.insert(item);
					ref(ref, loadOrder, tmp.dependencies);
				}
			};
		for (auto& d : header.dependencies)
		{
			of::asset::Header tmp;
			of::asset::loadHeader(d, tmp);
			loadOrder.insert(d);
			x(x, loadOrder, tmp.dependencies);
		}

		context.buildModOrderFile(m_selectedFile, loadOrder);

		auto& logger = of::logger::get().getLogger("of::editor::modal::LoadFile");
		logger.Debug("Loading Editor Variables...");
		context.loadAllEditorVariables();
		logger.Info("Successfully loaded mod [" + header.name + "].");
		context.openedFileName = header.name;
	}
	LoadFile::LoadFile(const of::common::String& modalName/*, DataTree& tree*/) : ModalBase(modalName)/*, tree(tree)*/
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
		auto mainFiles = of::os::listDirectory("Data", ".main", false);
		auto i_modFiles = of::os::listDirectory("Data", ".mod", false);
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

	void LoadFile::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		if (isOpen())
			show();
		ImGuiRenderModal();
	}

}
