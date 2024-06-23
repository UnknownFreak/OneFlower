#pragma once

#include "menu.hpp"
#include <vector>

#include <imgui/imgui.h>
#include <functional>

namespace of::editor::menu
{

	class SubMenu : public Menu
	{
		std::vector<std::shared_ptr<Menu>> m_subMenus;

	public:
		SubMenu(const of::common::String& name, const of::common::String& shortcut)
			: Menu(name, shortcut)
		{
		}
		~SubMenu() = default;

		void addMenu(std::shared_ptr<Menu> menuItem)
		{
			m_subMenus.push_back(menuItem);
		}

		void draw() override
		{

			if (ImGui::BeginMenu(m_menuName.c_str()))
			{
				for (auto& subMenu : m_subMenus)
				{
					subMenu->draw();
				}
				ImGui::EndMenu();
			}
		}
	};

	class Separator : public Menu
	{

	public:
		Separator()
			: Menu("", "")
		{
		}

		~Separator() = default;

		void draw() override
		{
			ImGui::Separator();
		}
	};

	class SubMenuCallback : public Menu
	{
		std::function<void()> m_callback;
	public:
		SubMenuCallback(const of::common::String& name, const of::common::String& shortcut, std::function<void()> func)
			: Menu(name, shortcut)
			, m_callback(func)
		{
		}
		~SubMenuCallback() = default;

		void draw() override
		{

			if(ImGui::MenuItem(m_menuName.c_str(), m_menuShortcut.c_str()))
			{
				m_callback();
			}
		}

	};

}