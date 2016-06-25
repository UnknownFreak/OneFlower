#ifndef OPTIONS_PANEL_HPP
#define OPTIONS_PANEL_HPP

#include "../Window/BaseWindow.hpp"
#include "../Text/Message.hpp"
namespace Menu
{
	namespace Options
	{

		class OptionsPanel
		{
			GUI::Window::Addon::Button m_general;
			GUI::Window::Addon::Button m_keybinds;
			GUI::Window::Addon::Button m_close;
			
			bool open;

			sf::Sprite window;
			Vector2 position;
			sf::VertexArray outline;
			GUI::Text::Message title;
		public:
			OptionsPanel();

			void draw();
			void WindowHandle();

			void openPanel();

			bool isOpen();

			void close();

		};
	}
}


#endif