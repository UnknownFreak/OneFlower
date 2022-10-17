#include "ModalBase.hpp"

#include <imgui/imgui.h>

namespace Graphics::Editor::Modals
{
    ModalBase::ModalBase(const Core::String& modalName) : m_modalName(modalName)
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

    void ModalBase::show()
    {
        m_isOpen = false;
        ImGui::OpenPopup(m_modalName.c_str());

    }
}
