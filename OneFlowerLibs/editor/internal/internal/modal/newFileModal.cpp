#include <internal/modal/newFileModal.hpp>

#include <imgui/imgui_stdlib.hpp>

#include <utils/os/ListDir.hpp>

#include <file/Header.hpp>
#include <file/Handler.hpp>
#include <file/archive/loadHeader.hpp>

#include <imgui/basicToolTip.hpp>


namespace of::editor::modal
{

	std::vector<TreeItem> NewFile::loadDependencyDetails(const of::common::String& file)
	{
		std::vector<TreeItem> deps;
		of::file::Header header;
		if (of::file::archive::loadHeader(file, header))
		{
			for (auto dependency : header.dependencies)
			{
				TreeItem ti{ dependency, loadDependencyDetails(dependency) };
				deps.push_back(ti);
			}
		}
		return deps;
	}

	void NewFile::newModFile()
	{
		//tree.clear();
		auto& manager = of::engine::GetModule<of::file::Handler>();
		auto& modLoader = of::engine::GetModule<of::file::Loader>();
		modLoader.loadOrder.clear();

		std::vector<of::common::String> deps;
		std::set<of::common::String> loadOrder;


		const auto x = [&](auto const& ref, std::set<of::common::String>& loadOrder, std::vector<TreeItem>& items) -> void
			{
				for (auto& item : items)
				{
					loadOrder.insert(item.ItemName);
					ref(ref, loadOrder, item.subItems);
				}
			};
		for (auto& d : modFiles)
			if (d.selected)
			{
				deps.push_back(d.ItemName);
				loadOrder.insert(d.ItemName);
				x(x, loadOrder, d.subItems);
			}

		of::common::String fileName = m_fileName;
		if (isMaster)
			fileName.append(".main");
		else
			fileName.append(".mod");

		of::file::Header header;
		header.name = fileName;
		header.dependencies = deps;

		manager.buildModOrderFile(fileName, loadOrder);

		manager.openedFile = header;
		auto& logger = of::engine::GetModule<of::logger::Logger>().getLogger("of::editor::modal::NewFile");
		//logger.Debug("Creating new language module [" + Core::Builtin + "].");
		//manager.getLanguage();

		logger.Debug("Saving the file...");
		manager.saveGameDatabase(header.name, header);
		logger.Debug("Loading Editor Variables...");
		manager.loadAllEditorVariables();
		logger.Info("Successfully created mod [" + header.name + "].");

	}

	ImVec4 NewFile::drawTree(const TreeItem& item)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

		ImVec2 padding = ImGui::GetCursorScreenPos();

		if (item.subItems.size() == 0)
		{
			flags |= ImGuiTreeNodeFlags_Leaf;
			padding.x -= 15.f;
		}

