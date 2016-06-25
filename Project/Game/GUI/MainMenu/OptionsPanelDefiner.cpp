#include "OptionsPanel.hpp"
#include "../../../Engine.hpp"

namespace Menu
{
	namespace Options
	{

		OptionsPanel::OptionsPanel() : outline(sf::LinesStrip, 5), open(false), window(*Engine::Graphic.requestTexture("DefaultWindow.png"), sf::IntRect(0, 0, 400, 500)),
			title(*Engine::Graphic.font.requestFont("arial.ttf")), m_close("ToolTipIcon.png", "x", sf::IntRect(0, 0, 26, 26), 0, 0, GUI::Window::Addon::Button::Center)
		{
			m_close.setPosition(600-26, 50);
			this->title = " Options";
			this->title.setSize(21);
			outline[0].position = sf::Vector2f(200, 50);
			outline[1].position = sf::Vector2f(200 + 400, 50);
			outline[2].position = sf::Vector2f(200 + 400, 50 + 500);
			outline[3].position = sf::Vector2f(200, 50 + 500);
			outline[4].position = sf::Vector2f(200, 50);

			outline[0].color = sf::Color::Black;
			outline[1].color = sf::Color::Black;
			outline[2].color = sf::Color::Black;
			outline[3].color = sf::Color::Black;
			outline[4].color = sf::Color::Black;

			window.setPosition(200, 50);
			title.setPosition(200, 50);
			m_close.onClick = std::bind(&OptionsPanel::close, this);
			Engine::Input.registerCallback(std::bind(&OptionsPanel::close, this), sf::Keyboard::Escape, Input::Action::Release);
		}
		void OptionsPanel::draw()
		{
			Engine::Graphic.view.render.draw(window);
			Engine::Graphic.view.render.draw(outline);

			title.draw();
			m_close.draw();

			if (m_close.onHover() && Engine::Input.mouse.leftClick())
				m_close.onClick();
			WindowHandle();
		}
		void OptionsPanel::WindowHandle()
		{
		}
		void OptionsPanel::openPanel()
		{
			open = true;
		}
		void OptionsPanel::close()
		{
			open = false;
		}
		bool OptionsPanel::isOpen()
		{
			return open;
		}
	}
}