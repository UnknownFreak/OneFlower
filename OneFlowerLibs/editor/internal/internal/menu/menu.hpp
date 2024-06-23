#pragma once

#include <utils/common/string.hpp>

namespace of::editor::menu
{

	class Menu
	{
	protected:

		of::common::String m_menuName;
		of::common::String m_menuShortcut;
	public:

		Menu(const of::common::String& menuName, const of::common::String& menuShortcut)
		: m_menuName(menuName), m_menuShortcut(menuShortcut)
		{

		}

		virtual ~Menu() = default;
		
		virtual void draw() = 0;

	};
}