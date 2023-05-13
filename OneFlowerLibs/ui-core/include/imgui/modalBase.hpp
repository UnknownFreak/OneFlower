#pragma once

#include <utils/common/string.hpp>

namespace of::imgui
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