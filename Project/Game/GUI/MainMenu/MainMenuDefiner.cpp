#include "MainMenu.hpp"
#include "../../../Engine.hpp"
namespace Menu
{
	namespace MainMenu
	{
		MainMenu::MainMenu()
		{
			m_newGame = GUI::Window::Addon::Button("ToolTipIcon.png", "New Game", sf::IntRect(0, 0, 100, 30),0,0,GUI::Window::Addon::Button::Center);
			m_continue = GUI::Window::Addon::Button("ToolTipIcon.png", "Continue", sf::IntRect(0, 0, 100, 30), 0, 0, GUI::Window::Addon::Button::Center);
			m_load = GUI::Window::Addon::Button("ToolTipIcon.png", "Load Game", sf::IntRect(0, 0, 100, 30), 0, 0, GUI::Window::Addon::Button::Center);
			m_options = GUI::Window::Addon::Button("ToolTipIcon.png", "Options", sf::IntRect(0, 0, 100, 30), 0, 0, GUI::Window::Addon::Button::Center);
			m_exit = GUI::Window::Addon::Button("ToolTipIcon.png", "Exit", sf::IntRect(0, 0, 100, 30), 0, 0, GUI::Window::Addon::Button::Center);

			m_newGame.onClick = std::bind(&MainMenu::newGame, this);
			m_continue.onClick = std::bind(&MainMenu::continueGame, this);
			m_load.onClick = std::bind(&MainMenu::loadGame, this);
			m_options.onClick = std::bind(&MainMenu::options, this);
			m_exit.onClick = std::bind(&MainMenu::exit, this);


		}
		void MainMenu::showHide()
		{
			open != open;
		}
		void MainMenu::draw()
		{
			if (!m_optionsPanel.isOpen())
			{
				WindowHandle();
				m_newGame.draw();
				m_continue.draw();
				m_load.draw();
				m_options.draw();
				m_exit.draw();

				if (m_newGame.onHover())
				{
				}
				if (m_continue.onHover())
				{
				}
				if (m_load.onHover())
				{
				}
				if (m_options.onHover() && Engine::Input.mouse.leftClick())
				{
					if (m_options.onClick != nullptr)
					{
						m_options.onClick();
						std::cout << &m_optionsPanel << std::endl;
					}
				}
				if (m_exit.onHover() && Engine::Input.mouse.leftClick())
				{
					if (m_exit.onClick != nullptr)
						m_exit.onClick();
				}
			}
			else
			{
				m_optionsPanel.draw();
			}
		}
		void MainMenu::WindowHandle()
		{
			m_newGame.setPosition(320 , 40);
			m_continue.setPosition(320, 80);
			m_load.setPosition(320, 120);
			m_options.setPosition(320, 160);
			m_exit.setPosition(320, 200);
		}

		// functions for the buttons go here
		void MainMenu::exit()
		{
			Engine::Graphic.view.render.close();
		}
		void MainMenu::options()
		{
			m_optionsPanel.openPanel();
		}
		void MainMenu::loadGame()
		{

		}
		void MainMenu::continueGame()
		{
		}
		void MainMenu::newGame()
		{
		}

		bool MainMenu::isOpen()
		{
			return open;
		}
	}
}