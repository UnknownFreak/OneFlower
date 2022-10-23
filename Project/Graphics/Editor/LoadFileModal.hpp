#ifndef LoadFileModal_HPP
#define LoadFileModal_HPP

#include <vector>

#include "ModalBase.hpp"

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

			public:

				LoadFile(const Core::String& modalName);

				void ImGuiRenderModal() override;
				void OnOpen() override;


			};

		}
	}
}

#endif