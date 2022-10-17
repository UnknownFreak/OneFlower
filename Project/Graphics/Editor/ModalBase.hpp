#ifndef ModalBase_HPP
#define ModalBase_HPP

#include <Helpers/String.hpp>

namespace Graphics
{
	namespace Editor
	{
		namespace Modals
		{
			class ModalBase
			{
				bool m_isOpen = false;
			protected:
				Core::String m_modalName;

			public:
				ModalBase(const Core::String& modalName);

				void open();
				bool isOpen() const;
				void show();

				virtual void ImGuiRenderModal() = 0;
			};
		}
	}
}

#endif
