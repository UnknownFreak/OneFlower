#ifndef ModalBase_HPP
#define ModalBase_HPP

#include <utils/common/string.hpp>

namespace Graphics
{
	namespace Editor
	{
		namespace Modals
		{
			class ModalBase
			{
				bool m_isOpen = false;
				bool m_closed = true;
			protected:
				of::common::String m_modalName;

			public:
				ModalBase(const of::common::String& modalName);

				void open();
				bool isOpen() const;
				bool isClosed() const;
				void show();
				void close();

				virtual void OnOpen() = 0;
				virtual void ImGuiRenderModal() = 0;
			};
		}
	}
}

#endif
