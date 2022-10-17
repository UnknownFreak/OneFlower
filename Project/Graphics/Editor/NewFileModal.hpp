#ifndef NewFileModal_HPP
#define NewFileModal_HPP

#include "ModalBase.hpp"

namespace Graphics
{
	namespace Editor
	{
		namespace Modals
		{
			class NewFile : public ModalBase
			{
				bool m_isOpen = false;
				Core::String m_fileName;
				bool isMaster = false;
			public:

				NewFile(const Core::String& modalName);

				void ImGuiRenderModal() override;


			};

		}
	}
}



#endif