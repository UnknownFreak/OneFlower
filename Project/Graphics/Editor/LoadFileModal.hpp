#ifndef LoadFileModal_HPP
#define LoadFileModal_HPP

#include <vector>

#include "ModalBase.hpp"
#include "DataTree.hpp"

namespace Graphics
{
	namespace Editor
	{
		namespace Modals
		{

			class LoadFile : public ModalBase
			{
				of::common::String m_selectedFile;
				std::vector<std::pair<of::common::String, bool>> m_fileNames;
				void load();
				DataTree& tree;
			public:

				LoadFile(const of::common::String& modalName, DataTree& tree);

				void ImGuiRenderModal() override;
				void OnOpen() override;


			};

		}
	}
}

#endif