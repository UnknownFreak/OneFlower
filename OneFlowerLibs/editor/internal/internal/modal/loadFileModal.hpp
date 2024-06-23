#pragma once
#include <vector>

#include <graphics/parentedRenderable.hpp>

#include <imgui/modalBase.hpp>


namespace of::editor::modal
{

	class LoadFile : public of::imgui::ModalBase, public graphics::ParentedRenderable
	{
		of::common::String m_selectedFile;
		std::vector<std::pair<of::common::String, bool>> m_fileNames;
		void load();
		/*DataTree& tree;*/
	public:

		LoadFile(const of::common::String& modalName); // , DataTree& tree);

		void ImGuiRenderModal() override;
		void OnOpen() override;
		virtual void updateFrame(const float ) override {}

		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&) override;
	};
}