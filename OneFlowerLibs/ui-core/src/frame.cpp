#include <graphics/ui/frame.hpp>

namespace of::graphics::ui
{

	Frame::Frame(const ImVec4& frameSize, const Relation& relation) : UIRenderable(frameSize, relation) {
		m_frameIdString = "###" + m_frameId.to_string();
	}

	void Frame::beginRender()
	{
		ImGui::SetNextWindowPos({ m_renderBox.x, m_renderBox.y });
		ImGui::SetNextWindowSize({ m_renderBox.z, m_renderBox.w });
		ImGui::Begin(m_frameIdString.c_str(), nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	}

	void Frame::render()
	{
	}

	void Frame::endRender()
	{
		ImGui::End();
	}
}