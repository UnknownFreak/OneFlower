#pragma once

#include <vector>
#include <imgui/modalBase.hpp>
#include <imgui/imgui.h>
#include <graphics/parentedRenderable.hpp>

namespace of::editor::modal
{
	struct TreeItem
	{
		of::common::String ItemName;
		std::vector<TreeItem> subItems;
		bool operator <(const TreeItem& other);
	};

	struct TreeItemRoot
	{
		of::common::String ItemName;
		bool selected;
		std::vector<TreeItem> subItems;
		bool operator<(const TreeItemRoot& other);
	};


	class NewFile : public of::imgui::ModalBase, public of::graphics::ParentedRenderable
	{
		of::common::String m_fileName;
		bool isMaster = false;
		std::vector<TreeItemRoot> modFiles;
		//DataTree& tree;

		std::vector<TreeItem> loadDependencyDetails(const of::common::String& file);

		void newModFile();

		ImVec4 drawTree(const TreeItem& item);
		void drawTree(TreeItemRoot& item);

		void ImGuiRenderModal() override;
		void OnOpen() override;

	public:

		NewFile(const of::common::String& modalName);// , DataTree& tree);

		virtual void updateFrame(const float&) {}
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp) override;
	};
}