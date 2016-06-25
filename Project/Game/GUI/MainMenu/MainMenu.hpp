#ifndef	MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "OptionsPanel.hpp"
namespace Menu
{
	namespace MainMenu
	{

		class MainMenu
		{
			GUI::Window::Addon::Button m_newGame;
			GUI::Window::Addon::Button m_continue;
			GUI::Window::Addon::Button m_load;
			GUI::Window::Addon::Button m_options;
			GUI::Window::Addon::Button m_exit;

			Menu::Options::OptionsPanel m_optionsPanel;
			bool open = true;
		public:
			MainMenu();
			void draw();
			void WindowHandle();
			bool isOpen();
		
		private:

			void exit();
			void options();
			void loadGame();
			void continueGame();
			void newGame();
			void showHide();

		};
	}
}

#endif