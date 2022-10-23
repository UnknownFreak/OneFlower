#ifndef NewFileModal_HPP
#define NewFileModal_HPP

#include <vector>
#include "ModalBase.hpp"
#include <imgui/imgui.h>

namespace Graphics
{
	namespace Editor
	{
		namespace Modals
		{
			struct TreeItem
			{
				Core::String ItemName;
				std::vector<TreeItem> subItems;
				bool operator <(const TreeItem& other);
			};

			struct TreeItemRoot
			{
				Core::String ItemName;
				bool selected;
				std::vector<TreeItem> subItems;
				bool operator<(const TreeItemRoot& other);
			};


			class NewFile : public ModalBase
			{
				Core::String m_fileName;
				bool isMaster = false;
				std::vector<TreeItemRoot> modFiles;

				std::vector<TreeItem> loadDependencyDetails(const Core::String& file);

				void newModFile();

				ImVec4 drawTree(const TreeItem& item);
				void drawTree(TreeItemRoot& item);

			public:

				NewFile(const Core::String& modalName);

				void ImGuiRenderModal() override;
				void OnOpen() override;


			};

		}
	}
}



#endif