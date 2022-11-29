#include "ModalBase.hpp"

#include <imgui/imgui.h>

namespace Graphics::Editor::Modals
{
    ModalBase::ModalBase(const of::common::String& modalName) : m_modalName(modalName)
{
}

    void ModalBase::open()
    {
        m_isOpen = true;
    }

    bool ModalBase::isOpen() const
    {
        return m_isOpen;
    }

    bool ModalBase::isClosed() const
    {
        return m_closed;
    }

    void ModalBase::show()
    {
        m_isOpen = false;
        m_closed = false;
        OnOpen();
        ImGui::OpenPopup(m_modalName.c_str());

    }
    void ModalBase::close()
    {
        m_closed = true;
        ImGui::CloseCurrentPopup();
    }
}