		ImGui::SetCursorScreenPos(padding);
		const bool recurse = ImGui::TreeNodeEx(item.ItemName.c_str(), flags);
		if (item.subItems.size() == 0)
		{
			padding = ImGui::GetCursorScreenPos();
			padding.x += 15.f;
			ImGui::SetCursorScreenPos(padding);
		}
		auto [x, y] = ImGui::GetItemRectMin();
		auto [w, h] = ImGui::GetItemRectMax();
		const ImVec4 nodeRect = ImVec4(x, y, w, h);
		if (recurse)
		{
			const ImColor TreeLineColor = ImColor(128, 128, 128, 255);
			const float SmallOffsetX = -10.0f; //for now, a hardcoded value; should take into account tree indent size
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			ImVec2 verticalLineStart = ImGui::GetCursorScreenPos();
			verticalLineStart.x += SmallOffsetX; //to nicely line up with the arrow symbol
			ImVec2 verticalLineEnd = verticalLineStart;

			for (auto& i : item.subItems)
			{
				const float HorizontalTreeLineSize = 8.0f; //chosen arbitrarily
				const ImVec4 childRect = drawTree(i);
				const float midpoint = (childRect.y + childRect.w) / 2.0f;
				drawList->AddLine(ImVec2(verticalLineStart.x, midpoint), ImVec2(verticalLineStart.x + HorizontalTreeLineSize, midpoint), TreeLineColor);
				verticalLineEnd.y = midpoint;
			}
			drawList->AddLine(verticalLineStart, verticalLineEnd, TreeLineColor);
			ImGui::TreePop();
		}
		return nodeRect;
	}

	void NewFile::drawTree(TreeItemRoot& item)
	{
		std::string s = "###" + item.ItemName;
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (item.subItems.size() == 0)
			flags |= ImGuiTreeNodeFlags_Leaf;

		const bool recurse = ImGui::TreeNodeEx(s.c_str(), flags);
		auto [x, y] = ImGui::GetItemRectMin();
		auto [w, h] = ImGui::GetItemRectMax();
		const ImVec4 nodeRect = ImVec4(x, y, w, h);

		ImGui::SameLine();
		ImGui::Checkbox(item.ItemName.c_str(), &item.selected);

		if (recurse)
		{
			const ImColor TreeLineColor = ImColor(128, 128, 128, 255);
			const float SmallOffsetX = -10.0f; //for now, a hardcoded value; should take into account tree indent size
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			ImVec2 verticalLineStart = ImGui::GetCursorScreenPos();
			verticalLineStart.x += SmallOffsetX; //to nicely line up with the arrow symbol
			ImVec2 verticalLineEnd = verticalLineStart;

			for (auto& i : item.subItems)
			{
				const float HorizontalTreeLineSize = 8.0f; //chosen arbitrarily
				const ImVec4 childRect = drawTree(i);
				const float midpoint = (childRect.y + childRect.w) / 2.0f;
				drawList->AddLine(ImVec2(verticalLineStart.x, midpoint), ImVec2(verticalLineStart.x + HorizontalTreeLineSize, midpoint), TreeLineColor);
				verticalLineEnd.y = midpoint;
			}
			drawList->AddLine(verticalLineStart, verticalLineEnd, TreeLineColor);

			ImGui::TreePop();
		}
	}


	NewFile::NewFile(const of::common::String& modalName)/*, DataTree& tree)*/ : ModalBase(modalName), m_fileName("")/*, tree(tree)*/
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
			imgui::BasicToolTip(
				"Check if this file is a main file (only changes extension from .mod to .main)\n"
				"This only highlights the file as a possible base mod.\n"
				"You can still create a mod based of a mod, but it's more for clarification than anything");
			ImGui::Text("Select Dependencies");
			if (ImGui::BeginListBox("###Dependencies", ImVec2(-1, 275.f)))
			{
				for (auto& file : modFiles)
				{
					drawTree(file);
				}
				ImGui::EndListBox();
			}

			ImGui::SetCursorPos(ImVec2(480.f, 370.f));
			if (ImGui::Button("Create", ImVec2(50, 0)))
			{
				if (m_fileName != "")
				{
					newModFile();
					close();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(50, 0)))
			{
				close();
			}
			ImGui::EndPopup();
		}
	}

	void NewFile::OnOpen()
	{
		m_fileName = "";
		auto mainFiles = of::os::listDirectory("Data", ".main", false);
		auto i_modFiles = of::os::listDirectory("Data", ".mod", false);
		modFiles.clear();

		for (auto file : mainFiles)
		{
			auto itm = loadDependencyDetails(file);
			modFiles.push_back(TreeItemRoot{ file, false, itm });
		}
		for (auto file : i_modFiles)
		{
			auto itm = loadDependencyDetails(file);
			modFiles.push_back({ file, false, itm });
		}

		std::sort(modFiles.begin(), modFiles.end());
	}

	void NewFile::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& , of::graphics::view::MVP& )
	{
		if (isOpen())
			show();
		ImGuiRenderModal();
	}


	bool TreeItem::operator<(const TreeItem& other)
	{
		return ItemName < other.ItemName;
	}
	bool TreeItemRoot::operator<(const TreeItemRoot& other)
	{
		return ItemName < other.ItemName;
	}
}
