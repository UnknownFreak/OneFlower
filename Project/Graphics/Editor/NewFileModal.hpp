#ifndef NewFileModal_HPP
#define NewFileModal_HPP

#include <vector>
#include <imgui/modalBase.hpp>
#include <imgui/imgui.h>
#include "DataTree.hpp"
namespace Graphics
{
	namespace Editor
	{
		namespace Modals
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


			class NewFile : public of::imgui::ModalBase
			{
				of::common::String m_fileName;
				bool isMaster = false;
				std::vector<TreeItemRoot> modFiles;
				DataTree& tree;

				std::vector<TreeItem> loadDependencyDetails(const of::common::String& file);

				void newModFile();

				ImVec4 drawTree(const TreeItem& item);
				void drawTree(TreeItemRoot& item);

			public:

				NewFile(const of::common::String& modalName, DataTree& tree);

				void ImGuiRenderModal() override;
				void OnOpen() override;


			};

		}
	}
}



#endif