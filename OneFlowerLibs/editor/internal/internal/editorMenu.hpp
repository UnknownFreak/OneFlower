#pragma once

#include <graphics/parentedRenderable.hpp>

#include <vector>
#include <internal/menu/menu.hpp>
#include <imgui/imgui.h>

namespace of::editor
{

	class EditorMenu : public of::graphics::ParentedRenderable
	{
		std::vector<std::shared_ptr<menu::Menu>> m_menus;

	public:

		EditorMenu() = default;

		void addMenu(std::shared_ptr<menu::Menu> menu)
		{
			m_menus.push_back(menu);
		}

		// Inherited via ParentedRenderable
		virtual void updateFrame(const float& ) override {}
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& , of::graphics::view::MVP& ) override
		{
			if (ImGui::BeginMainMenuBar())
			{
				for (auto& menu: m_menus)
				{
					menu->draw();
				}
				ImGui::EndMainMenuBar();
			}
		}
	};

}