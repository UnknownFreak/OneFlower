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
				Core::String m_selectedFile;
				std::vector<std::pair<Core::String, bool>> m_fileNames;
				void load();
				DataTree& tree;
			public:

				LoadFile(const Core::String& modalName, DataTree& tree);

				void ImGuiRenderModal() override;
				void OnOpen() override;


			};

		}
	}
}

#endif